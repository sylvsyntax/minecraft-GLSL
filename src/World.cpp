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
    //Texture map plane
    Vertex vertices[] =
    {//         COORDINATES     /         COLORS             /   TexCoord    /       NORMALS       //
        Vertex{glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
    };


    // Indices for vertices order
    GLuint indices[] =
    {
         0, 1, 2,
         0, 2, 3
    };

    //Light cube box
    Vertex lightVertices[] =
    { //     COORDINATES       //
        Vertex{glm::vec3(-0.1f, -0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, 0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, 0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, 0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, 0.1f, 0.1f)},
    };

    GLuint lightIndices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7,
    };
    
    Texture textures[]
    {
        Texture("src/Textures/terrain.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
    };
    
    
    vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    vector<GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    Mesh floor(verts, ind, tex);
    sceneMeshes.push_back(floor);
    
    
    //Begins the shaders to the lighting mesh
    //Builds the mesh that controls the light cube
    vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
    Mesh light(lightVerts, lightInd, tex);
    sceneLights.push_back(light);

    //Sets the color of the light
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(-0.0f, 0.5f, 0.0f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    
    
    
    //Plane
    pyramidModel = glm::translate(pyramidModel, pyramidPos);
    
    //Light
    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
    
    
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    
    
    
    //This creates the light cube
    LightingCube ls(glm::vec3(-0.4f, 0.0f, 0.3f));
    sceneLights.push_back(ls.mesh);
    
    
    glm::vec3 position = glm::vec3(0.3f, 0.3f, 0.1f);               //Assigns the position
    Cube newBlock(position);                                        //Makes the block in the position
    newBlock.LightSources.push_back(ls);                            //Pushes it to the block shader
    sceneMeshes.push_back(newBlock.mesh);                           //Pushes it to the world renderer
    
    
    
    
    
    
    // Don't do this... this is broken after the normals were added
    // But if you do end up enabling this... I'm sorry...
    
    
    //
    // Also by making a seperate vector2 or vec3 in the cubes, we can probably assign
    // Textures that way...
    //
    
    //This creates the 10x10x10 chunk
    for (int i = 0; i < 10; i++){
        for (int f = 0; f < 10; f++){
            for (int v = 0; v < 10; v++){
                glm::vec3 position = glm::vec3(0.1f * v, 0.1f * f, 0.1f * i);   //Assigns the position
                Cube newBlock(position);                                        //Makes the block in the position
                newBlock.LightSources.push_back(ls);                            //Pushes it to the block shader
                sceneMeshes.push_back(newBlock.mesh);                           //Pushes it to the world renderer
            }
        }
    }
}
