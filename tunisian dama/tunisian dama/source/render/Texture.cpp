#include"Texture.h"
#include"../Log.h"


namespace imatics {
	texture::texture(int location,size_t size) :m_size(size),m_samplerloc(location) {
		m_tbo = new unsigned int[size];
		m_unit = new int[size];
	}

	void texture::addtexture(const char* path ,size_t unit) {
		if (m_count >= m_size) {
			Log("you can't load more texture in this instance");
		}
		else {

			int widht;
			int hight;
			int channels;
			stbi_set_flip_vertically_on_load(1);
			unsigned char* data = stbi_load(path, &widht, &hight, &channels, 4);
			m_count++;

			glGenTextures(1, &m_tbo[m_count-1]);//coz m_count start from 1
			//glBindTexture(GL_TEXTURE_2D,m_tbo[m_count - 1]);
			bind(unit, true);
			m_unit[m_count - 1] = unit;
			

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			
			if (data) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, widht, hight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
				
				if (m_count == m_size) {

					switch (m_size) {
						case 1: glUniform1i(m_samplerloc, m_unit[m_count - 1]);
							break;
						case 2: glUniform1iv(m_samplerloc, 2, m_unit);
							break;
						case 3: glUniform1iv(m_samplerloc, 3, m_unit);
							break;
						case 4: glUniform1iv(m_samplerloc, 4, m_unit);
							break;
						case 5: glUniform1iv(m_samplerloc, 5, m_unit);
							break;
						case 6: glUniform1iv(m_samplerloc, 6, m_unit);
							break;
						case 7: glUniform1iv(m_samplerloc, 7, m_unit);
							break;
						case 8: glUniform1iv(m_samplerloc, 8, m_unit);
							break;
						default:
							Log("you can't pass more than 8ui to the sampler ");
					}
				}
				
			}
			else {
				Log("ERROR: cann't load texture of path : " << path);
			}
			//glBindTexture(GL_TEXTURE_2D, 0);
			Log(m_unit[m_count - 1]);
			//bind(0, false);
		}
	}
	void texture::bind(unsigned int unit,bool BIND  ){
		if (BIND) {
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_2D, m_tbo[unit]);//here exist a mistake
		}
		else {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	}

}