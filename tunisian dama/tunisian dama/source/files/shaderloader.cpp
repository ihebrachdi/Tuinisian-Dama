#include"shaderloader.h"
#include<glew.h>
#include<string>
#include<fstream>
#include<sstream>
#include"../Log.h"

#define VERTEX  0
#define FRAGMENT  1

namespace imatics {
	//this function doesn't care about the order as long as you declare #vertex #fragment int the files
	pairstr VFloader(const std::string& filepath, const std::string& filepath2) {

		std::string file1;
		std::string file2;

		std::ifstream stream[2];
		stream[0].open(filepath);
		stream[1].open(filepath2);
		std::string line;

		std::stringstream sstring[2];

		getline(stream[0], line);
		for (int i = 0; i < 2; i++) {
			if (line.find("#vertex") != std::string::npos) {

				sstring[VERTEX] << stream[i].rdbuf();
				file1 = sstring[VERTEX].str();

				if (i == 0)
					getline(stream[1], line);
			}
			else if (line.find("#fragment") != std::string::npos) {
				sstring[FRAGMENT] << stream[i].rdbuf();
				file2 = sstring[FRAGMENT].str();
				if (i == 0)
					getline(stream[1], line); // to handel if the first path is fragement so we need to delete the #vertex frome 2th file
			}
			else {
				Log("the required shader file doesn't exist check again");
				i = 2;
			}
		}

		stream[0].close();
		stream[1].close();

		return { file1 , file2 };
	}
}