//
//  World.cpp
//  Minecraft-GLSL
//
//  Created by Sylvia Sharpe on 12/2/21.
//


#include <math.h>
#include <filesystem>
#include "World.h"

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
    int t = 0;
    int genSize = 1;
    for (int i = -genSize; i <= genSize; i++)
    {
        for (int j = -genSize; j <= genSize; j++)
        {
            t++;
            cout << "Building chunk: " << t << endl;
            generateChunk(i, j);
        }
    }
    updateChunks();
    
    
    
    
    
    
    
    
    
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
    //Build default grass Block
    

}
bool generatedBlock;
void World::updateSpecial(){
    Block grass(vec3(0, worldTime / 10, 0), blockType::grass);
    for(auto & i : grass.buildCubes()){
        sceneMeshes.pop_back();
    }
    for(auto & i : grass.buildCubes()){
        sceneMeshes.push_back(i.mesh);
    }
    cout << "Time: " << worldTime << endl;
}


void World::updateChunks()
{
    vector<vector<Block>> blocks(numOfBlocktypes + 1);
    for(auto& i : blocks){
        i.reserve(32000);
    }
    sceneMeshes.clear();
    vector<blockPos> generateSide;
    
    for (auto& i : chunks) {
        //vec3 posToPlace = i.second.blocks
        
        for (int x = 0; x < Chunk::CHUNK_SIZE; x++)
        {
            for (int y = 0; y < Chunk::MAX_HEIGHT; y++)
            {
                for (int z = 0; z < Chunk::CHUNK_SIZE; z++)
                {
                    if (i.second.blocks[x][y][z] != (int)blockType::air) {
                        //RIGHT SIDE
                        if (x == Chunk::CHUNK_SIZE - 1) {
                            if (chunks.find(Vector2Key{ i.second.position.x + 1, i.second.position.y }) != chunks.end())
                            {
                                if (chunks[Vector2Key{ i.second.position.x + 1,i.second.position.y }].blocks[0][y][z] == (int)blockType::air)
                                {
                                    generateSide.push_back(blockPos::sideRight);
                                }
                            }
                            else
                                generateSide.push_back(blockPos::sideRight);
                        }
                        else if (i.second.blocks[x + 1][y][z] == (int)blockType::air)
                            generateSide.push_back(blockPos::sideRight);


                        //LEFT SIDE
                        if (x == 0) {
                            if (chunks.find(Vector2Key{ i.second.position.x - 1, i.second.position.y }) != chunks.end())
                            {
                                if (chunks[Vector2Key{ i.second.position.x - 1,i.second.position.y }].blocks[Chunk::CHUNK_SIZE - 1][y][z] == (int)blockType::air)
                                {
                                    generateSide.push_back(blockPos::sideLeft);
                                }
                            }
                            else
                                generateSide.push_back(blockPos::sideLeft);
                        }
                        else if (i.second.blocks[x - 1][y][z] == (int)blockType::air)
                            generateSide.push_back(blockPos::sideLeft);


                        //TOP
                        if (y == Chunk::MAX_HEIGHT - 1)
                            generateSide.push_back(blockPos::top);
                        else if (i.second.blocks[x][y + 1][z] == (int)blockType::air)
                            generateSide.push_back(blockPos::top);

                        //BOTTOM
                        if (y != 0)
                            if (i.second.blocks[x][y - 1][z] == (int)blockType::air)
                                generateSide.push_back(blockPos::bottom);


                        //BACK
                        if (z == Chunk::CHUNK_SIZE - 1) {
                            if (chunks.find(Vector2Key{ i.second.position.x, i.second.position.y + 1 }) != chunks.end())
                            {
                                if (chunks[Vector2Key{ i.second.position.x,i.second.position.y + 1 }].blocks[x][y][0]== (int)blockType::air)
                                {
                                    generateSide.push_back(blockPos::back);
                                }
                            }
                            else
                                generateSide.push_back(blockPos::back);
                        }
                        else if (i.second.blocks[x][y][z + 1] == (int)blockType::air)
                            generateSide.push_back(blockPos::back);


                        //FRONT
                        if (z == 0) {
                            if (chunks.find(Vector2Key{ i.second.position.x, i.second.position.y - 1 }) != chunks.end())
                            {
                                if (chunks[Vector2Key{ i.second.position.x,i.second.position.y - 1 }].blocks[x][y][Chunk::CHUNK_SIZE - 1] == (int)blockType::air)
                                {
                                    generateSide.push_back(blockPos::front);
                                }
                            }
                            else
                                generateSide.push_back(blockPos::front);
                        }
                        else if (i.second.blocks[x][y][z - 1] == (int)blockType::air)
                            generateSide.push_back(blockPos::front);
                        
                        if(generateSide.size() != 0)
                        {
                            //Switch to batch rendering
                            
                            
                            
                            
                            //The block gets made
                            Block generateBlock(vec3(i.second.position.x * (Chunk::CHUNK_SIZE * BLOCK_SIZE) + (x * BLOCK_SIZE), (y * BLOCK_SIZE), i.second.position.y * (Chunk::CHUNK_SIZE * BLOCK_SIZE) + (z * BLOCK_SIZE)), blockType(i.second.blocks[x][y][z]), generateSide);
                            generateSide.clear();
                            
                            //Build each individual block and assign it to blocks
                            for(auto & z : generateBlock.buildBlocks()){
                                blocks[(int)z.type].push_back(z);
                            }
                        }
                    }
                }
            }
        }
        
        
        Texture textures[]
        {
            Texture("src/Textures/dirt.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
            Texture("src/Textures/cobblestone.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
            Texture("src/Textures/grass_block_top.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
            Texture("src/Textures/grass_block_side.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
            Texture("src/Textures/wood_side.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
            Texture("src/Textures/wood_top.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
            Texture("src/Textures/leaves.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
        };
        int z = 0;
        for(auto & j : blocks){ //Per vector
            vector<Vertex> cubeVertex;
            if(j.size())
            for (auto & f : j) //Per block
                for (auto & j : f.buildCube().getVertexSet(f.pos, f.sideExclusion))
                    cubeVertex.push_back(j);
            
            
            vector<GLuint> cubeInd;
            for (int p = 0; p < cubeVertex.size(); p++){
                cubeInd.push_back(p);
            }
            if(cubeInd.size() != 0){
                vector<Texture> tex;
                if(z == (int)blockType::wood)
                    tex.push_back(textures[(int)blockType::wood]);
                else
                    tex.push_back(textures[(int)j[z].type]);
                
                
                glm::vec3 cubePos = glm::vec3(i.second.position.x * 8 * 0.2, 0, i.second.position.y * 8 * 0.2);
                glm::mat4 cubeModel = glm::mat4(1.0f);
                cubeModel = glm::translate(cubeModel, cubePos);
                
                Mesh set(cubeVertex, cubeInd, tex);
                sceneMeshes.push_back(set);
                j.clear();
            }
            z++;
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
