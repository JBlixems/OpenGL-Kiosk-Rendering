// Scene.cpp
#include "Scene.h"
#include <iostream>

Scene::Scene() {
    Floor floor = Floor();
    Window window = Window(1.0f, 1.0f, 0.1f, glm::vec3(0.0f, 0.0f, 0.0f));

    addObject(std::make_shared<Floor>(floor));
    addObject(std::make_shared<Window>(window));
}

void Scene::addObject(const std::shared_ptr<Drawable>& object) {
    objects.push_back(object);
}

void Scene::render(const Shader& shader, const Camera& camera) const {
    for (const auto& object : objects) {
        if (frustumCulling.isBoxInFrustum(object->getBoundingBoxMin(), object->getBoundingBoxMax())) {
            object->draw(shader);
        }
    }
}

void Scene::updateFrustum(const glm::mat4& projection, const glm::mat4& view) {
    frustumCulling.updateFrustum(projection, view);
}