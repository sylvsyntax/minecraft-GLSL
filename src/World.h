//
//  World.hpp
//  Minecraft-GLSL
//
//  Created by Sylvia Sharpe on 12/2/21.
//

#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include "Mesh.h"
#include "Chunk.h"
#include "Cube.h"
class World
{
public:
    World();
    LightingCube sun;
    std::vector<Mesh> sceneMeshes;
    std::vector<Mesh> sceneLights;
    std::vector<vector<Chunk>> chunks;
    Shader shaderProgram;
    Shader lightShader;
};

#endif /* World_hpp */
