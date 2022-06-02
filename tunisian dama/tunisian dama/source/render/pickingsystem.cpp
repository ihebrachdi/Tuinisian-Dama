#include<glew.h>
#include"pickingsystem.h"
#include"../Log.h"


namespace imatics {
	picking::picking(vec2 dimport) {
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		glGenTextures(1, &m_tbo);
		glBindTexture(GL_TEXTURE_2D, m_tbo);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, dimport.x, dimport.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_tbo, 0);
		GLenum statusinfo = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		
		if (statusinfo != GL_FRAMEBUFFER_COMPLETE) {
			Log("ERROR::FRAMEBUFFER::Not Complete : " << statusinfo);
		}
		
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		
	}

	void picking::bind(vec3 backgroundcolor) {
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		glClearColor(backgroundcolor.x, backgroundcolor.y, backgroundcolor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

	}

	void picking::unbind(vec3 Defaultbackgroundcolor) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(Defaultbackgroundcolor.x, Defaultbackgroundcolor.y, Defaultbackgroundcolor.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}


	vec3 picking::readpixel(double x_mouse, double y_mouse ,int height) {
		vec3 rgb;

		glReadBuffer(GL_COLOR_ATTACHMENT0);
		glReadPixels(x_mouse, height - y_mouse, 1, 1, GL_RGB, GL_FLOAT, &rgb);
		glReadBuffer(GL_NONE);
		m_lastpickedindex = (int)(rgb.y*100.0f);
		
		return rgb;

	}
}