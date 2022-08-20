#include <iostream>
#include <fstream>
#include <sstream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#pragma once
class Shader
{
public:
	Shader();
	Shader(const char* vertSrc, const char* fragSrc);
	~Shader();
	void Use();
	
private:
	unsigned int vertShader, fragShader, shaderProgram;
};

