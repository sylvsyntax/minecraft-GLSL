//
//  Block.cpp
//  Minecraft-GLSL
//
//  Created by Sylvia Sharpe on 12/3/21.
//

#include "Block.h"


Block::Block(){
    pos = vec3(0);
    type = dirt;
}

Block::Block(vec3 pos, blockType type){
    this->pos = pos;
    this->type = type;
}

Cube Block::buildCube (){
    int n = type;
    vector<int> sideExclusion;
    sideExclusion.push_back(0);
    sideExclusion.push_back(2);
    return Cube(n, pos, sideExclusion);
}

