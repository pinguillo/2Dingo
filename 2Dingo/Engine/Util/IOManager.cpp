#include "IOManager.h"
#include <fstream>

bool IOManager::ReadFileToBuffer(std::string filepath, std::vector<unsigned char>& buffer)
{
	std::ifstream file(filepath, std::ios::binary);
	if (file.fail())
	{
		perror(filepath.c_str());
		return false;
	}

	//File size
	file.seekg(0, std::ios::end);
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);
	//Reduce size by header size
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char*)&(buffer[0]), fileSize);
	file.close();

	return true;
}
