#include "ResourceManager.h"

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture> ResourceManager::textures;

Shader ResourceManager::LoadShader(const char* vshader, const char* fshader, std::string name)
{
	shaders[name] = loadShaderFromFile(vshader, fshader);
	return shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
	return shaders[name];
}

Texture ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
	textures[name] = loadTextureFromFile(file, alpha);
	return textures[name];
}

Texture& ResourceManager::GetTexture(std::string name)
{
	return textures[name];
}

Shader ResourceManager::loadShaderFromFile(const char* vshader, const char* fshader)
{
	Shader shader(vshader, fshader);
	return shader;
}

Texture ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
	Texture texture(file, alpha);
	return texture;
}

//Deletes shader programs and all their corresponding shaders. Also deletes all textures.
void ResourceManager::Clear()
{
	for (auto shader : shaders)
	{
		glDeleteProgram(shader.second.shaderProgram);
	}
	for (auto texture : textures)
	{
		glDeleteTextures(1, &texture.second.texture);
	}
}