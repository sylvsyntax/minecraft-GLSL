//
//  Cube.hpp
//  Minecraft-GLSL
//
//  Created by Sylvia Sharpe on 12/2/21.
//

#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include "Mesh.h"


class Cube
{
public:
    Cube();
    Cube(glm::vec3 position);
    
    glm::vec3 position;
    Shader shaderProgram;
    Mesh mesh;
    //Cube(Cube cubeType, glm::vec3 position);

};

#endif /* Cube_hpp */
