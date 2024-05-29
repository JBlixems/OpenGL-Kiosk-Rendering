#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../shader.hpp"
#include "drawable.h"
#include "../include/stb_image.h"

class Window: public Drawable {
public:
    Window(float width, float height, float depth, const glm::vec3& position);
    // ~Window();
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
    glm::vec3 position;

    void setupMesh();
    void loadTexture(const char* texturePath);
    glm::vec3 boundingBoxMin;
    glm::vec3 boundingBoxMax;
};

#endif // WINDOW_H
