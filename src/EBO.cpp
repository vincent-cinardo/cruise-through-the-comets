#include "EBO.h"

EBO::EBO()
{

}

EBO::EBO(const void* data, unsigned int size)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	indices = (int*)malloc(size);
	memcpy(indices, data, size);
}

EBO::~EBO()
{
	glDeleteBuffers(1, &id);
	free(indices); //Why isn't this working?
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
