#include "Display.h"


Display::Display() {
}

Display::Display(float l, float w, const std::string& n) {
	length = l;
	width = w;
	name = n;
	aRatio = l / w;
	closed = true;
}

Display::~Display() {
}

void Display::set(float l, float w, const std::string& n) {
	length = l;
	width = w;
	name = n;
	aRatio = l / w;
	closed = true;
}

void Display::_init() {
	closed = false;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 64);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)length, (int)width, SDL_WINDOW_OPENGL);

	glContext = SDL_GL_CreateContext(window);

	GLenum status = glewInit();

	if (status != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(status));
	}

	glEnable(GL_DEPTH_TEST);
}

void Display::_clean() {
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Display::_update() {
	SDL_GL_SwapWindow(window);
}

SDL_Window* Display::getWindow() {
	return window;
}