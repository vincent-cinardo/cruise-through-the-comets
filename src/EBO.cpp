#include "EBO.h"

EBO::EBO()
{
	
}

EBO::EBO(int* data, unsigned int size)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	indices = new int[size];
	memcpy(indices, data, size);
}

EBO::~EBO()
{
	glDeleteBuffers(1, &id);
	if (indices != NULL)
	{
		delete[] indices;
	}
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}


void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int EBO::GetCount()
{
	return sizeof(indices);
}