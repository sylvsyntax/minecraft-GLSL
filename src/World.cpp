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

World::World() : shaderProgram("src/Shaders/default.vert","src/Shaders/default.frag"), lightShader("src/Shaders/light.vert", "src/Shaders/light.frag"), sun(glm::vec3(0.0f,0.0f,0.0f)) {
    
    //This specifies point 0,0,0
   // LightingCube centerCube(glm::vec3(0.0f, 0.0f, 0.0f));
    sceneMeshes.push_back(sun.mesh);
    
    // =====================================
    //
    //              ISSUE HERE:
    //
    // ======================================
    
    //This creates the light cube
    //The issue is the light cube is supposed to be at point 0, 0.2 and 0
    //That's the block above the center block
    
    //glm::vec3 lightBlockPos = glm::vec3(0.0f, 0.2f, 0.0f);
   // LightingCube ls(lightBlockPos);
    sceneLights.push_back(sun.mesh);
    
    
/*                      Enable when working with chunks
 --------------------------------------------------------------------------------
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Chunk testChunk(i, j);

            for (int x = 0; x < Chunk::CHUNK_SIZE; x++)
            {
                for (int y = 0; y < Chunk::MAX_HEIGHT; y++)
                {
                    for (int z = 0; z < Chunk::CHUNK_SIZE; z++)
                    {
                        testChunk.blocks[x][y][z].LightSources.push_back(sun);
                        sceneMeshes.push_back(testChunk.blocks[x][y][z].mesh);
                    }
                }
            }

            chunks.push_back(testChunk);
        }
    }
*/
    //Random Cube
    glm::vec3 position = glm::vec3(-0.2f, -0.4f, -0.4f);             //Assigns the position
    Cube newBlock(position);                                        //Makes the block in the position
    newBlock.LightSources.push_back(sun);                            //Pushes it to the block shader
    sceneMeshes.push_back(newBlock.mesh);                           //Pushes it to the world renderer
    
    Cube airBlock(glm::vec3(glm::vec3(0.0, 0.4f, 0.0f)));
    
    
    //Random Block Test
    Block grassBlock = Block(vec3(-0.4, 1, 0), grass);
    Cube gbCube = grassBlock.buildCube();
    gbCube.LightSources.push_back(sun);
    sceneMeshes.push_back(gbCube.mesh);
    
    
    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(sun.lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), sun.lightColor.x, sun.lightColor.y, sun.lightColor.z, sun.lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(sun.lightModel));
    
    
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), sun.lightColor.x, sun.lightColor.y, sun.lightColor.z, sun.lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), sun.lightPos.x, sun.lightPos.y, sun.lightPos.z);
    
    
    
    
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



    // CHUNK GEN BABY


}

