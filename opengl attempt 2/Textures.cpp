#include "Textures.h"




Textures::Textures(const std::string& path)
	:ID(0), Filepath(path), Width(0),Height(0),BBP(0)

	{
	//Flipping the image
	//Opengl draws from bottom left to top right, but a png reads from top left to bottom right.
	stbi_set_flip_vertically_on_load(1);

	// storing the width, height, and bytes per pixel in the class instance
	LocalBuffer = stbi_load(path.c_str(),&Width, &Height, &BBP, 4);



	//Gen one 2d texture
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	//Specifying Texture Paramaters

	//GL_LINEAR = no tiling / GL_NEAREST = tiling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocalBuffer);
	glBindTexture(GL_TEXTURE_2D,0);

	if (LocalBuffer)
		stbi_image_free(LocalBuffer);
	//std::cout << "Image Freed " << glGetError() << std::endl;
	
	}

	Textures::~Textures()
	{
		//UnBind();
		std::cout << "Texture Deleted" << std::endl;
		glDeleteTextures(1, &ID);
		//delete LocalBuffer;
	}

	void Textures::Bind(unsigned int slot) const
	{
	
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, ID);
	
	//	std::cout << "Bound Texture " << glGetError() << std::endl;
	
	}
	void Textures::UnBind() const
	{
		std::cout << "Unbound Texture" << std::endl;
		glBindTexture(GL_TEXTURE_2D, 0);

	}

