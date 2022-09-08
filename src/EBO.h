#pragma once
#include <iostream>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class EBO
{
public:
	EBO();
	EBO(int* data, unsigned int size);
	~EBO();
	void Bind();
	void Unbind();
	int GetCount();
	int* indices;

private:
	unsigned int id;
};

