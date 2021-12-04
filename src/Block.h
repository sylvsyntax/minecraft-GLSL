//
//  Block.hpp
//  Minecraft-GLSL
//
//  Created by Sylvia Sharpe on 12/3/21.
//


#ifndef BLOCK_CLASS_H
#define BLOCK_CLASS_H

#include "Cube.h"

class Block
{
public:
    Block();
    Block(vec3 pos, blockType type);
    Block(vec3 pos, blockType type, vector<blockPos> sideExclusion);
    
    //Front,Bottom, Top,    Back,   Left,   Right
    //0     1,      2,      3,      4,      5
    vector<blockPos> sideExclusion;
    vec3 pos;
    Cube buildCube();
    blockType type;
    
    Cube buildBlock();
};


#endif /* Block_hpp */
