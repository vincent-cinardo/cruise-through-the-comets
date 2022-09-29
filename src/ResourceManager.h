#pragma once
#include <map>
#include <glad/glad.h>
#include <iostream>
#include "Shader.h"
#include "Texture.h"

class ResourceManager
{
public:
	static Shader LoadShader(const char* vshader, const char* fshader, std::string name);
	static Shader GetShader(std::string name);
	static Texture LoadTexture(const char* file, bool alpha, std::string name);
	static Texture& GetTexture(std::string name);
	static void Clear();
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture> textures;

private:
	ResourceManager() {}
	static Shader loadShaderFromFile(const char* vshader, const char* fshader);
	static Texture loadTextureFromFile(const char *file, bool alpha);

};

