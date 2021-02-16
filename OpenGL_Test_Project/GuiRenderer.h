#pragma once
#include "GuiShader.h"
#include "Camera.h"
#include "GUI.h"

#include <map>
#include <list>

class GuiRenderer
{
public:
	GuiRenderer();
	~GuiRenderer() {};

	void render();
	void addGui(GUI& gui);

private:
	void initTexturedModel(GUI& terrain);
	void initInstance(GUI& water);
	void unbindTexturedModel(GUI& terrain);

	GuiShader guiShader;
	std::list<GUI> guis;
};

