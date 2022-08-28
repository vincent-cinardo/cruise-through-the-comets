#include "Shader.h"

Shader::Shader()
{

}

Shader::Shader(const char* vertSrc, const char* fragSrc)
{
	std::ifstream vertFile(vertSrc);

	if (!vertFile.is_open())
	{
		std::cout << "Cannot open " << vertSrc << std::endl;
		return;
	}

	std::ifstream fragFile(fragSrc);

	if (!fragFile.is_open())
	{
		std::cout << "Cannot open " << fragSrc << std::endl;
		vertFile.close();
		return;
	}

	std::stringstream vertStream, fragStream;
	vertStream << vertFile.rdbuf();
	fragStream << fragFile.rdbuf();

	std::string vertBuff, fragBuff;
	vertBuff = vertStream.str();
	fragBuff = fragStream.str();
	const char* vertCode = vertBuff.c_str();
	const char* fragCode = fragBuff.c_str();

	int success;
	char infoLog[512];

	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertCode, NULL);
	glCompileShader(vertShader);
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	
	if (!success)
	{
		glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
		std::cout << "ERROR: Vertex shader compilation failed - " << infoLog << std::endl;
	}

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragCode, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		std::cout << "ERROR: Fragment shader compilation failed - " << infoLog << std::endl;
	}

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR: Program did not link correctly - " << infoLog << std::endl;
	}
}

void Shader::Use()
{
	//Maybe set the texture mode here?
	glUseProgram(shaderProgram);
}

//Sets the model uniform in the currently bound vertex shader.
void Shader::SetModel(float x, float y)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(x, y, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
}

Shader::~Shader()
{
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

unsigned int Shader::GetProgram()
{
	return shaderProgram;
}

/*Shader::setMat4()
{

}*/

//Shader::setInt(const char *name);