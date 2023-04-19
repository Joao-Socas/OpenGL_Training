#ifndef SHADER_H
#define SHADER_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader(const char* Path);
    ~Shader() { delete shaderCode; };

    virtual void Compile() = 0;
    unsigned int ID;
    char* shaderCode;
protected:
    void checkCompileErrors(unsigned int shader, std::string type);
};


class VertexShader : public Shader
{
public:
    VertexShader(const char* Path) :Shader(Path) { Compile(); };
    ~VertexShader() {};

    virtual void Compile() override;
private:

};

class FragmentShader : public Shader
{
public:
	FragmentShader(const char* Path):Shader(Path) { Compile(); };
    ~FragmentShader() {};

    virtual void Compile() override;
private:

};



class ShaderProgram
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    ShaderProgram(VertexShader vertexShader, FragmentShader fragmentShader);
    // use/activate the shader
    void use();
    // utility uniform functions
    template <typename T>
    void setUniform(const std::string& name, T& value) const;
private:
    void checkCompileErrors();
};

template <typename T>
inline void ShaderProgram::setUniform(const std::string& name, T& value) const
{
}

template <>
inline void ShaderProgram::setUniform<bool>(const std::string& name, bool& value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

template <>
inline void ShaderProgram::setUniform<int>(const std::string& name, int& value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

template <>
inline void ShaderProgram::setUniform<float>(const std::string& name, float& value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

template <>
inline void ShaderProgram::setUniform<glm::vec3>(const std::string& name, glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

template <>
inline void ShaderProgram::setUniform<glm::vec4>(const std::string& name, glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

template <>
inline void ShaderProgram::setUniform<glm::mat3>(const std::string& name, glm::mat3& value) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

template <>
inline void ShaderProgram::setUniform<glm::mat4>(const std::string& name, glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
#endif