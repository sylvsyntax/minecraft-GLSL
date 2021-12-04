//
//  Block.cpp
//  Minecraft-GLSL
//
//  Created by Sylvia Sharpe on 12/3/21.
//

#include "Block.h"

bool isEqual(int k, int i){
    return (k == i);
}

Block::Block(){
    pos = vec3(0);
    type = dirt;
    sideExclusion.push_back(0);
    sideExclusion.push_back(1);
    sideExclusion.push_back(2);
    sideExclusion.push_back(3);
    sideExclusion.push_back(4);
    sideExclusion.push_back(5);
}

Block::Block(vec3 pos, blockType type){
    this->pos = pos;
    this->type = type;
    sideExclusion.push_back(0);
    sideExclusion.push_back(1);
    sideExclusion.push_back(2);
    sideExclusion.push_back(3);
    sideExclusion.push_back(4);
    sideExclusion.push_back(5);
}

Block::Block(vec3 pos, blockType type, vector<int> sideExclusion){
    this->pos = pos;
    this->type = type;
    this->sideExclusion = sideExclusion;
}

Cube Block::buildCube (){
    int n = type;
    return Cube(n, pos, sideExclusion);
}

