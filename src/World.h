//
//  World.hpp
//  Minecraft-GLSL
//
//  Created by Sylvia Sharpe on 12/2/21.
//

#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include <stdio.h>
#include "Mesh.h"

class World
{
public:
    World();
    std::vector<Mesh> sceneMeshes;
    std::vector<Mesh> sceneLights;
    Shader shaderProgram;
    Shader lightShader;
};

#endif /* World_hpp */
