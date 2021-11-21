#ifndef BLOCK_CLASS_H
#define BLOCK_CLASS_H

#include "Mesh.h"

class Block
{
public:
	
	glm::vec3 position;
	Mesh& mesh;

	Block(Mesh& mesh);
	Block(Block blockType, glm::vec3 position);

};

#endif