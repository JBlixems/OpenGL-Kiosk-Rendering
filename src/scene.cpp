// Scene.cpp
#include "Scene.h"

Scene::Scene() {
    Floor floor = Floor();
    addObject(std::make_shared<Floor>(floor));
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