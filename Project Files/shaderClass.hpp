#ifndef shaderClass_hpp
#define shaderClass_hpp

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

#endif /* shaderClass_hpp */
