#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include "Cube.h"

class Chunk
{
public:
	const int CHUNK_SIZE = 8;
	const int MAX_HEIGHT = 25;
	// https://stackoverflow.com/a/7367817
	// 1D to 3D 
	// Flat[x + WIDTH * (y * DEPTH * z)] = x,y,z
	vector<Cube> blocks;
	glm::vec2 position;
	
	Chunk(int x, int y);
};

#endif