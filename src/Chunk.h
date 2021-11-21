#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include "Block.h"

class Chunk
{
public:
	const GLuint CHUNK_SIZE = 8;
	// https://stackoverflow.com/a/7367817
	// 1D to 3D 
	// Flat[x + WIDTH * (y * DEPTH * z)] = x,y,z
	vector<Block> blocks;
	glm::vec2 position;
	
	Chunk();
};

#endif