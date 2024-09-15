#pragma once
#include <glad/glad.h>  // include glad to get the required OpenGL headers
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Shader
{
  public:
    // the program ID
    unsigned int ID;

    void initialise(const char *vertexPath, const char *fragmentPath);

    // use/activate the shader
    void use();
    void close();

    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};
