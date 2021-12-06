//
//  Structures.hpp
//  Minecraft-GLSL
//
//  Created by Sylvia Sharpe on 12/6/21.
//

#ifndef STRUCTURES_CLASS_H
#define STRUCTURES_CLASS_H

#include "Cube.h"
#include "Block.h"
#include "BlockEnums.h"
#include "Mesh.h"
#include "World.h"

enum structureType{
    Tree, LargeTree
};


class Structures
{
public:
    Structures(structureType type, vec3 pos){
        vector<blockPos> sideExclus{blockPos::sideLeft, blockPos::sideRight, blockPos::front, blockPos::back};
        blockArray.push_back(Block(vec3(0,0.2,0) + pos, blockType::wood, sideExclus));
        blockArray.push_back(Block(vec3(0,0.4,0) + pos, blockType::wood, sideExclus));
        blockArray.push_back(Block(vec3(0,0.6,0) + pos, blockType::wood, sideExclus));
        sideExclus.push_back(blockPos::top);
        blockArray.push_back(Block(vec3(0,0.8,0) + pos, blockType::wood, sideExclus));
        int startingPt = -2;
        for(int i = 0; i < 3; i++){
            //startingPt++;
            for(int v = -2; v < 2; v++)
                for(int z = startingPt; z < abs(startingPt); z++)
                    blockArray.push_back(Block(vec3(v * 0.2, 1 + (i * 0.2), z * 0.2) + pos, blockType::leaves));
        }
    }
    vector<Block> blockArray;
    vector<LightingCube> LightSources;
    vector<Mesh> sceneMeshes;
    
    glm::vec3 position;
    
    vector<Mesh> BuildStruct(){
        Block grass(vec3(0, -1, 0), blockType::grass);
        
        for(auto & i : blockArray){
            for(auto & f : i.buildCubes()){
                sceneMeshes.push_back(f.mesh);
            }
        }
        return sceneMeshes;
    }
};

#endif
