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
    
    //The light cube instead is at point 0, 0, 0 since center cube is storing
    //the information of where the center is and moving the light model there.
    //This is an issue.

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Chunk testChunk(i, j);

            for (auto& block : testChunk.blocks)
            {
                block.LightSources.push_back(sun);
                sceneMeshes.push_back(block.mesh);
            }
        }
    }


    //Random Cube
    glm::vec3 position = glm::vec3(-0.2f, -0.4f, -0.4f);             //Assigns the position
    Cube newBlock(position);                                        //Makes the block in the position
    newBlock.LightSources.push_back(sun);                            //Pushes it to the block shader
    sceneMeshes.push_back(newBlock.mesh);                           //Pushes it to the world renderer
    
    Cube airBlock(glm::vec3(glm::vec3(0.0, 0.4f, 0.0f)));
    
    
    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(sun.lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), sun.lightColor.x, sun.lightColor.y, sun.lightColor.z, sun.lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(sun.lightModel));
    
    
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), sun.lightColor.x, sun.lightColor.y, sun.lightColor.z, sun.lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), sun.lightPos.x, sun.lightPos.y, sun.lightPos.z);
    
    
    
    
    
    
    
    // Don't do this... this is broken after the normals were added
    // But if you do end up enabling this... I'm sorry...
    
    
    //
    // Also by making a seperate vector2 or vec3 in the cubes, we can probably assign
    // Textures that way...
    //
    
    //This creates the 10x10x10 chunk
    /*for (int i = 0; i < 10; i++) {
        for (int f = 0; f < 10; f++){
            for (int v = 0; v < 10; v++){
                glm::vec3 position = glm::vec3(0.2f * v, 0.2f * f, 0.2f * i);   //Assigns the position
                position = glm::vec3(position.x + 0.4f, position.y + -1.0f, position.z + -0.8f);
                                                                                //Moves over the position
                Cube newBlock(position);                                        //Makes the block in the position
                newBlock.LightSources.push_back(ls);                            //Pushes it to the block shader
                sceneMeshes.push_back(newBlock.mesh);                           //Pushes it to the world renderer
            }
        }
    }*/



    // CHUNK GEN BABY


}

