#include "Renderer.h"

Renderer::Renderer() {}

Renderer::Renderer(Shader *shader) {}

void Renderer::Draw(Texture& texture, glm::vec3 position)
{
	shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	shader.SetMat4("model", model);

	glActiveTexture(GL_TEXTURE0);
	texture.Use();
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::Draw(Texture& texture, glm::vec3 position, float angle)
{
	shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	shader.SetMat4("model", model);

	glActiveTexture(GL_TEXTURE0);
	texture.Use();
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}