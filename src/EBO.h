#ifndef EBO_CLASS_H
#define EBO_CLASS_H

// Most of this class was provided from an OpenGL tutorial
// https://youtu.be/45MIykWJ-C4

#include <glad/glad.h>
#include <vector>

class EBO
{
public:
	GLuint ID;

	EBO(std::vector<GLuint>& indices);

	void Bind();
	void Unbind();
	void Delete();
};

#endif /* EBO_CLASS_H */