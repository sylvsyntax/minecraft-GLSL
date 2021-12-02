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
    
    std::vector<Mesh> sceneMeshes;
    Shader shaderProgram("src/default.vert", "src/default.frag");
    void Define();
};

#endif /* World_hpp */
