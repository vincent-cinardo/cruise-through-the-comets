#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class EBO
{
public:
	EBO(const void* data, unsigned int size);
	~EBO();
	void Bind();
	void Unbind();

private:
	unsigned int id;
};

