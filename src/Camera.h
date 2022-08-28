#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera();
	Camera(float x, float y, float z);
	~Camera();
	void Move(float x, float y, float z);
private:
	glm::mat4 view;
};

