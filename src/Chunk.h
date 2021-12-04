#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include "Cube.h"

class Chunk
{
public:
	static const int CHUNK_SIZE = 8;
	static const int MAX_HEIGHT = 25;
	// https://stackoverflow.com/a/7367817
	// 1D to 3D 
	// Flat[x + WIDTH * (y * DEPTH * z)] = x,y,z
	Cube blocks[CHUNK_SIZE][MAX_HEIGHT][CHUNK_SIZE];
	glm::vec2 position;
	
	Chunk(int x, int y);
};

#endif
