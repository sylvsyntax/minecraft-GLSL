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
    air = -1, dirt = 0, stone = 1, grass = 2
};

enum blockPos {
    front = 0, bottom = 1, top = 2, back = 3, sideLeft = 4, sideRight = 5
};

class Block
{
public:
    Block();
    Block(vec3 pos, blockType type);
    Block(vec3 pos, blockType type, vector<int> sideExclusion);
    
    //Front,Bottom, Top,    Back,   Left,   Right
    //0     1,      2,      3,      4,      5
    vector<int> sideExclusion;
    vec3 pos;
    Cube buildCube();
    blockType type;
    
    Cube buildBlock();
};


#endif /* Block_hpp */
