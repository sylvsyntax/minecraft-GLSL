#ifndef VBO_CLASS_H
#define VBO_CLASS_H

// Most of this class was provided from an OpenGL tutorial
// https://youtu.be/45MIykWJ-C4

#include <glm/glm.hpp>

#include <glad/glad.h>
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normals;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO
{
public:
	GLuint ID;

	VBO(std::vector<Vertex>& vertices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif /* VBO_CLASS_H */
