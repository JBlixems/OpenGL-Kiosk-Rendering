#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../shader.hpp"
#include "drawable.h"
#include "../include/stb_image.h"

class Table: public Drawable {
public:
    Table(float width, float height, float depth, const glm::vec3& position, bool);
    void addPrismVertices(float x0, float y0, float x1, float y1, float z0, float z1, const glm::vec4& color);
    void addCylinderVertices(float radius, float height, const glm::vec4& color);
    void addLegsVertices(float legWidth, float legHeight, float legDepth, const glm::vec4& color);
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
