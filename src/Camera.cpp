#include "Camera.h"-

//Camera positioned to -3 by default
Camera::Camera() 
{
	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -4.0f));
	fov = 90.0f;
	projection = glm::perspective(fov, 1920.0f/1080.0f, 0.1f, -8.0f);
}

Camera::Camera(glm::mat4 view, glm::mat4 projection)
{
	this->view = view;
	this->projection = projection;
	fov = 90.0f;
}

//Specify a camera at a certain position
Camera::Camera(float x, float y, float z)
{
	view = glm::lookAt(
		glm::vec3(x, y, z),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	projection = glm::perspective(30.0f, 1920.0f/1080.0f, 0.1f, -8.0f);
}

Camera::~Camera() {}

void Camera::Move(float x, float y, float z)
{
	view = glm::translate(view, glm::vec3(-x, -y, -z));
}

//Must be called to set the projection matrix in shader.
void Camera::Zoom(float fovAmt, float aspect, unsigned int shaderProgram)
{
	this->fov += fovAmt;

	glm::mat4 projection = glm::perspective(
		this->fov, aspect, 0.1f, 30.0f
	);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

//Must be called to set the view matrix in shader; translates the view matrix.
void Camera::View(float x, float y, unsigned int shaderProgram)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
}

void Camera::Aspect(float x, float y)
{
	x = x > 0 ? x : 0.1;
	y = y > 0 ? y : 0.1;
	projection = glm::perspective(fov, x / y, 0.1f, -8.0f);
}