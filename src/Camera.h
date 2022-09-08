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
	Camera(glm::mat4 view, glm::mat4 projection);
	Camera(float x, float y, float z);
	~Camera();
	void Move(float x, float y, float z);
	void Zoom(float fovAmt, float aspect, unsigned int shaderProgram);
	void View(float x, float y, unsigned int shaderProgram);
	glm::mat4 view;
	glm::mat4 projection;
private:
	float x, y, z;
	float fov;
};

