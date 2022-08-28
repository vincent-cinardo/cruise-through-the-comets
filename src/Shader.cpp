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

Shader::~Shader()
{
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

Shader::setMat4()
{

}

//Shader::setInt(const char *name);