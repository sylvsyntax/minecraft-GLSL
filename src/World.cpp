#include "World.h"

#include <filesystem>

World::World(string texturesFolder)
{

	// to enumerate over all files in a directory
	//https://stackoverflow.com/a/612176
	int i = 0;
	for (const auto& entry : filesystem::directory_iterator(texturesFolder))
	{
		allTextures.push_back(Texture(entry.path().string().c_str(), "diffuse", i++, GL_RGBA, GL_UNSIGNED_BYTE));
	}

	// 1. generate mesh based off of texture
	// 2. create block type from mesh
	// 3. add to all block types
}