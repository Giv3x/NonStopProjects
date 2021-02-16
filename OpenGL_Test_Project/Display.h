#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <iostream>
#include <SDL2\SDL.h>
#include <GL\glew.h>

class Display
{
public:
	Display();
	Display(float l, float w, const std::string& n);
	~Display();

	void set(float l, float w, const std::string& n);
	void close() { closed = true; }
	bool isClosed() { return closed; }
	
	void _init();
	void _update();
	void _clean();
	
	float getAspectRatio() { return aRatio; }
	float getWidth() { return width; }
	float getLegth() { return length; }
	SDL_Window* getWindow();
private:
	float length;
	float width;
	float aRatio;
	bool closed;
	std::string name;

	SDL_Window *window;
	SDL_GLContext glContext;
};

#endif