//
//  Cube.hpp
//  Minecraft-GLSL
//
//  Created by Sylvia Sharpe on 12/2/21.
//

#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include "Mesh.h"
#include "shapes.h"

class LightingCube
{
public:
    LightingCube();
    LightingCube(glm::vec3 position);
    Shader lightShader;
    Mesh mesh;
    
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(-0.0f, -0.0f, 0.0f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    
    
};

class Cube
{
public:
    Cube();
    Cube(glm::vec3 position);
    Cube(int type, vec3 pos);
    int type;
    vector<LightingCube> LightSources;
    
    glm::vec3 position;
    Shader shaderProgram;
    Mesh mesh;
    int type;
    //Cube(Cube cubeType, glm::vec3 position);

};

#endif /* Cube_hpp */
