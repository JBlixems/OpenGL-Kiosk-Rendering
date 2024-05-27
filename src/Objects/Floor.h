// Floor.h
#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../shader.hpp"
#include "Drawable.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Floor : public Drawable {
public:
    Floor();
    Floor(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    void draw(const Shader& shader) const override;
    glm::vec3 getBoundingBoxMin() const override;
    glm::vec3 getBoundingBoxMax() const override;
    void computeBoundingBox();

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    GLuint VAO, VBO, EBO;

    void setupMesh();
    glm::vec3 boundingBoxMin;
    glm::vec3 boundingBoxMax;
};

#endif
