#pragma once
#include "FrameBufferObject.h"
#include "Texture.h"

class WaterFrameBuffer
{
public:
	WaterFrameBuffer(const int& reflWidth, const int& reflHeight, const int& refrWidth, const int& refrHeight, Display& display);
	~WaterFrameBuffer();

	void bindReflectionBuffer();
	void bindRefractionBuffer();
	void unbindReflectionBuffer(Display& display);
	void unbindRefractionBuffer(Display& display);
	void clean();

	FrameBufferObject& getReflectionFrameBuffer() { return reflectionFrameBuffer; }
	FrameBufferObject& getRefractionFrameBuffer() { return refractionFrameBuffer; }
	Texture& getReflectionTexture() { return reflectionTexture; }
	Texture& getRefractionTexture() { return refractionTexture; }
	Texture& getRefractionDepthTexture() { return refractionDepthTexture; }

private:
	FrameBufferObject reflectionFrameBuffer;
	FrameBufferObject refractionFrameBuffer;
	Texture reflectionTexture;
	Texture refractionTexture;
	Texture refractionDepthTexture;
	
	int reflectionWidth;
	int reflectionHeight;
	int refractionWidth;
	int refractionHeight;
};

