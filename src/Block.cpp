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


vector<Cube> Block::buildCubes(){
    vector<Cube> caughtCubes;
    vector<blockPos> newExclusions;
    
    //          Only if the caught block is a grass block
    
    if(type == blockType::grass){
        for(auto & i : sideExclusion){
            if (i == blockPos::top)
                caughtCubes.push_back(Cube(type, pos, {blockPos::top}));
            else if (i == blockPos::bottom)
                caughtCubes.push_back(Cube(blockType::dirt, pos, {blockPos::bottom}));
            else
                newExclusions.push_back(i);
            if(newExclusions.size() != 0)
                caughtCubes.push_back(Cube(blockType::sideGrass, pos, newExclusions));
        }
    }
    else if(type == blockType::wood){
        for(auto & i : sideExclusion){
            if (i == blockPos::top)
                caughtCubes.push_back(Cube(blockType::woodEnd, pos, {blockPos::top}));
            else if (i == blockPos::bottom)
                caughtCubes.push_back(Cube(blockType::woodEnd, pos, {blockPos::bottom}));
            else
                newExclusions.push_back(i);
            if(newExclusions.size() != 0)
                caughtCubes.push_back(Cube(blockType::wood, pos, newExclusions));
        }
    }
    else
        caughtCubes.push_back(Cube (type, pos, sideExclusion));
    
    return caughtCubes;
}

vector<Block> Block::buildBlocks(){
    vector<Block> caughtBlocks;
    vector<blockPos> newExclusions;
    
    //          Only if the caught block is a grass block
    
    if(type == blockType::grass){
        for(auto & i : sideExclusion){
            if (i == blockPos::top)
                caughtBlocks.push_back(Block(pos, type, {blockPos::top}));
            else if (i == blockPos::bottom)
                caughtBlocks.push_back(Block(pos, blockType::dirt, {blockPos::bottom}));
            else
                newExclusions.push_back(i);
            if(newExclusions.size() != 0)
                caughtBlocks.push_back(Block(pos, blockType::sideGrass, newExclusions));
        }
    }
    else if(type == blockType::wood){
        for(auto & i : sideExclusion){
            if (i == blockPos::top)
                caughtBlocks.push_back(Block(pos, blockType::woodEnd, {blockPos::top}));
            else if (i == blockPos::bottom)
                caughtBlocks.push_back(Block(pos, blockType::woodEnd, {blockPos::bottom}));
            else
                newExclusions.push_back(i);
            if(newExclusions.size() != 0)
                caughtBlocks.push_back(Block(pos, blockType::wood, newExclusions));
        }
    }
    else
        caughtBlocks.push_back(Block (pos, type, sideExclusion));
    
    return caughtBlocks;
}

