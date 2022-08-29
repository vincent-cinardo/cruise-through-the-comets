#include "Camera.h"

//Camera positioned to -3 by default
Camera::Camera() 
{
	view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
	width = 30.0f;
	height = 30.0f;
	fov = 45.0f;
	std::cout << "View: " << std::endl << glm::to_string(view) << std::endl;
}

//Specify the position of the camera
Camera::Camera(float x, float y, float z)
{
	view = glm::lookAt(
		glm::vec3(x, y, z),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	width = 30.0f;
	height = 30.0f;
}

Camera::~Camera() {}

void Camera::Move(float x, float y, float z)
{
	view = glm::translate(view, glm::vec3(-x, -y, -z));
}

//Must be called to set the projection matrix in shader.
void Camera::ZoomOrtho(float fovAmt, float aspect, unsigned int shaderProgram)
{
	//width = (width - widthAmt * aspectx > 2.0f * aspectx) ? width - widthAmt * aspecty : 16.0f;
	//height = (height - heightAmt * aspecty > 2.0f * aspecty) ? height - heightAmt * aspecty : 9.0f;

	//width = (width - widthAmt) > 2.0f ? width - widthAmt: 2.0f;
	//height = (height - heightAmt) > 2.0f ? height - heightAmt : 2.0f;

	//aspectx = (aspectx - widthAmt > 2.0f) ? aspectx - widthAmt : 2.0f;
	//aspecty = (aspecty - heightAmt > 2.0f) ? aspecty - heightAmt : 2.0f;

	this->fov += fovAmt;

	glm::mat4 projection = glm::perspective(
		this->fov, 1920.0f/1080.0f, 0.1f, 30.0f
	);

	//Previous
	/*glm::mat4 projection = glm::ortho(
		-width/2,
		width/2,
		-height/2, 
		height/2, 
		0.0f, 
		15.0f
	);*/

	//Dependent on aspect ratio
	/*glm::mat4 projection = glm::ortho(
		-aspectx / 2,
		aspectx / 2,
		-aspecty / 2,
		aspecty / 2,
		0.0f,
		15.0f
	);*/
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

//Must be called to set the view matrix in shader; translates the view matrix.
void Camera::View(float x, float y, unsigned int shaderProgram)
{
	//view = glm::translate(view, glm::vec3(x, y, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
}