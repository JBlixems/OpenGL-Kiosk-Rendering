#ifndef ROOF_H
#define ROOF_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../shader.hpp"
#include "drawable.h"
#include "../include/stb_image.h"

class Roof: public Drawable {
public:
    Roof(float radius, float width, const glm::vec3& position, unsigned int numStrips);
    void addCylinderVertices(float radius, float width, const glm::vec3& position, const glm::vec4& color);
    glm::vec3 getBoundingBoxMin() const override;
    glm::vec3 getBoundingBoxMax() const override;
    void computeBoundingBox();

    void draw(const Shader& shader) const;

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;
    unsigned int textureID;

    float width, height, depth;
    float radius;
    glm::vec3 position;

    void setupMesh();
    void loadTexture(const char* texturePath);
    glm::vec3 boundingBoxMin;
    glm::vec3 boundingBoxMax;
};

#endif // WINDOW_H
