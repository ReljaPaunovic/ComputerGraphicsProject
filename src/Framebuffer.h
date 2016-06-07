#pragma once

#include <GL/freeglut.h>

struct Framebuffer {
	GLuint fbo;
	GLuint colorTexture;

	Framebuffer() : fbo(0), colorTexture(0) {}

	Framebuffer(int width, int height) {
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		// Create texture to hold color buffer
		glGenTextures(1, &colorTexture);
		glBindTexture(GL_TEXTURE_2D, colorTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Create renderbuffer for depth buffer
		GLuint rboDepthStencil;
		glGenRenderbuffers(1, &rboDepthStencil);
		glBindRenderbuffer(GL_RENDERBUFFER, rboDepthStencil);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepthStencil);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
};
