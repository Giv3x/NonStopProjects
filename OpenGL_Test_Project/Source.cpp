#include <iostream>
#include <GL\glew.h>

#include "Display.h"
#include "BasicShader.h"
#include "utility.h"
#include "Camera.h"
#include "Entity.h"
#include "Loader.h"
#include "OBJloader.h"
#include "Player.h"
#include "GUI.h"

#include "MasterRenderer.h"
#include "WaterRenderer.h"
#include "GuiRenderer.h"
#include "WaterFrameBuffer.h"

int main(int argc, char** argv) {
	Display display(1280, 768, "OpenGL Tutorial Project");
	SDL_Event eventSDL;
	Transform transform;

	display._init();

	WaterFrameBuffer waterFrameBuffer(1280, 720, 1280, 720, display);

	MasterRenderer masterRenderer;
	WaterRenderer waterRenderer;
	GuiRenderer guiRenderer;
	
	TexturedModel barrelModel(OBJloader::load("res/objs/normal_models/barrel.obj", true), Loader::loadTexture2D("res/textures/normal_map_textures/barrel.png"), glm::vec3(0.5, 0.5, 0.5), glm::vec3(2, 2, 2), glm::vec3(0.6, 0.6, 0.6));
	barrelModel.addTexture(Loader::loadTexture2D("res/textures/normal_map_textures/barrelNormal.png"));
	TexturedModel boulderModel(OBJloader::load("res/objs/normal_models/boulder.obj", true), Loader::loadTexture2D("res/textures/normal_map_textures/boulder.png"), glm::vec3(0.9, 0.9, 0.9), glm::vec3(2, 2, 2), glm::vec3(0.6, 0.6, 0.6));
	boulderModel.addTexture(Loader::loadTexture2D("res/textures/normal_map_textures/boulderNormal.png"));
	TexturedModel crateModel(OBJloader::load("res/objs/normal_models/crate.obj", true), Loader::loadTexture2D("res/textures/normal_map_textures/crate.png"), glm::vec3(0.9, 0.9, 0.9), glm::vec3(2, 2, 2), glm::vec3(0.6, 0.6, 0.6));
	crateModel.addTexture(Loader::loadTexture2D("res/textures/normal_map_textures/crateNormal.png"));
	
	TexturedModel playerModel(OBJloader::load("res/objs/person.obj"), Loader::loadTexture2D("res/textures/playerTexture.png"), glm::vec3(0.9, 0.9, 0.9), glm::vec3(2, 2, 2), glm::vec3(0.6, 0.6, 0.6));
	TexturedModel treeModel(OBJloader::load("res/objs/pine.obj"), Loader::loadTexture2D("res/textures/pine.png"), glm::vec3(0.9, 0.9, 0.9), glm::vec3(2, 2, 2), glm::vec3(0.6, 0.6, 0.6));
	TexturedModel fernModel(OBJloader::load("res/objs/fern.obj"), Loader::loadTexture2D("res/textures/fern.png", true), glm::vec3(0.9, 0.9, 0.9), glm::vec3(2, 2, 2), glm::vec3(0.6, 0.6, 0.6), true);
	TexturedModel grassModel(OBJloader::load("res/objs/grassModel.obj"), Loader::loadTexture2D("res/textures/grassTexture.png", true), glm::vec3(0.9, 0.9, 0.9), glm::vec3(2, 2, 2), glm::vec3(0.6, 0.6, 0.6), true);
	
	Light light(glm::vec3(0,1000,-1000), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(0.5, 0.5, 0.5));
	Terrain terrain1(0, 0, Loader::loadTexture2D("res/textures/blendMap.png"), glm::vec3(0.9, 0.9, 0.9), glm::vec3(0.3, 0.3, 0.3), glm::vec3(0.6, 0.6, 0.6));
	Water water(glm::vec3(70, -33, 70), glm::vec3(0.9, 0.9, 0.9), glm::vec3(0.3, 0.3, 0.3), glm::vec3(0.6, 0.6, 0.6));
	water.addTextures(waterFrameBuffer, Loader::loadTexture2D("res/textures/water_textures/waterDUDV.png"), Loader::loadTexture2D("res/textures/water_textures/water_new_height.png"));
	GUI gui(glm::vec3(-0.5, 0.5, 0), glm::vec3(0.4), waterFrameBuffer.getRefractionTexture());
	GUI gui1(glm::vec3(0.5, 0.5, 0), glm::vec3(0.4), waterFrameBuffer.getReflectionTexture());

	Player player;
	Camera camera(display.getAspectRatio());
	glm::vec3 playerPosition(player.getTransform().getPosition());
	SpotLight spotLight(playerPosition + glm::vec3(0, 0.1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, 1), 8, 20);
	
	camera.init();

	glm::ivec2 mouseLocation;
	std::map<int, bool> keyPress;

	std::list<Entity> trees;
	std::list<Entity> ferns;
	std::list<Entity> grass;
	Entity barrelEntity(Entity(glm::vec3(44, 20, 30), glm::vec3(0, 0, 0), glm::vec3(0.5, 0.5, 0.5)));
	Entity boulderEntity(Entity(glm::vec3(39, 20, 20), glm::vec3(0, 0, 0), glm::vec3(0.5, 0.5, 0.5)));
	Entity crateEntity(Entity(glm::vec3(19, 20, 20), glm::vec3(0, 0, 0), glm::vec3(0.02, 0.02, 0.02)));

	//camera.setPosition(glm::vec3(player.getTransform().getPosition().x, 8, player.getTransform().getPosition().z - 20));
	//camera.setTPPForward(player.getTransform().getPosition());

	for (int i = 0; i < 100; ) {
		float x = (rand() % 1600);
		float z = rand() % 1600;
		float height = terrain1.getHeight(x, z);
		if (height < -25)
			continue;
		trees.push_back(Entity(glm::vec3(x, height, z), glm::vec3(0,0,0), glm::vec3(4,4,4)));
		i++;
	}

	for (int i = 0; i < 100;) {
		float x = (rand() % 1600);
		float z = rand() % 1600;
		float height = terrain1.getHeight(x, z);
		if (height > -30 && height < 22) {
			ferns.push_back(Entity(glm::vec3(x, height, z), glm::vec3(0, 0, 0), glm::vec3(2, 2, 2)));
			i++;
		}
	}

	/*for (int i = 0; i < 100; i++) {
		int x = (rand() % 1200);
		int z = rand() % 1200;
		grass.push_back(Entity(glm::vec3(x, 0, z), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));
	}*/

	//masterRenderer.addEntitiy(&texturedModel, entity);
	//masterRenderer.addTerrain(terrain2);

	masterRenderer.addTerrain(terrain1);
	waterRenderer.addWater(water);
	guiRenderer.addGui(gui);
	guiRenderer.addGui(gui1);

	float counter = 0;
	while (!display.isClosed()) {
		masterRenderer.addEntity(&playerModel, player);
		masterRenderer.addEntities(&treeModel, trees);
		masterRenderer.addEntities(&fernModel, ferns);
		masterRenderer.addEntities(&grassModel, grass);
		masterRenderer.addNormalMapEntity(&barrelModel, barrelEntity);
		masterRenderer.addNormalMapEntity(&boulderModel, boulderEntity);
		masterRenderer.addNormalMapEntity(&crateModel, crateEntity);

		barrelEntity.getTransform().getRotation().y += 0.001;
		boulderEntity.getTransform().getRotation().y += 0.001;
		crateEntity.getTransform().getRotation().y += 0.001;

		if (camera.isFirstPerson()) {
			camera.move(4, display, keyPress);
			//camera.changeCameraMod();
		}
		else {
			player.move(0.006, keyPress, terrain1);
			camera.move(player, display, keyPress);
		}

		glm::vec3 playerPosition(player.getTransform().getPosition());
		spotLight.setPosition(playerPosition + glm::vec3(0, 5, 0));

		glEnable(GL_CLIP_DISTANCE0);
		waterFrameBuffer.bindRefractionBuffer();
		masterRenderer.render(camera, light, spotLight, glm::vec4(0, -1, 0, water.getPos().y));
		waterFrameBuffer.unbindRefractionBuffer(display);

		waterFrameBuffer.bindReflectionBuffer();
		float distance = 2 * (camera.getPostion().y - water.getPos().y);
		camera.getPostion().y -= distance;
		camera.invertPitch();
		masterRenderer.render(camera, light, spotLight, glm::vec4(0, 1, 0, -water.getPos().y + 1));
		camera.getPostion().y += distance;
		camera.invertPitch();
		waterFrameBuffer.unbindReflectionBuffer(display);
		glDisable(GL_CLIP_DISTANCE0);

		masterRenderer.render(camera, light, spotLight, glm::vec4(0));
		waterRenderer.render(camera, light);
		//guiRenderer.render();

		display._update();


		while (SDL_PollEvent(&eventSDL)) {
			if (eventSDL.type == SDL_QUIT)
				display.close();
			if (eventSDL.type == SDL_KEYDOWN)
				keyPress[eventSDL.key.keysym.sym] = true;
			if (eventSDL.type == SDL_KEYUP)
				keyPress[eventSDL.key.keysym.sym] = false;
			if (eventSDL.type == SDL_MOUSEBUTTONDOWN) {
				keyPress[eventSDL.button.button] = true;
				if (eventSDL.button.button == SDL_BUTTON_RIGHT) {
					SDL_ShowCursor(SDL_DISABLE);
					SDL_WarpMouseInWindow(display.getWindow(), display.getLegth() / 2, display.getWidth() / 2);
				}
			}
			if (eventSDL.type == SDL_MOUSEBUTTONUP) {
				keyPress[eventSDL.button.button] = false;
				if (eventSDL.button.button == SDL_BUTTON_RIGHT) {
					SDL_ShowCursor(SDL_ENABLE);
				}
			}
		}

		
		/*if (keyPress[SDLK_UP]) {
			camera.rotateY(-0.1f);
		}
		if (keyPress[SDLK_DOWN]) {
			camera.rotateY(0.1f);
		}
		if (keyPress[SDLK_LEFT]) {
			camera.rotateX(0.1f);
		}
		if (keyPress[SDLK_RIGHT]) {
			camera.rotateX(-0.1f);
		}*/
		//system("pause");
		counter += 0.004;
		masterRenderer.cleanEntities();
	}

	waterFrameBuffer.clean();
	display._clean();
	//shader.clean();
	//entity.getModel().getModel().clean();

	return 0;
}