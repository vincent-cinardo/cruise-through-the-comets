#include "VBO.h"

VBO::VBO()
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

//Creates a vertex buffer object of a fixed size.
VBO::VBO(const void* data, unsigned int size)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

//Creates a vertex buffer object that can be used dynamically, 1KB.
VBO::VBO(const void* data)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_DYNAMIC_DRAW);
}

VBO::~VBO() 
{
	glDeleteBuffers(1, &id);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}


void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

