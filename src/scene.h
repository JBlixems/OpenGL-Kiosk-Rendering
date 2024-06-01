// Scene.h
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include "Helpers/FrustrumCulling.h"
#include "Objects/Floor.h"
#include "Objects/Drawable.h"
#include "Objects/Camera.h"
#include "Objects/Window.h"
#include "Objects/NorthWall.h"
#include "Objects/EastWall.h"
#include "Objects/Roof.h"

class Scene {
public:
    Scene();
    void addObject(const std::shared_ptr<Drawable>& object);
    void render(const Shader& shader, const Camera& camera) const;
    void updateFrustum(const glm::mat4& projection, const glm::mat4& view);

private:
    std::vector<std::shared_ptr<Drawable>> objects;
    FrustumCulling frustumCulling;
};

#endif
