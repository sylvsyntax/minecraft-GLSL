//
//  Cube.cpp
//  Minecraft-GLSL
//
//  Created by Sylvia Sharpe on 12/2/21.
//

#include "Cube.h"

Cube::Cube() : shaderProgram("src/default.vert","src/default.frag"){
    //Cube
    Vertex cubeVertices[] =
    { //     COORDINATES       //
        Vertex{glm::vec3(-0.1f, -0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.1f, -0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, -0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.1f, 0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.1f, 0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.1f, 0.1f)},
    };

    GLuint cubeIndices[] =
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
    
    vector<Vertex> cubeVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
    vector<GLuint> cubeInd(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
    vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    
    //Sets the color of the light
    glm::vec3 cubePos = position;
    glm::mat4 cubeModel = glm::mat4(1.0f);
    cubeModel = glm::translate(cubeModel, cubePos);
    
    Mesh cube(cubeVerts, cubeInd, tex);
    mesh = cube;
    
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
}




Cube::Cube(glm::vec3 newPosition) : shaderProgram("src/default.vert","src/default.frag"){
    //Cube
    Vertex cubeVertices[] =
    { //     COORDINATES       //
        Vertex{glm::vec3(-0.1f, -0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
        Vertex{glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, -0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.1f, 0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.1f, 0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.1f, 0.1f)},
    };
    
    //This is our translation (please fix)
    for (int i = 0; i < 8; i++){
        cubeVertices[i].position.x += newPosition.x;
        cubeVertices[i].position.y += newPosition.y;
        cubeVertices[i].position.z += newPosition.z;
    }

    GLuint cubeIndices[] =
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
    vector<Vertex> cubeVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
    vector<GLuint> cubeInd(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
    vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    
    glm::vec3 cubePos = position;
    glm::mat4 cubeModel = glm::mat4(1.0f);
    cubeModel = glm::translate(cubeModel, cubePos);
    
    Mesh cube(cubeVerts, cubeInd, tex);
    mesh = cube;
    
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
    
    for (auto & i : LightSources)
    {
        glm::vec4 lightColor = i.lightColor;
        glm::vec3 lightPos = i.lightPos;
        glm::mat4 lightModel = i.lightModel;
        lightModel = glm::translate(lightModel, lightPos);
            
        glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    }
}







LightingCube::LightingCube(glm::vec3 newPosition) : lightShader("src/light.vert", "src/light.frag"){
    //Cube
    Vertex cubeVertices[] =
    { //     COORDINATES       //
        Vertex{glm::vec3(-0.1f, -0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.1f, -0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, -0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.1f, 0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.1f, 0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.1f, 0.1f)},
    };
    
    for (int i = 0; i < 8; i++){
        cubeVertices[i].position.x += newPosition.x;
        cubeVertices[i].position.y += newPosition.y;
        cubeVertices[i].position.z += newPosition.z;
    }
    GLuint cubeIndices[] =
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
    
    vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    vector<Vertex> lightVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
    vector<GLuint> lightInd(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
    Mesh light(lightVerts, lightInd, tex);
    mesh = light;
    
    lightModel = glm::translate(lightModel, lightPos);
    
    lightShader.Activate();
    
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
}

LightingCube::LightingCube() : lightShader("src/light.vert", "src/light.frag"){
    //Cube
    Vertex cubeVertices[] =
    { //     COORDINATES       //
        Vertex{glm::vec3(-0.1f, -0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.1f, -0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, -0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, -0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, -0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.1f, 0.1f, 0.1f)},
        Vertex{glm::vec3(-0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.1f, 0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.1f, -0.1f)},
        Vertex{glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.1f, 0.1f)},
    };

    GLuint cubeIndices[] =
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
    
    vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    vector<Vertex> lightVerts(cubeVertices, cubeVertices + sizeof(cubeVertices) / sizeof(Vertex));
    vector<GLuint> lightInd(cubeIndices, cubeIndices + sizeof(cubeIndices) / sizeof(GLuint));
    Mesh light(lightVerts, lightInd, tex);
    mesh = light;
    
    lightModel = glm::translate(lightModel, lightPos);
    
    lightShader.Activate();
    
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
}
