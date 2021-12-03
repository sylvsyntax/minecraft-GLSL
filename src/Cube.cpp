//
//  Cube.cpp
//  Minecraft-GLSL
//
//  Created by Sylvia Sharpe on 12/2/21.
//

#include "Cube.h"
#include "Shapes/shapes.h"
const int numberOfVertices = 6 * 6;
const int numberOfIndices = numberOfVertices * (3/2);

Vertex cubeVertices[] =
{          //         COORDINATES       //         NORMALS           //           COLOR          //       TEXCOORD       //
    Vertex{glm::vec3(-0.1f, -0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0, 0)},
    Vertex{glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0, 1)},
    Vertex{glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1, 1)},
    Vertex{glm::vec3(0.1f, -0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1, 0)},
    Vertex{glm::vec3(-0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0, 0)},
    Vertex{glm::vec3(-0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0, 1)},
    Vertex{glm::vec3(0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1, 1)},
    Vertex{glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1, 0)},
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

Vertex convertPtToVert(vec3 point){
    return Vertex{glm::vec3(point.getx(), point.gety(), point.getz()), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0, 0)};
}

void resetVertices(){
    Vertex defaultCubeVertices[] =
    {          //         COORDINATES       //         NORMALS           //           COLOR          //       TEXCOORD       //
        Vertex{glm::vec3(-0.1f, -0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0, 0)},
        Vertex{glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0, 1)},
        Vertex{glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1, 1)},
        Vertex{glm::vec3(0.1f, -0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1, 0)},
        Vertex{glm::vec3(-0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0, 0)},
        Vertex{glm::vec3(-0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0, 1)},
        Vertex{glm::vec3(0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1, 1)},
        Vertex{glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1, 0)},
    };
    
    for(int i = 0; i < numberOfVertices; i++){
        cubeVertices[i] = defaultCubeVertices[i];
    }
    
}

Cube::Cube() : shaderProgram("src/Shaders/default.vert","src/Shaders/default.frag"){
    //Cube
    
    Texture textures[]
    {
        Texture("src/Textures/dirt.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
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



//Because we don't have enough vertices we cant build what we need to in order to properly assign the normals...
Cube::Cube(glm::vec3 newPosition) : shaderProgram("src/Shaders/default.vert","src/Shaders/default.frag"){

    //This is our translation (please fix)
    for (int i = 0; i < 8; i++){
        cubeVertices[i].position.x += newPosition.x;
        cubeVertices[i].position.y += newPosition.y;
        cubeVertices[i].position.z += newPosition.z;
    }

    
    Texture textures[]
    {
        Texture("src/Textures/dirt.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
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
    resetVertices();
}







LightingCube::LightingCube(glm::vec3 newPosition) : lightShader("src/Shaders/light.vert", "src/Shaders/light.frag"){

    
    Texture textures[]
    {
        Texture("src/Textures/dirt.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
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
    resetVertices();
}

LightingCube::LightingCube() : lightShader("src/Shaders/light.vert", "src/Shaders/light.frag"){

    
    Texture textures[]
    {
        Texture("src/Textures/dirt.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
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
