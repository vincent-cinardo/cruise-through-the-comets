#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class EBO
{
public:
	EBO();
	EBO(const void* data, unsigned int size);
	~EBO();
	void Bind();
	void Unbind();
	int GetCount();
	int* indices;

private:
	unsigned int id;
};

