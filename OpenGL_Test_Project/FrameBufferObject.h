#pragma once
#include <GL\glew.h>

#include "Display.h"

class FrameBufferObject
{
public:
	FrameBufferObject() {}
	~FrameBufferObject() {}

	GLuint getFrameBuffer() { return frameBuffer; }
	void bind(int& width, int& height);
	void unbind(Display& display);
	void init(const int& attachLevel);
	void initDepthBufferAttach(int& width, int& height);
	void clean();

private:
	GLuint frameBuffer;
	GLuint renderBuffer;
};

