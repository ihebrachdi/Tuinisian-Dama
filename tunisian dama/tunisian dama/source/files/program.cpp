#include <glew.h>
#include"program.h"
#include"shaderloader.h"

#include"..\Log.h"


namespace imatics {
	static unsigned int compileshader(const char* shader, unsigned int type, unsigned int idp) {
		unsigned int id = glCreateShader(type);
		
		glShaderSource(id, 1, &shader, nullptr);
		glCompileShader(id);
		//handle error
		int good;
		glGetShaderiv(id, GL_COMPILE_STATUS, &good);
		if (!good) {
			int len;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
			char* info = (char*)alloca(len * sizeof(char));
			//char* info = new char[len];
			glGetShaderInfoLog(id, len, &len, info);
			Log("problem in compilation");
			Log(info);
		}
		glAttachShader(idp, id);
		return id;
	}
	program::program(const std::string& vertex, const std::string& fragment) {
		pairstr vf = VFloader(vertex, fragment);
		m_id = glCreateProgram();
		unsigned int idv = compileshader(vf.str1.c_str(), GL_VERTEX_SHADER, m_id);
		unsigned int idf = compileshader(vf.str2.c_str(), GL_FRAGMENT_SHADER, m_id);
		glLinkProgram(m_id);
		glValidateProgram(m_id);
		glDeleteShader(idv);
		glDeleteShader(idf);
	}
	void program::use(bool bind) {
		if (bind) {
			glUseProgram(m_id);
			m_bind = true;
		}
		else {
			glUseProgram(0);
			m_bind = false;
		}
	}
	unsigned int program::findlocation(const char* name) {
		return glGetUniformLocation(m_id, name);
	}

	void program::draw(size_t nbr_triangle) {
		if (m_bind) {
			glDrawElements(GL_TRIANGLES, 3 * nbr_triangle, GL_UNSIGNED_INT, (void*)0);
		}
		else {
			use(true);
			glDrawElements(GL_TRIANGLES, 3 * nbr_triangle, GL_UNSIGNED_INT, (void*)0);
		}
	}
	program::~program() {
		glDeleteProgram(m_id);
	}

}
