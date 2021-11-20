#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
using namespace std;

string get_file_contents(const char* file_name);

class Shader
{
public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);
    
    void Activate();
    void Delete();
};

#endif /* SHADER_CLASS_H */
