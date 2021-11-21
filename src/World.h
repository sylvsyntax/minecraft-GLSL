#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include "Chunk.h"

class World
{
public:
	const GLuint TOTAL_CHUNKS = 2;

	vector<Block> allBlockTypes;
	vector<Texture> allTextures;

	vector<Chunk> loadedChunks;
	vector<Chunk> unloadedChunks;
	World(string textureFolder);

	void generateWorldSpawn();
};

#endif