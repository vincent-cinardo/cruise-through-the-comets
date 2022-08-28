#include "Camera.h"

//Camera positioned to -3 by default
Camera::Camera() 
{
	view = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 3.0f), 
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	std::cout << glm::to_string(view) << std::endl;
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

//Must be called to set the projection matrix in shader.
void Camera::ZoomOrtho(float width, float height, unsigned int shaderProgram)
{
	glm::mat4 projection = glm::ortho(width / 2, width / 2, height / 2, height / 2, 0.0f, 10.0f);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

//Must be called to set the view matrix in shader; translates the view matrix.
void Camera::View(float x, float y, unsigned int shaderProgram)
{
	view = glm::translate(view, glm::vec3(x, y, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
}