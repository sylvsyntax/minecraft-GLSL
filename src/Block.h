//
//  Block.hpp
//  Minecraft-GLSL
//
//  Created by Sylvia Sharpe on 12/3/21.
//


#ifndef BLOCK_CLASS_H
#define BLOCK_CLASS_H

#include "Mesh.h"
#include "shapes.h"
#include "Cube.h"

enum blockType {
    air = -1, dirt = 0, stone = 1, grass = 2,
};

class Block
{
public:
    Block();
    
    Block(vec3 pos, Cube cube, blockType type);
    
    
    vec3 pos;
    Cube buildCube;
    blockType type;
    
    void buildBlock();
};


#endif /* Block_hpp */
