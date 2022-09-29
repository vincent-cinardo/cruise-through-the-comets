#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);

}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &id);
}

void VAO::Bind()
{
	glBindVertexArray(id);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Enable(int index)
{
}

void VAO::SetAttribute(int index, int size, int offset)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, size * sizeof(float), (void*) offset);
}