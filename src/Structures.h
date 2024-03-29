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
    Tree, LargeTree, House
};


class Structures
{
public:
    vector<Block> blockArray;
    vector<LightingCube> LightSources;
    vector<Mesh> sceneMeshes;
    structureType type;
    vec3 pos;
    
    Structures(structureType type, vec3 pos){
        this->type = type;
        this->pos = pos;
    }
    
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
    
    void ApplyBuild(){
        if(type == Tree){
            vector<blockPos> sideExclus{blockPos::sideLeft, blockPos::sideRight, blockPos::front, blockPos::back};
            blockArray.push_back(Block(vec3(0,0.2,0) + pos, blockType::wood, sideExclus));
            blockArray.push_back(Block(vec3(0,0.4,0) + pos, blockType::wood, sideExclus));
            blockArray.push_back(Block(vec3(0,0.6,0) + pos, blockType::wood, sideExclus));
            sideExclus.push_back(blockPos::top);
            blockArray.push_back(Block(vec3(0,0.8,0) + pos, blockType::wood, sideExclus));
            int startingPt = -2;
            for(int i = 0; i < 3; i++){
                for(int v = startingPt; v <= abs(startingPt); v++)
                    for(int z = startingPt; z <= abs(startingPt); z++)
                        blockArray.push_back(Block(vec3(v * 0.2, 1 + (i * 0.2), z * 0.2) + pos, blockType::leaves));
                startingPt++;
            }
        }
    }
    
    void ApplyBuildWithoutTranslation(){
        if(type == Tree){
            blockArray.push_back(Block(vec3(0,0,0) + pos, blockType::wood));
            blockArray.push_back(Block(vec3(0,1,0) + pos, blockType::wood));
            blockArray.push_back(Block(vec3(0,2,0) + pos, blockType::wood));
            blockArray.push_back(Block(vec3(0,3,0) + pos, blockType::wood));
            int startingPt = -2;
            for(int i = 0; i < 3; i++){
                for(int v = startingPt; v <= abs(startingPt); v++)
                    for(int z = startingPt; z <= abs(startingPt); z++)
                        blockArray.push_back(Block(vec3(v, 3 + i, z) + pos, blockType::leaves));
                startingPt++;
            }
        }
        if(type == House){
            int houseSize = 4;
            int houseHeight = 4;
            int roofHeight = 10;
            for(int i = -houseSize; i <= houseSize; i++)
                for(int f = -houseSize; f <= houseSize; f++)
                    blockArray.push_back(Block(vec3(i,0,f) + pos, blockType::woodPanel));
            
            for(int x = -houseSize; x <= houseSize; x++)
                for(int z = -houseSize; z <= houseSize; z++)
                    for(int y = 0; y <= houseHeight; y++)
                        if((abs(x) == houseSize) && (abs(z) == houseSize))
                            blockArray.push_back(Block(vec3(x,y,z) + pos, blockType::wood));
                        else if((abs(x) == houseSize) || (abs(z) == houseSize))
                            if((x != 0) || (y > 2) || (z != houseSize))
                                blockArray.push_back(Block(vec3(x,y,z) + pos, blockType::woodPanel));
            int startingPt = houseSize + 1;
            for(int i = houseHeight; i < roofHeight; i++){
                for(int v = -startingPt; v <= startingPt; v++)
                    for(int z = -houseSize - 1; z <= houseSize + 1; z++)
                        if(abs(v) == startingPt)
                            blockArray.push_back(Block(vec3(v, i, z) + pos, blockType::wood));
                        else if((abs(v) == houseSize) && (abs(z) == houseSize))
                            blockArray.push_back(Block(vec3(v,i,z) + pos, blockType::wood));
                        else if(abs(z) == houseSize)
                            blockArray.push_back(Block(vec3(v, i, z) + pos, blockType::woodPanel));
                startingPt--;
            }
            for(int x = -houseSize; x <= houseSize; x++)
                for(int z = -houseSize; z <= houseSize; z++)
                    for(int y = -4; y <= 0; y++)
                        if((abs(x) == houseSize) && (abs(z) == houseSize))
                            blockArray.push_back(Block(vec3(x,y,z) + pos, blockType::wood));
            
            
        }
    }
};

#endif /* STRUCTURES_CLASS_H */
