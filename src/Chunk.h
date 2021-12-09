#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include "Block.h"
#include "Mesh.h"
#include "PerlinNoise.h"

class Chunk
{
public:
	static const int CHUNK_SIZE = 8;
	static const int MAX_HEIGHT = 30;
	// https://stackoverflow.com/a/7367817
	// 1D to 3D 
	// Flat[x + WIDTH * (y * DEPTH * z)] = x,y,z
	int blocks[CHUNK_SIZE][MAX_HEIGHT][CHUNK_SIZE];
	glm::ivec2 position;
	
	Chunk() = default;
	Chunk(int x, int y);
    vec3 getTop(int x, int y);
    vec3 getLocalTop(int x, int y);
};

#endif
