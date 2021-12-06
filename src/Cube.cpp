//
//  Cube.cpp
//  Minecraft-GLSL
//
//  Created by Sylvia Sharpe on 12/2/21.
//

#include "Cube.h"
#include "VBO.h"
#include "BlockEnums.h"

glm::vec3 regVecToGLM(vec3 pt){
    return glm::vec3(pt.getx(), pt.gety(), pt.getz());
}


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
    
    for(int i = 0; i < 8; i++){
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
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), newPosition.x, newPosition.y, newPosition.z);
    }
    resetVertices();
}



LightingCube::LightingCube(glm::vec3 newPosition) : lightShader("src/Shaders/light.vert", "src/Shaders/light.frag"){
    
    lightPos.x += newPosition.x;
    lightPos.y += newPosition.y;
    lightPos.z += newPosition.z;
    
    for (int i = 0; i < 8; i++){
        cubeVertices[i].position.x += newPosition.x;
        cubeVertices[i].position.y += newPosition.y;
        cubeVertices[i].position.z += newPosition.z;
    }
    
    lightPos.x = cubeVertices[0].position.x;
    lightPos.y = cubeVertices[0].position.y;
    lightPos.z = cubeVertices[0].position.z;
    
    
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


//New cube method

Cube::Cube(blockType type, vec3 pos) : position(pos.getx(), pos.gety(), pos.getz()), shaderProgram("src/Shaders/default.vert", "src/Shaders/default.frag") {
    this->type = type;
    if (type == blockType::air) return;
    glm::vec3 defaultNormal = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 defaultColor = glm::vec3(1.0f, 1.0f, 1.0f);
    
    
    face cube[6];
    vec3 defaultpt1 = vec3(0, 1, 0);
    vec3 defaultpt2 = vec3(1, 0, 0);
    vec3 defaultpt3 = vec3(0);

    //And these are the default triangles used for nef. The singular face we will manipulate to build this box.
    triangle trg = triangle(defaultpt1, defaultpt2, defaultpt3);
    triangle trg2 = triangle(defaultpt1, defaultpt2, defaultpt3);
    //The rotation is done to complete the face.
    trg2.rotateAcrossAxis('x');

    //Then we assign the triangles to the face that we will be manipulating
    face nef = face(&trg, &trg2);
    cube[0] = nef;
    cube[0].removeConstructors();

    //This makes the bottom of the box
    //Essentially we rotate it 90 degrees backwards so it's facing inside
    //Than we flip the shape by switching the direction of the triangles
    nef.rotateY90();
    cube[1] = nef;
    cube[1].removeConstructors();

    //We can then move the shape up
    //And flip it again
    nef.translate(vec3(0, 1, 0));
    cube[2] = nef;
    cube[2].removeConstructors();

    //Now we reset to the default position and flip
    //the triangles again
    trg = triangle(defaultpt1, defaultpt2, defaultpt3);
    trg2 = triangle(defaultpt1, defaultpt2, defaultpt3);
    trg2.rotateAcrossAxis('x');

    //We translate the shape backwards and flip it so it makes the back wall
    nef.translate(vec3(0, 0, 1));
    cube[3] = nef;
    cube[3].removeConstructors();

    //Than we move the shape the opposite direction
    //Repeating the steps back to normal so its facing
    //the original position
    nef.translate(vec3(0, 0, -1));

    //Now we can rotate the shape sideways and flip it
    nef.rotateX90();
    cube[4] = nef;
    cube[4].removeConstructors();

    //Than we translate it by the x value so it can be in
    //the propper position, and we flip it so it faces
    //the right direction
    nef.translate(vec3(1, 0, 0));
    cube[5] = nef;
    cube[5].removeConstructors();
    
    Vertex cubeVertex[36]{};
    
    if(type == blockType::grass)
        defaultColor = glm::vec3(-0.5f, 2, -0.5f);
    else
        defaultColor = glm::vec3(1, 1, 1);
        
    for(int i = 0; i < 6; i++){
        cube[i].scale(vec3(0.2));
        cube[i].translate(pos);
        cubeVertex[i * 6 + 0] = {regVecToGLM(cube[i].t1->pt1), defaultNormal, defaultColor, glm::vec2(0, 0)};
        cubeVertex[i * 6 + 1] = {regVecToGLM(cube[i].t1->pt2), defaultNormal, defaultColor, glm::vec2(1, 0)};
        cubeVertex[i * 6 + 2] = {regVecToGLM(cube[i].t1->pt3), defaultNormal, defaultColor, glm::vec2(0, 1)};
        cubeVertex[i * 6 + 3] = {regVecToGLM(cube[i].t2->pt1), defaultNormal, defaultColor, glm::vec2(1, 1)};
        cubeVertex[i * 6 + 4] = {regVecToGLM(cube[i].t2->pt2), defaultNormal, defaultColor, glm::vec2(0, 1)};
        cubeVertex[i * 6 + 5] = {regVecToGLM(cube[i].t2->pt3), defaultNormal, defaultColor, glm::vec2(1, 0)};
    }
    
    
    GLuint cubeInd[36 * 6]{};
    for (int i = 0; i < (36 * 6); i++){
        cubeInd[i] = i;
    }
    
    //This is our translation (please fix)
    for (int i = 0; i < 8; i++){
        cubeVertices[i].position.x += pos.getx();
        cubeVertices[i].position.y += pos.gety();
        cubeVertices[i].position.z += pos.getz();
    }
    
    
    
    Texture textures[]
    {
        Texture("src/Textures/dirt.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("src/Textures/cobblestone.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("src/Textures/grass_block_top.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
    };
    vector<Vertex> cubeVerts(cubeVertex, cubeVertex + sizeof(cubeVertex) / sizeof(Vertex));
    vector<GLuint> cubeIndices(cubeInd, cubeInd + sizeof(cubeInd) / sizeof(GLuint));
    vector<Texture> tex;
    tex.push_back(textures[(int)type]);
    
    glm::vec3 cubePos = position;
    glm::mat4 cubeModel = glm::mat4(1.0f);
    cubeModel = glm::translate(cubeModel, cubePos);
    
    Mesh block(cubeVerts, cubeIndices, tex);
    mesh = block;
    
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
    
    for (auto & i : LightSources)
    {
        glm::vec4 lightColor = i.lightColor;
        glm::vec3 lightPos = i.lightPos;
        glm::mat4 lightModel = i.lightModel;
        lightModel = glm::translate(lightModel, lightPos);
        glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), pos.getx(), pos.gety(), pos.getz());
    }
}

//Front, Bottom, Top, Back, Left, Right
Cube::Cube(blockType type, vec3 pos, vector<blockPos> sideExclusion) : position(pos.getx(), pos.gety(), pos.getz()), shaderProgram("src/Shaders/default.vert", "src/Shaders/default.frag") {
    this->type = type;
    if (type == blockType::air) return;
    glm::vec3 defaultNormal = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 defaultColor = glm::vec3(1.0f, 1.0f, 1.0f);
    
    
    face cube[6];
    vec3 defaultpt1 = vec3(0, 1, 0);
    vec3 defaultpt2 = vec3(1, 0, 0);
    vec3 defaultpt3 = vec3(0);

    //And these are the default triangles used for nef. The singular face we will manipulate to build this box.
    triangle trg = triangle(defaultpt1, defaultpt2, defaultpt3);
    triangle trg2 = triangle(defaultpt1, defaultpt2, defaultpt3);
    //The rotation is done to complete the face.
    trg2.rotateAcrossAxis('x');

    //Then we assign the triangles to the face that we will be manipulating
    face nef = face(&trg, &trg2);
    nef.flip();
    cube[0] = nef;
    cube[0].removeConstructors();
    nef.flip();

    //This makes the bottom of the box
    //Essentially we rotate it 90 degrees backwards so it's facing inside
    //Than we flip the shape by switching the direction of the triangles
    nef.rotateY90();
    nef.flip();
    cube[1] = nef;
    cube[1].removeConstructors();

    //We can then move the shape up
    //And flip it again
    nef.translate(vec3(0, 1, 0));
    nef.flip();
    nef.rotateVerts();
    cube[2] = nef;
    cube[2].removeConstructors();

    //Now we reset to the default position and flip
    //the triangles again
    trg = triangle(defaultpt1, defaultpt2, defaultpt3);
    trg2 = triangle(defaultpt1, defaultpt2, defaultpt3);
    trg2.rotateAcrossAxis('x');

    //We translate the shape backwards and flip it so it makes the back wall
    nef.translate(vec3(0, 0, 1));
    nef.flip();
    cube[3] = nef;
    cube[3].removeConstructors();

    //Than we move the shape the opposite direction
    //Repeating the steps back to normal so its facing
    //the original position
    nef.translate(vec3(0, 0, -1));
    nef.flip();

    //Now we can rotate the shape sideways and flip it
    nef.rotateX90();
    nef.flip();
    cube[4] = nef;
    cube[4].removeConstructors();

    //Than we translate it by the x value so it can be in
    //the propper position, and we flip it so it faces
    //the right direction
    nef.translate(vec3(1, 0, 0));
    cube[5] = nef;
    cube[5].removeConstructors();

    vector<Vertex> cubeVertex(6 * sideExclusion.size());
    
    if(type == blockType::grass)
        defaultColor = glm::vec3(-0.5f, 2, -0.5f);
    else
        defaultColor = glm::vec3(1, 1, 1);
    
    int v = 0;
    for(int i = 0; i < 6; i++){
        cube[i].scale(vec3(0.2));
        cube[i].translate(pos);
        for(blockPos f : sideExclusion)
            if((int)f == i){
                cubeVertex[static_cast<std::vector<Vertex, std::allocator<Vertex>>::size_type>(v) * 6 + 0] = {regVecToGLM(cube[i].t1->pt1), defaultNormal, defaultColor, glm::vec2(0, 0)};
                cubeVertex[static_cast<std::vector<Vertex, std::allocator<Vertex>>::size_type>(v) * 6 + 1] = {regVecToGLM(cube[i].t1->pt2), defaultNormal, defaultColor, glm::vec2(1, 0)};
                cubeVertex[static_cast<std::vector<Vertex, std::allocator<Vertex>>::size_type>(v) * 6 + 2] = {regVecToGLM(cube[i].t1->pt3), defaultNormal, defaultColor, glm::vec2(0, 1)};
                cubeVertex[static_cast<std::vector<Vertex, std::allocator<Vertex>>::size_type>(v) * 6 + 3] = {regVecToGLM(cube[i].t2->pt1), defaultNormal, defaultColor, glm::vec2(1, 1)};
                cubeVertex[static_cast<std::vector<Vertex, std::allocator<Vertex>>::size_type>(v) * 6 + 4] = {regVecToGLM(cube[i].t2->pt2), defaultNormal, defaultColor, glm::vec2(0, 1)};
                cubeVertex[static_cast<std::vector<Vertex, std::allocator<Vertex>>::size_type>(v) * 6 + 5] = {regVecToGLM(cube[i].t2->pt3), defaultNormal, defaultColor, glm::vec2(1, 0)};
                v++;
            }
    }
    
    
    vector<GLuint> cubeInd;
    for (int i = 0; i < (36 * sideExclusion.size()); i++){
        cubeInd.push_back(i);
    }
    
    
    //In order to go about seperate images per face we can do this
    
    //Seperate each face into it's own mesh
    //Apply textures seperately
    //Make it work with the exclusion method
    
    //Each mesh will have 6 verteces and 6 vertexes
    //Possibly make a new class to handle this method?
    
    
    Texture textures[]
    {
        Texture("src/Textures/dirt.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("src/Textures/cobblestone.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("src/Textures/grass_block_top.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("src/Textures/grass_block_side.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE)
    };
    //vector<Vertex> cubeVerts(cubeVertex, cubeVertex + sizeof(cubeVertex) / sizeof(Vertex));
    //vector<GLuint> cubeIndices(cubeInd, cubeInd + sizeof(cubeInd) / sizeof(GLuint));
    vector<Texture> tex;
    tex.push_back(textures[(int)type]);
    
    glm::vec3 cubePos = position;
    glm::mat4 cubeModel = glm::mat4(1.0f);
    cubeModel = glm::translate(cubeModel, cubePos);
    
    Mesh block(cubeVertex, cubeInd, tex);
    mesh = block;
    
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cubeModel));
    
    for (auto & i : LightSources)
    {
        glm::vec4 lightColor = i.lightColor;
        glm::vec3 lightPos = i.lightPos;
        glm::mat4 lightModel = i.lightModel;
        lightModel = glm::translate(lightModel, lightPos);
        glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), pos.getx(), pos.gety(), pos.getz());
    }
}
