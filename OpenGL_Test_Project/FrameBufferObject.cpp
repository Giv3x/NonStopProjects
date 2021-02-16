#include "FrameBufferObject.h"


void FrameBufferObject::init(const int& attachLevel) {
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glDrawBuffer(GL_COLOR_ATTACHMENT0 + attachLevel);
}

void FrameBufferObject::initDepthBufferAttach(int& width, int& height) {
	glGenRenderbuffers(1, &renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
}

void FrameBufferObject::bind(int& width, int& height) {
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glViewport(0, 0, width, height);
}

void FrameBufferObject::unbind(Display& display) {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, display.getLegth(), display.getWidth());
}

void FrameBufferObject::clean() {
	glDeleteFramebuffers(1, &frameBuffer);
	glDeleteRenderbuffers(1, &renderBuffer);
}