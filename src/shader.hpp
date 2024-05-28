#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader {
public:
    GLuint ID;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use() const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setInt(const std::string& name, int value) const; 

private:
    void checkCompileErrors(GLuint shader, std::string type);
};

#endif
