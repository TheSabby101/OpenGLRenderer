#pragma once
#include "Header.h"
#include "res/3rd party/stb_image.h"


class Textures
{
private:
	unsigned int ID;
	std::string Filepath;
	unsigned char* LocalBuffer;
	int Width, Height, BBP;
	//unsigned char* LocalBuffer = new unsigned char;
public:

	Textures(const std::string& path);
	~Textures();

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

};