//
//  World.cpp
//  Minecraft-GLSL
//
//  Created by Sylvia Sharpe on 12/2/21.
//

#include <filesystem>
#include "World.h"
#include "Cube.h"

World::World() : shaderProgram("src/Shaders/default.vert","src/Shaders/default.frag"), lightShader("src/Shaders/light.vert", "src/Shaders/light.frag") {
    
    //This specifies point 0,0,0
    LightingCube centerCube(glm::vec3(0.0f, -0.5f, 0.0f));
    sceneMeshes.push_back(centerCube.mesh);
    
    // =====================================
    //
    //              ISSUE HERE:
    //
    // ======================================
    
    //This creates the light cube
    //The issue is the light cube is supposed to be at point 0, 0.2 and 0
    //That's the block above the center block
    
    glm::vec3 lightBlockPos = glm::vec3(0.0f, 0.4f, 0.0f);
    LightingCube ls(lightBlockPos);
    sceneLights.push_back(ls.mesh);
    
    //The light cube instead is at point 0, 0, 0 since center cube is storing
    //the information of where the center is and moving the light model there.
    //This is an issue.
    
    //Random Cube
    vec3 position = vec3(-0.2f, 0.4f, -0.8f);             //Assigns the position
    Cube newBlock(1, position);                                        //Makes the block in the position
    newBlock.LightSources.push_back(ls);                            //Pushes it to the block shader
    sceneMeshes.push_back(newBlock.mesh);                           //Pushes it to the world renderer
    
    
    
    
    
    
    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(centerCube.lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), ls.lightColor.x, ls.lightColor.y, ls.lightColor.z, ls.lightColor.w);
    
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(centerCube.lightModel));
    
    
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), ls.lightColor.x, ls.lightColor.y, ls.lightColor.z, ls.lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightBlockPos.x, lightBlockPos.y, lightBlockPos.z);
    
    
    
    
    int blockType = 1;
    //This creates the 10x10x10 chunk
    for (int i = 0; i < 10; i++){
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
    }
}
