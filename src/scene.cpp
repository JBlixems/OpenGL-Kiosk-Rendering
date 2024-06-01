// Scene.cpp
#include "Scene.h"
#include <iostream>

Scene::Scene() {
    Floor floor = Floor();
    addObject(std::make_shared<Floor>(floor));

    //North wall
    NorthWall northWall1 = NorthWall(0.1f, 0.7f, 60.0f, glm::vec3(10.25f, 0.75f, 0.0f), 70.0f, true);
    addObject(std::make_shared<NorthWall>(northWall1));
    NorthWall northWall2 = NorthWall(0.1f, 0.7f, 60.0f, glm::vec3(10.25f, 2.4f, 0.0f), -70.0f, true);
    addObject(std::make_shared<NorthWall>(northWall2));
    NorthWall northWall3 = NorthWall(0.1f, 1.2f, 60.0f, glm::vec3(10.55f, 4.85f, 0.0f), 70.0f, true);
    addObject(std::make_shared<NorthWall>(northWall3));
    NorthWall northWall4 = NorthWall(0.1f, 1.2f, 60.0f, glm::vec3(11.75f, 6.49f, 0.0f), 0.0f, true);
    addObject(std::make_shared<NorthWall>(northWall4));
    NorthWall northWall5 = NorthWall(0.1f, 1.2f, 60.0f, glm::vec3(11.0f, 8.85f, 0.0f), 70.0f, true);
    addObject(std::make_shared<NorthWall>(northWall5));
    NorthWall northWall6 = NorthWall(0.1f, 1.8f, 60.0f, glm::vec3(11.15f, 7.21f, 0.0f), 0.0f, true);
    addObject(std::make_shared<NorthWall>(northWall6));
    NorthWall northWall7 = NorthWall(0.1f, 1.2f, 60.0f, glm::vec3(12.19f, 10.5f, 0.0f), 0.0f, true);
    addObject(std::make_shared<NorthWall>(northWall7));
    NorthWall northWall8 = NorthWall(0.1f, 1.2f, 60.0f, glm::vec3(12.19f, 11.5f, 0.0f), 0.0f, true);
    addObject(std::make_shared<NorthWall>(northWall8));
    NorthWall northWall9 = NorthWall(0.1f, 0.8f, 60.0f, glm::vec3(11.89f, 13.2f, 0.0f), 80.0f, true);
    addObject(std::make_shared<NorthWall>(northWall9));

    //Add many small windows
    for (int i = 0; i < 60; i++){
        Window window = Window(0.1f, 0.6f, 1.0f, glm::vec3(12.0f, 6.85f, -30.0f + i), false, false, true);
        addObject(std::make_shared<Window>(window));
    }

    for (int i = 0; i < 60; i++){
        Window window = Window(0.1f, 0.9f, 1.0f, glm::vec3(12.19f, 11.0f, -30.0f + i), false, false, true);
        addObject(std::make_shared<Window>(window));
    }
    
    //South wall
    NorthWall southWall1 = NorthWall(0.1f, 0.7f, 60.0f, glm::vec3(-10.25f, 0.75f, 0.0f), -70.0f, false);
    addObject(std::make_shared<NorthWall>(southWall1));
    NorthWall southWall2 = NorthWall(0.1f, 0.7f, 60.0f, glm::vec3(-10.25f, 2.4f, 0.0f), 70.0f, false);
    addObject(std::make_shared<NorthWall>(southWall2));
    NorthWall southWall3 = NorthWall(0.1f, 1.2f, 60.0f, glm::vec3(-10.55f, 4.85f, 0.0f), -70.0f, false);
    addObject(std::make_shared<NorthWall>(southWall3));
    NorthWall southWall4 = NorthWall(0.1f, 1.2f, 60.0f, glm::vec3(-11.75f, 6.49f, 0.0f), 0.0f, false);
    addObject(std::make_shared<NorthWall>(southWall4));
    NorthWall southWall5 = NorthWall(0.1f, 1.2f, 60.0f, glm::vec3(-11.0f, 8.85f, 0.0f), -70.0f, false);
    addObject(std::make_shared<NorthWall>(southWall5));
    NorthWall southWall6 = NorthWall(0.1f, 1.8f, 60.0f, glm::vec3(-11.15f, 7.21f, 0.0f), 0.0f, false);
    addObject(std::make_shared<NorthWall>(southWall6));
    NorthWall southWall7 = NorthWall(0.1f, 1.2f, 60.0f, glm::vec3(-12.19f, 10.5f, 0.0f), 0.0f, false);
    addObject(std::make_shared<NorthWall>(southWall7));
    NorthWall southWall8 = NorthWall(0.1f, 1.2f, 60.0f, glm::vec3(-12.19f, 11.5f, 0.0f), 0.0f, false);
    addObject(std::make_shared<NorthWall>(southWall8));
    NorthWall southWall9 = NorthWall(0.1f, 0.8f, 60.0f, glm::vec3(-11.89f, 13.2f, 0.0f), -80.0f, false);
    addObject(std::make_shared<NorthWall>(southWall9));

    //Add many small windows
    for (int i = 0; i < 60; i++){
        Window window = Window(0.1f, 0.6f, 1.0f, glm::vec3(-12.0f, 6.85f, -30.0f + i), false, false, true);
        addObject(std::make_shared<Window>(window));
    }

    for (int i = 0; i < 60; i++){
        Window window = Window(0.1f, 0.9f, 1.0f, glm::vec3(-12.19f, 11.0f, -30.0f + i), false, false, true);
        addObject(std::make_shared<Window>(window));
    }

    //Windows on the floor
    //Set 1
    Window windowSet11 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, 2.85f), true, false, false);
    Window windowSet12 = Window(0.1f, 1.2f, 5.1f, glm::vec3(-6.93f, 0.65f, 2.85f), false, false, false);
    Window windowSet13 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, 7.95f), true, false, false);

    addObject(std::make_shared<Window>(windowSet11));
    addObject(std::make_shared<Window>(windowSet13));
    addObject(std::make_shared<Window>(windowSet12));

    //Set 2
    Window windowSet21 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, 9.35f), true, false, false);
    Window windowSet22 = Window(0.1f, 1.2f, 5.1f, glm::vec3(-6.93f, 0.65f, 9.35f), false, false, false);
    Window windowSet23 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, 14.45f), true, false, false);

    addObject(std::make_shared<Window>(windowSet21));
    addObject(std::make_shared<Window>(windowSet23));
    addObject(std::make_shared<Window>(windowSet22));

    //Set 3
    Window windowSet31 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, -3.65f), true, false, false);
    Window windowSet32 = Window(0.1f, 1.2f, 5.1f, glm::vec3(-6.93f, 0.65f, -3.65f), false, false, false);
    Window windowSet33 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, 1.45f), true, false, false);

    addObject(std::make_shared<Window>(windowSet31));
    addObject(std::make_shared<Window>(windowSet33));
    addObject(std::make_shared<Window>(windowSet32));

    //Set 4
    Window windowSet41 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, -10.15f), true, false, false);
    Window windowSet42 = Window(0.1f, 1.2f, 5.1f, glm::vec3(-6.93f, 0.65f, -10.15f), false, false, false);
    Window windowSet43 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, -5.05f), true, false, false);

    addObject(std::make_shared<Window>(windowSet41));
    addObject(std::make_shared<Window>(windowSet43));
    addObject(std::make_shared<Window>(windowSet42));

    //Set 5
    Window windowSet51 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, -16.65f), true, false, false);
    Window windowSet52 = Window(0.1f, 1.2f, 5.1f, glm::vec3(-6.93f, 0.65f, -16.65f), false, false, false);
    Window windowSet53 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, -11.55f), true, false, false);

    addObject(std::make_shared<Window>(windowSet51));
    addObject(std::make_shared<Window>(windowSet53));
    addObject(std::make_shared<Window>(windowSet52));

    //Set 6
    Window windowSet61 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, -23.15f), true, false, false);
    Window windowSet62 = Window(0.1f, 1.2f, 5.1f, glm::vec3(-6.93f, 0.65f, -23.15f), false, false, false);
    Window windowSet63 = Window(3.1f, 1.2f, 0.1f, glm::vec3(-8.43f, 0.65f, -18.05f), true, false, false);

    addObject(std::make_shared<Window>(windowSet61));
    addObject(std::make_shared<Window>(windowSet63));
    addObject(std::make_shared<Window>(windowSet62));

    //East wall
    EastWall eastWall1 = EastWall(12.5f, 19.0f, 1.0f, glm::vec3(-5.8f, 1.0f, 29.7f));
    addObject(std::make_shared<EastWall>(eastWall1));

    EastWall eastWall2 = EastWall(4.0f, 16.0f, 1.0f, glm::vec3(-13.7f, 1.0f, 29.7f));
    addObject(std::make_shared<EastWall>(eastWall2));

    EastWall eastWall3 = EastWall(4.0f, 16.0f, 1.0f, glm::vec3(9.72f, 1.0f, 29.7f));
    addObject(std::make_shared<EastWall>(eastWall3));

    float currentH = 7.0f;
    for (int i = 0; i < 6; i++)
    {
        float height = 1.5f + (i%2);
        float width = 1.58f;
        if((i%2) == 1){
            height += 0.2f;
            Window wind1 = Window(width, height, 0.2f, glm::vec3(-9.1f, currentH + 0.6f, 30.3f), true, true, false);
            Window wind2 = Window(width, height, 0.2f, glm::vec3(-9.1f + width + 0.1, currentH + 0.6f, 30.3f), true, true, false);
            addObject(std::make_shared<Window>(wind1));
            addObject(std::make_shared<Window>(wind2));
        }else{
            Window wind1 = Window(width, height, 0.2f, glm::vec3(-9.1f, currentH, 30.3f), true, true, false);
            Window wind2 = Window(width, height, 0.2f, glm::vec3(-9.1f + width + 0.1, currentH, 30.3f), true, true, false);
            addObject(std::make_shared<Window>(wind1));
            addObject(std::make_shared<Window>(wind2));
        }

        currentH += height;
    }

    currentH = 7.0f;
    for (int i = 0; i < 6; i++)
    {
        float height = 1.5f + (i%2);
        float width = 1.58f;
        if((i%2) == 1){
            height += 0.2f;
            Window wind1 = Window(width, height, 0.2f, glm::vec3(6.92f, currentH + 0.6f, 30.3f), true, true, false);
            Window wind2 = Window(width, height, 0.2f, glm::vec3(6.92f + width + 0.1, currentH + 0.6f, 30.3f), true, true, false);
            addObject(std::make_shared<Window>(wind1));
            addObject(std::make_shared<Window>(wind2));
        }else{
            Window wind1 = Window(width, height, 0.2f, glm::vec3(6.92f, currentH, 30.3f), true, true, false);
            Window wind2 = Window(width, height, 0.2f, glm::vec3(6.92f + width + 0.1, currentH, 30.3f), true, true, false);
            addObject(std::make_shared<Window>(wind1));
            addObject(std::make_shared<Window>(wind2));
        }

        currentH += height;
    }

    //West wall
    EastWall westWall2 = EastWall(4.0f, 16.0f, 1.0f, glm::vec3(-13.7f, 1.0f, -29.7f));
    addObject(std::make_shared<EastWall>(westWall2));

    EastWall westWall3 = EastWall(4.0f, 16.0f, 1.0f, glm::vec3(9.72f, 1.0f, -29.7f));
    addObject(std::make_shared<EastWall>(westWall3));

    currentH = 0.8f;
    for (int i = 0; i < 10; i++)
    {
        float height = 1.5f + (i%2);
        float width = 1.61f;

        if((i%2) == 1){
            height += 0.2f;
        }
        for (int j = 0; j < 12; j++)
        {
            if((i%2) == 1){
                Window wind1 = Window(width, height, 0.2f, glm::vec3(-9.1f + width*j, currentH + 0.6f, -30.3f), true, true, false);
                addObject(std::make_shared<Window>(wind1));
            }else{
                Window wind1 = Window(width, height, 0.2f, glm::vec3(-9.1f + width*j, currentH, -30.3f), true, true, false);
                addObject(std::make_shared<Window>(wind1));
            }

        }
        currentH += height;
    }
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