#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../shader.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Floor {
public:
    Floor(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    void draw(const Shader& shader) const;

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    GLuint VAO, VBO, EBO;

    void setupMesh();
};

#endif
