//
//  World.cpp
//  Minecraft-GLSL
//
//  Created by Sylvia Sharpe on 12/2/21.
//


#include <math.h>
#include <filesystem>
#include "World.h"
#include "Cube.h"
#include "Chunk.h"
#include "Block.h"
#include "Structures.h"

World::World() : shaderProgram("src/Shaders/default.vert","src/Shaders/default.frag"), lightShader("src/Shaders/light.vert", "src/Shaders/light.frag"), sun(glm::vec3(0.0f,0.0f,0.0f)) {
    
    //This specifies point 0,0,0
    //LightingCube centerCube(glm::vec3(0.0f, 0.0f, 0.0f));
    sceneMeshes.push_back(sun.mesh);
    
    //glm::vec3 lightBlockPos = glm::vec3(0.0f, 0.2f, 0.0f);
    // LightingCube ls(lightBlockPos);
    sceneLights.push_back(sun.mesh);
    
    //updateChunks();
    
/*                      Enable when working with chunks
 --------------------------------------------------------------------------------
 */
    
    

    
    //Cube airBlock(glm::vec3(glm::vec3(0.0, 0.4f, 0.0f)));
    
    
    /*
    //========================================================================================
    //                              EXAMPLES OF BLOCK BUILDING
    //========================================================================================
    
    
    
    //======================
    //  How to build a block
    //======================
    
    //Random Block Test
    vector<blockPos> faces;          //These are the faces we ar showing
    faces.push_back(top);       //Because of the enum (stored in block.h) we can just say what side we want
    faces.push_back(sideRight);
    faces.push_back(sideLeft);
    
    Block grassBlock = Block(vec3(-0.4, 1, 0), grass, faces);   //Now we build the block
    Cube gbCube = grassBlock.buildCube();                       //We store it's cube
    gbCube.LightSources.push_back(sun);                         //We apply its light source
    sceneMeshes.push_back(gbCube.mesh);                         //And we push it to the scene
    
    
    
    
    //======================
    //  Default Block
    //======================
     Block grass(vec3(0, -1, 0), blockType::grass); //Create the block and store it's information
     for(auto & i : grass.buildCubes()){            //Build the cubes and store them to an array
         sceneMeshes.push_back(i.mesh);             //Push each cube to the mesh
     }                                              //Each cube has an individual texture for each side of the object
    
    */
    
    
    
    
    //int blockType = 1;
    //This creates the 10x10x10 chunk
    /*for (int i = 0; i < 10; i++){
        for (int v = 0; v < 10; v++){
            for (int f = 0; f < 10; f++){
                vec3 position = vec3(0.2f * v - 1.0f, 0.2f * f - 2.1f, 0.2f * i - 1.0f);   //Assigns the position
                
                if(f >= 7 && f <= 8)
                    blockType = 0;
                else if (f >= 9)
                    blockType = 2;
                else
                    blockType = 1;
                
                Cube newBlock(blockType, position);
                
                //Makes the block in the position
                newBlock.LightSources.push_back(ls);                            //Pushes it to the block shader
                sceneMeshes.push_back(newBlock.mesh);                           //Pushes it to the world renderer
            }
        }
    }*/
    
    
    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(sun.lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), sun.lightColor.x, sun.lightColor.y, sun.lightColor.z, sun.lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(sun.lightModel));


    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), sun.lightColor.x, sun.lightColor.y, sun.lightColor.z, sun.lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), sun.lightPos.x, sun.lightPos.y, sun.lightPos.z);


    // CHUNK GEN BABY

    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            generateChunk(i, j);
        }
    }
    updateChunks();
    
    
    
    
    
    //Build default grass Block
    
    Block grass(vec3(0, -1, 0), blockType::grass);
    for(auto & i : grass.buildCubes()){
        sceneMeshes.push_back(i.mesh);
    }
    
    
    
    
    
}

void World::generateChunk(int x, int y)
{
    // update chunks if position given hasnt been generated
    if (chunks.find(Vector2Key{ x, y }) != chunks.end()) {
        cout << "Found Chunk";
        return;
    }
    Chunk chunk(x, y);
    chunks[Vector2Key{ x, y }] = chunk;

}

void World::updateChunks()
{
    sceneMeshes.clear();
    for (auto& i : chunks) {
        for (int x = 0; x < Chunk::CHUNK_SIZE; x++)
        {
            for (int y = 0; y < Chunk::MAX_HEIGHT; y++)
            {
                for (int z = 0; z < Chunk::CHUNK_SIZE; z++)
                {
                    if (i.second.blocks[x][y][z].type != blockType::air) {
                        vector<blockPos> generateSide;
                        //RIGHT SIDE
                        if (x == Chunk::CHUNK_SIZE - 1) {
                            if (chunks.find(Vector2Key{ i.second.position.x + 1, i.second.position.y }) != chunks.end())
                            {
                                if (chunks[Vector2Key{ i.second.position.x + 1,i.second.position.y }].blocks[0][y][z].type == blockType::air)
                                {
                                    generateSide.push_back(blockPos::sideRight);
                                }
                            }
                            else
                                generateSide.push_back(blockPos::sideRight);
                        }
                        else if (i.second.blocks[x + 1][y][z].type == blockType::air)
                            generateSide.push_back(blockPos::sideRight);


                        //LEFT SIDE
                        if (x == 0) {
                            if (chunks.find(Vector2Key{ i.second.position.x - 1, i.second.position.y }) != chunks.end())
                            {
                                if (chunks[Vector2Key{ i.second.position.x - 1,i.second.position.y }].blocks[Chunk::CHUNK_SIZE - 1][y][z].type == blockType::air)
                                {
                                    generateSide.push_back(blockPos::sideLeft);
                                }
                            }
                            else
                                generateSide.push_back(blockPos::sideLeft);
                        }
                        else if (i.second.blocks[x - 1][y][z].type == blockType::air)
                            generateSide.push_back(blockPos::sideLeft);


                        //TOP
                        if (y == Chunk::MAX_HEIGHT - 1)
                            generateSide.push_back(blockPos::top);
                        else if (i.second.blocks[x][y + 1][z].type == blockType::air)
                            generateSide.push_back(blockPos::top);

                        //BOTTOM
                        if (y != 0)
                            if (i.second.blocks[x][y - 1][z].type == blockType::air)
                                generateSide.push_back(blockPos::bottom);


                        //BACK
                        if (z == Chunk::CHUNK_SIZE - 1) {
                            if (chunks.find(Vector2Key{ i.second.position.x, i.second.position.y + 1 }) != chunks.end())
                            {
                                if (chunks[Vector2Key{ i.second.position.x,i.second.position.y + 1 }].blocks[x][y][0].type == blockType::air)
                                {
                                    generateSide.push_back(blockPos::back);
                                }
                            }
                            else
                                generateSide.push_back(blockPos::back);
                        }
                        else if (i.second.blocks[x][y][z + 1].type == blockType::air)
                            generateSide.push_back(blockPos::back);


                        //FRONT
                        if (z == 0) {
                            if (chunks.find(Vector2Key{ i.second.position.x, i.second.position.y - 1 }) != chunks.end())
                            {
                                if (chunks[Vector2Key{ i.second.position.x,i.second.position.y - 1 }].blocks[x][y][Chunk::CHUNK_SIZE - 1].type == blockType::air)
                                {
                                    generateSide.push_back(blockPos::front);
                                }
                            }
                            else
                                generateSide.push_back(blockPos::front);
                        }
                        else if (i.second.blocks[x][y][z - 1].type == blockType::air)
                            generateSide.push_back(blockPos::front);




                        //Building the blocks
                        i.second.blocks[x][y][z].sideExclusion = generateSide;
                        for(auto & i : i.second.blocks[x][y][z].buildCubes()){
                            sceneMeshes.push_back(i.mesh);
                        }
                    }
                }
            }
            for(auto & i : Structures(Tree, i.second.getTop(3, 4)).BuildStruct()){
                sceneMeshes.push_back(i);
            }
            ;

        }
        
    }

    /*lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(sun.lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), sun.lightColor.x, sun.lightColor.y, sun.lightColor.z, sun.lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(sun.lightModel));


    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), sun.lightColor.x, sun.lightColor.y, sun.lightColor.z, sun.lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), sun.lightPos.x, sun.lightPos.y, sun.lightPos.z);*/
}
