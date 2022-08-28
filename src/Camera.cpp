#include "Camera.h"

//Camera positioned to -3 by default
Camera::Camera() 
{
	view = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 3.0f), 
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}

//Specify the position of the camera
Camera::Camera(float x, float y, float z)
{
	view = glm::lookAt(
		glm::vec3(x, y, z),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
}

Camera::~Camera()
{

}

void Camera::Move(float x, float y, float z)
{
	glm::translate(view, glm::vec3(x, y, z));
}

