#include "WaterFrameBuffer.h"



WaterFrameBuffer::WaterFrameBuffer(const int& reflWidth, const int& reflHeight, const int& refrWidth, const int& refrHeight, Display& display)
		: reflectionWidth(reflWidth), reflectionHeight(reflHeight), refractionHeight(refrHeight), refractionWidth(refrWidth) {
	reflectionFrameBuffer.init(0);
	reflectionTexture.initTextureAttachment(reflectionWidth, reflectionHeight, 0);
	reflectionFrameBuffer.initDepthBufferAttach(reflectionWidth, reflectionHeight);
	reflectionFrameBuffer.unbind(display);

	refractionFrameBuffer.init(0);
	refractionTexture.initTextureAttachment(refractionWidth, refractionHeight, 0);
	refractionDepthTexture.initTextureDepthAttachment(refractionWidth, refractionHeight);
	refractionFrameBuffer.unbind(display);
}

void WaterFrameBuffer::bindReflectionBuffer() {
	reflectionFrameBuffer.bind(reflectionWidth, reflectionHeight);
}

void WaterFrameBuffer::bindRefractionBuffer() {
	refractionFrameBuffer.bind(refractionWidth, refractionHeight);
}

void WaterFrameBuffer::unbindReflectionBuffer(Display& display) {
	reflectionFrameBuffer.unbind(display);
}

void WaterFrameBuffer::unbindRefractionBuffer(Display& display) {
	refractionFrameBuffer.unbind(display);
}

void WaterFrameBuffer::clean() {
	reflectionFrameBuffer.clean();
	refractionFrameBuffer.clean();
	reflectionTexture.clean();
	refractionTexture.clean();
	refractionDepthTexture.clean();
}

WaterFrameBuffer::~WaterFrameBuffer() {
}
