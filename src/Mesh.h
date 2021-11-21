#ifndef MESH_CLASS_H
#define MESH_CLASS_H

// Starting of this class was provided from an OpenGL tutorial
// https://youtu.be/45MIykWJ-C4?t=5117

#include <string>

#include "VAO.h"
#include "EBO.h"
#include "Camera.h"
#include "Texture.h"

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;


	VAO VAO;

	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

	void Draw(Shader& shader, Camera& camera);
};


#endif