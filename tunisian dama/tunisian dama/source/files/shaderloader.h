#pragma once
#include<iostream>



namespace imatics {
	struct pairstr {
		std::string str1;
		std::string str2;
	};
	pairstr VFloader(const std::string& filepath, const std::string& filepath2);
}