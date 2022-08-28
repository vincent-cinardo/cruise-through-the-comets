#pragma once
#include <iostream>
#include "glad/glad.h"
#include "glfw/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

class Camera
{
public:
	Camera();
	Camera(float x, float y, float z);
	~Camera();
	void Move(float x, float y, float z);
	void ZoomOrtho(float width, float height, unsigned int shaderProgram);
	void View(float x, float y, unsigned int shaderProgram);
private:
	glm::mat4 view;
	float x, y, z;
};

