#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

//Matrix/vector math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma once
class Shader
{
public:
	Shader();
	Shader(const char* vertSrc, const char* fragSrc);
	~Shader();
	void Use();
	void SetModel(float x, float y);
	unsigned int GetProgram();
	Shader& SetMat4(const char* name, glm::mat4 matrix);
	void SetInteger(const char* name, unsigned int value);
	unsigned int shaderProgram;
	
private:
	unsigned int vertShader, fragShader;
};

