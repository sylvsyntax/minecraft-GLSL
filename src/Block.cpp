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
    type = blockType::dirt;
    sideExclusion.push_back(blockPos::front);
    sideExclusion.push_back(blockPos::bottom);
    sideExclusion.push_back(blockPos::top);
    sideExclusion.push_back(blockPos::back);
    sideExclusion.push_back(blockPos::sideLeft);
    sideExclusion.push_back(blockPos::sideRight);
}

Block::Block(vec3 pos, blockType type){
    this->pos = pos;
    this->type = type;
    sideExclusion.push_back(blockPos::front);
    sideExclusion.push_back(blockPos::bottom);
    sideExclusion.push_back(blockPos::top);
    sideExclusion.push_back(blockPos::back);
    sideExclusion.push_back(blockPos::sideLeft);
    sideExclusion.push_back(blockPos::sideRight);
}

Block::Block(vec3 pos, blockType type, vector<blockPos> sideExclusion){
    this->pos = pos;
    this->type = type;
    this->sideExclusion = sideExclusion;
}

Cube Block::buildCube (){
    return Cube(type, pos, sideExclusion);
}

