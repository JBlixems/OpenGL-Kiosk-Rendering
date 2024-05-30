// Scene.cpp
#include "Scene.h"
#include <iostream>

Scene::Scene() {
    Floor floor = Floor();
    addObject(std::make_shared<Floor>(floor));

    //Set 1
    Window windowSet11 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, 2.85f), true, false);
    Window windowSet12 = Window(0.1f, 1.2f, 5.1f, glm::vec3(-6.93f, 0.65f, 2.85f), false, false);
    Window windowSet13 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, 7.95f), true, false);

    addObject(std::make_shared<Window>(windowSet11));
    addObject(std::make_shared<Window>(windowSet13));
    addObject(std::make_shared<Window>(windowSet12));

    //Set 2
    Window windowSet21 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, 9.35f), true, false);
    Window windowSet22 = Window(0.1f, 1.2f, 5.1f, glm::vec3(-6.93f, 0.65f, 9.35f), false, false);
    Window windowSet23 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, 14.45f), true, false);

    addObject(std::make_shared<Window>(windowSet21));
    addObject(std::make_shared<Window>(windowSet23));
    addObject(std::make_shared<Window>(windowSet22));

    //Set 3
    Window windowSet31 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, -3.65f), true, false);
    Window windowSet32 = Window(0.1f, 1.2f, 5.1f, glm::vec3(-6.93f, 0.65f, -3.65f), false, false);
    Window windowSet33 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, 1.45f), true, false);

    addObject(std::make_shared<Window>(windowSet31));
    addObject(std::make_shared<Window>(windowSet33));
    addObject(std::make_shared<Window>(windowSet32));

    //Set 4
    Window windowSet41 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, -10.15f), true, false);
    Window windowSet42 = Window(0.1f, 1.2f, 5.1f, glm::vec3(-6.93f, 0.65f, -10.15f), false, false);
    Window windowSet43 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, -5.05f), true, false);

    addObject(std::make_shared<Window>(windowSet41));
    addObject(std::make_shared<Window>(windowSet43));
    addObject(std::make_shared<Window>(windowSet42));

    //Set 5
    Window windowSet51 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, -16.65f), true, false);
    Window windowSet52 = Window(0.1f, 1.2f, 5.1f, glm::vec3(-6.93f, 0.65f, -16.65f), false, false);
    Window windowSet53 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, -11.55f), true, false);

    addObject(std::make_shared<Window>(windowSet51));
    addObject(std::make_shared<Window>(windowSet53));
    addObject(std::make_shared<Window>(windowSet52));

    //Set 6
    Window windowSet61 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, -23.15f), true, false);
    Window windowSet62 = Window(0.1f, 1.2f, 5.1f, glm::vec3(-6.93f, 0.65f, -23.15f), false, false);
    Window windowSet63 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, -18.05f), true, false);

    addObject(std::make_shared<Window>(windowSet61));
    addObject(std::make_shared<Window>(windowSet63));
    addObject(std::make_shared<Window>(windowSet62));

    //North wall
    NorthWall northWall = NorthWall(0.1f, 40.0f, 60.0f, glm::vec3(8.43f, 0.65f, -23.15f));
    addObject(std::make_shared<NorthWall>(northWall));
}

void Scene::addObject(const std::shared_ptr<Drawable>& object) {
    objects.push_back(object);
}

void Scene::render(const Shader& shader, const Camera& camera) const {
    int drawing = 0;
    for (const auto& object : objects) {
        if (frustumCulling.isBoxInFrustum(object->getBoundingBoxMin(), object->getBoundingBoxMax())) {
            object->draw(shader);
            drawing++;
        }
    }
    std::cout << "Drawing " << drawing << " objects" << std::endl;
}

void Scene::updateFrustum(const glm::mat4& projection, const glm::mat4& view) {
    frustumCulling.updateFrustum(projection, view);
}