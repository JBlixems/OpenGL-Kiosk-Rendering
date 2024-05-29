// Floor.h
#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../shader.hpp"
#include "Drawable.h"
#include "../include/stb_image.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Color;
};


class Floor : public Drawable {
public:
    Floor();
    void draw(const Shader& shader) const override;
    glm::vec3 getBoundingBoxMin() const override;
    glm::vec3 getBoundingBoxMax() const override;
    void computeBoundingBox();

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    GLuint VAO, VBO, EBO;
    GLuint textureID;

    void setupMesh();
    void loadTexture(const std::string& path);
    glm::vec3 boundingBoxMin;
    glm::vec3 boundingBoxMax;
};

#endif
