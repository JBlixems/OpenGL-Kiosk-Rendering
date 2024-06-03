#ifndef PLANTPOT_H
#define PLANTPOT_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../shader.hpp"
#include "drawable.h"
#include "../include/stb_image.h"

class PlantPot : public Drawable{
public:
    PlantPot(float width, float height, float depth, const glm::vec3& position);
    void draw(const Shader& shader) const;

    glm::vec3 getBoundingBoxMin() const;
    glm::vec3 getBoundingBoxMax() const;

private:
    void addPotVertices(float width, float height, float depth, const glm::vec4& color);
    void addPlantVertices(float width, float height, float depth, const glm::vec4& color);
    void addTriangleVertices(const glm::vec3& base1, const glm::vec3& base2, const glm::vec3& top, const glm::vec4& color);
    void addPrismVertices(float x0, float y0, float x1, float y1, float z0, float z1, const glm::vec4& color);
    void setupMesh();
    void loadTexture(const char* path);
    void computeBoundingBox();

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    glm::vec3 position;
    float width, height, depth;
    glm::vec3 boundingBoxMin;
    glm::vec3 boundingBoxMax;
    unsigned int VAO, VBO, EBO;
    unsigned int textureID;
};

#endif // PLANTPOT_H
