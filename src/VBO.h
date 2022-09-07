#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class VBO
{
public:
	VBO(const void* data, unsigned int size);
	~VBO();
	void Bind();
	void Unbind();
	
private:
	unsigned int id;
};

