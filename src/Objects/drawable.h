// Drawable.h
#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glm/glm.hpp>
#include "../shader.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec4 Color;
};

class Drawable {
public:
    virtual void draw(const Shader& shader) const = 0;
    virtual glm::vec3 getBoundingBoxMin() const = 0;
    virtual glm::vec3 getBoundingBoxMax() const = 0;
};

#endif
