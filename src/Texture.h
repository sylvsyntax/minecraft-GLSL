#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

// Most of this class was provided from an OpenGL tutorial
// https://youtu.be/45MIykWJ-C4

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <map>

#include "shaderClass.h"

class Texture
{
public:
	GLuint ID;
	const char* type;
	GLuint unit;

	Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
    static map<const char*, GLuint> idMap;
	void Bind();
	void Unbind();
	void Delete();
};

#endif /* TEXTURE_CLASS_H */
