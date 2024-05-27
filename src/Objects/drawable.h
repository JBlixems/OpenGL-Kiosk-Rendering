// Drawable.h
#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <glm/glm.hpp>
#include "../shader.hpp"

class Drawable {
public:
    virtual void draw(const Shader& shader) const = 0;
    virtual glm::vec3 getBoundingBoxMin() const = 0;
    virtual glm::vec3 getBoundingBoxMax() const = 0;
};

#endif
