#ifndef VAO_CLASS_H
#define VAO_CLASS_H

// Most of this class was provided from an OpenGL tutorial
// https://youtu.be/45MIykWJ-C4

#include "VBO.h"

class VAO
{
public: 
	GLuint ID;

	VAO();

	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();
};

#endif /* VAO_CLASS_H */