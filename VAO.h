#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class VAO
{
public:
	VAO();
	~VAO();
	void Bind();
	void Unbind();
	void Enable(int index);

	//Set this after setting up the vertex and index buffer.
	void SetAttribute(int index, int size, int offset);

private:
	unsigned int id;
};

