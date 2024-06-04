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

    //East wall
    EastWall eastWall1 = EastWall(12.5f, 19.0f, 1.0f, glm::vec3(-5.8f, 1.0f, 29.7f));
    addObject(std::make_shared<EastWall>(eastWall1));

    EastWall eastWall2 = EastWall(4.0f, 16.0f, 1.0f, glm::vec3(-13.7f, 1.0f, 29.7f));
    addObject(std::make_shared<EastWall>(eastWall2));

    EastWall eastWall3 = EastWall(4.0f, 16.0f, 1.0f, glm::vec3(9.72f, 1.0f, 29.7f));
    addObject(std::make_shared<EastWall>(eastWall3));

    PlainPrism eastWall4 = PlainPrism(3.4f, 3.0f, 1.0f, glm::vec3(7.75f, 4.7f, 29.9f), glm::vec4(0.4, 0.4, 0.4, 1));
    addObject(std::make_shared<PlainPrism>(eastWall4));

    PlainPrism eastWall5 = PlainPrism(3.4f, 3.0f, 1.0f, glm::vec3(-8.25f, 4.7f, 29.9f), glm::vec4(0.4, 0.4, 0.4, 1));
    addObject(std::make_shared<PlainPrism>(eastWall5));

    //West wall
    EastWall westWall2 = EastWall(4.0f, 16.0f, 1.0f, glm::vec3(-13.7f, 1.0f, -29.7f));
    addObject(std::make_shared<EastWall>(westWall2));

    EastWall westWall3 = EastWall(4.0f, 16.0f, 1.0f, glm::vec3(9.72f, 1.0f, -29.7f));
    addObject(std::make_shared<EastWall>(westWall3));

    //Roof
    Roof roof = Roof(50.0f, 62.0f, glm::vec3(0.0f, -33.5f, -32.0f), 60);
    addObject(std::make_shared<Roof>(roof));

    //White walls
    WhiteWall whiteWall1 = WhiteWall(2.0f, 2.6f, 0.25f, glm::vec3(1.0f, 1.3f, -15.0f));
    addObject(std::make_shared<WhiteWall>(whiteWall1));
    WhiteWall whiteWall2 = WhiteWall(2.0f, 2.6f, 0.25f, glm::vec3(3.0f, 1.3f, -15.0f));
    addObject(std::make_shared<WhiteWall>(whiteWall2));

    WhiteWall whiteWall3 = WhiteWall(0.25f, 2.6f, 2.0f, glm::vec3(-1.0f, 1.3f, -20.0f));
    addObject(std::make_shared<WhiteWall>(whiteWall3));
    WhiteWall whiteWall4 = WhiteWall(0.25f, 2.6f, 2.0f, glm::vec3(-1.0f, 1.3f, -22.0f));
    addObject(std::make_shared<WhiteWall>(whiteWall4));

    WhiteWall whiteWall5 = WhiteWall(2.0f, 2.6f, 0.25f, glm::vec3(-1.0f, 1.3f, -9.0f));
    addObject(std::make_shared<WhiteWall>(whiteWall5));
    WhiteWall whiteWall6 = WhiteWall(2.0f, 2.6f, 0.25f, glm::vec3(1.0f, 1.3f, -9.0f));
    addObject(std::make_shared<WhiteWall>(whiteWall6));
    WhiteWall whiteWall7 = WhiteWall(2.0f, 2.6f, 0.25f, glm::vec3(3.0f, 1.3f, -9.0f));
    addObject(std::make_shared<WhiteWall>(whiteWall7));

    WhiteWall whiteWall8 = WhiteWall(2.0f, 2.6f, 0.25f, glm::vec3(2.0f, 1.3f, -2.0f));
    addObject(std::make_shared<WhiteWall>(whiteWall8));
    WhiteWall whiteWall9 = WhiteWall(2.0f, 2.6f, 0.25f, glm::vec3(4.0f, 1.3f, -2.0f));
    addObject(std::make_shared<WhiteWall>(whiteWall9));

    WhiteWall whiteWall10 = WhiteWall(2.0f, 2.6f, 0.25f, glm::vec3(0.0f, 1.3f, 9.0f));
    addObject(std::make_shared<WhiteWall>(whiteWall10));
    WhiteWall whiteWall11 = WhiteWall(2.0f, 2.6f, 0.25f, glm::vec3(2.0f, 1.3f, 9.0f));
    addObject(std::make_shared<WhiteWall>(whiteWall11));

    WhiteWall whiteWall12 = WhiteWall(0.25f, 2.6f, 2.0f, glm::vec3(-2.0f, 1.3f, 4.0f));
    addObject(std::make_shared<WhiteWall>(whiteWall12));
    WhiteWall whiteWall13 = WhiteWall(0.25f, 2.6f, 2.0f, glm::vec3(-2.0f, 1.3f, 6.0f));
    addObject(std::make_shared<WhiteWall>(whiteWall13));

    WhiteWall whiteWall14 = WhiteWall(0.25f, 2.6f, 2.0f, glm::vec3(-1.0f, 1.3f, 16.0f));
    addObject(std::make_shared<WhiteWall>(whiteWall14));
    WhiteWall whiteWall15 = WhiteWall(0.25f, 2.6f, 2.0f, glm::vec3(-1.0f, 1.3f, 18.0f));
    addObject(std::make_shared<WhiteWall>(whiteWall15));

    //Tables
    Table table1 = Table(0.6f, 1.6f, 0.5f, glm::vec3(-3.0f, 0.8f, 27.5f), true);
    addObject(std::make_shared<Table>(table1));
    Table table2 = Table(0.6f, 1.6f, 0.5f, glm::vec3(2.0f, 0.8f, 27.5f), true);
    addObject(std::make_shared<Table>(table2));
    Table table3 = Table(1.0f, 0.6f, 0.5f, glm::vec3(1.0f, 0.3f, 18.5f), false);
    addObject(std::make_shared<Table>(table3));
    Table table4 = Table(1.2f, 0.6f, 0.5f, glm::vec3(0.0f, 0.3f, 6.5f), false);
    addObject(std::make_shared<Table>(table4));
    Table table5 = Table(1.2f, 0.6f, 0.5f, glm::vec3(2.0f, 0.3f, -3.5f), false);
    addObject(std::make_shared<Table>(table5));
    Table table6 = Table(1.0f, 0.6f, 0.5f, glm::vec3(4.0f, 0.3f, -12.0f), false);
    addObject(std::make_shared<Table>(table6));
    Table table7 = Table(1.0f, 0.6f, 0.5f, glm::vec3(-1.0f, 0.3f, -11.0f), false);
    addObject(std::make_shared<Table>(table7));
    Table table8 = Table(1.2f, 0.6f, 0.5f, glm::vec3(2.0f, 0.3f, -17.5f), false);
    addObject(std::make_shared<Table>(table8));

    //PlantPots
    PlantPot plantPot1 = PlantPot(0.6f, 1.5f, 0.6f, glm::vec3(0.2f, 0.0f, 10.0f));
    addObject(std::make_shared<PlantPot>(plantPot1));
    PlantPot plantPot2 = PlantPot(0.6f, 1.5f, 0.6f, glm::vec3(1.7f, 0.0f, 10.0f));
    addObject(std::make_shared<PlantPot>(plantPot2));

    PlantPot plantPot3 = PlantPot(0.6f, 1.5f, 0.6f, glm::vec3(2.2f, 0.0f, -1.0f));
    addObject(std::make_shared<PlantPot>(plantPot3));
    PlantPot plantPot4 = PlantPot(0.6f, 1.5f, 0.6f, glm::vec3(3.7f, 0.0f, -1.0f));
    addObject(std::make_shared<PlantPot>(plantPot4));

    PlantPot plantPot5 = PlantPot(0.6f, 1.5f, 0.6f, glm::vec3(0.7f, 0.0f, -13.8f));
    addObject(std::make_shared<PlantPot>(plantPot5));
    PlantPot plantPot6 = PlantPot(0.6f, 1.5f, 0.6f, glm::vec3(3.7f, 0.0f, -9.7f));
    addObject(std::make_shared<PlantPot>(plantPot6));

    PlantPot plantPot7 = PlantPot(0.6f, 1.5f, 0.6f, glm::vec3(-2.0f, 0.0f, -19.0f));
    addObject(std::make_shared<PlantPot>(plantPot7));
    PlantPot plantPot8 = PlantPot(0.6f, 1.5f, 0.6f, glm::vec3(-2.0f, 0.0f, -20.5f));
    addObject(std::make_shared<PlantPot>(plantPot8));

    //Cafeteria
    PlainPrism cafeteriaTable1 = PlainPrism(8.0f, 1.4f, 1.0f, glm::vec3(-0.5f, 0.0f, -28.0f), glm::vec4(0.3, 0.3, 0.3, 1));
    addObject(std::make_shared<PlainPrism>(cafeteriaTable1));
    PlainPrism cafeteriaTable2 = PlainPrism(1.0f, 1.4f, 3.0f, glm::vec3(3.5f, 0.0f, -30.0f), glm::vec4(0.3, 0.3, 0.3, 1));
    addObject(std::make_shared<PlainPrism>(cafeteriaTable2));
    PlainPrism cafeteriaTable3 = PlainPrism(10.0f, 3.0f, 0.2f, glm::vec3(-0.1f, 1.5f, -30.0f), glm::vec4(0.02, 0.02, 0.02, 1));
    addObject(std::make_shared<PlainPrism>(cafeteriaTable3));
    PlainPrism cafeteriaTable4 = PlainPrism(8.0f, 1.5f, 0.2f, glm::vec3(-0.1f, 2.0f, -29.7f), glm::vec4(0.2, 0.2, 0.2, 1));
    addObject(std::make_shared<PlainPrism>(cafeteriaTable4));

    PlainPrism cafeteriaTable5 = PlainPrism(0.6f, 0.6f, 0.8f, glm::vec3(3.5f, 0.8f, -29.0f), glm::vec4(0.7, 0.3, 0.3, 1));
    addObject(std::make_shared<PlainPrism>(cafeteriaTable5));

    //White floor underneath
    PlainPrism whiteFloor = PlainPrism(30.0f, 0.1f, 60.0f, glm::vec3(0.0f, -1.2f, -40.0f), glm::vec4(0.5, 0.5, 0.5, 1));
    addObject(std::make_shared<PlainPrism>(whiteFloor));

    //Black side walls
    PlainPrism blackWall1 = PlainPrism(30.0f, 25.0f, 0.1f, glm::vec3(0.0f, 6.5f, -32.0f), glm::vec4(0.3, 0.3, 0.3, 1));
    addObject(std::make_shared<PlainPrism>(blackWall1));
    PlainPrism blackWall55 = PlainPrism(30.0f, 4.0f, 1.0f, glm::vec3(0.0f, 10.5f, -32.0f), glm::vec4(0.6, 0.6, 0.6, 1));
    addObject(std::make_shared<PlainPrism>(blackWall55));
    PlainPrism blackWall56 = PlainPrism(30.0f, 4.0f, 1.0f, glm::vec3(0.0f, 4.5f, -32.0f), glm::vec4(0.6, 0.6, 0.6, 1));
    addObject(std::make_shared<PlainPrism>(blackWall56));

    PlainPrism blackWall2 = PlainPrism(30.0f, 25.0f, 0.1f, glm::vec3(0.0f, 6.5f, 35.0f), glm::vec4(0.1, 0.1, 0.1, 1));
    addObject(std::make_shared<PlainPrism>(blackWall2));
    PlainPrism blackWall3 = PlainPrism(0.1f, 25.0f, 80.0f, glm::vec3(15.0f, 3.5f, -35.0f), glm::vec4(0.1, 0.1, 0.1, 1));
    addObject(std::make_shared<PlainPrism>(blackWall3));
    PlainPrism blackWall4 = PlainPrism(0.1f, 25.0f, 80.0f, glm::vec3(-15.0f, 3.5f, -35.0f), glm::vec4(0.1, 0.1, 0.1, 1));
    addObject(std::make_shared<PlainPrism>(blackWall4));

    //Chairs
    Chair chair1 = Chair(0.7f, 1.3f, 0.7f, glm::vec3(-3.0f, 1.1f, 26.0f), glm::vec4(0.3, 0.3, 0.3, 1));
    addObject(std::make_shared<Chair>(chair1));

    Chair chair2 = Chair(0.7f, 1.3f, 0.7f, glm::vec3(-1.0f, 1.1f, 26.0f), glm::vec4(0.3, 0.3, 0.3, 1));
    addObject(std::make_shared<Chair>(chair2));

    Chair chair3 = Chair(0.7f, 1.3f, 0.7f, glm::vec3(3.0f, 1.1f, 26.0f), glm::vec4(0.3, 0.3, 0.3, 1));
    addObject(std::make_shared<Chair>(chair3));





    //Windows
    //Add many small windows on north wall
    for (int i = 0; i < 60; i++){
        Window window = Window(0.1f, 0.6f, 1.0f, glm::vec3(12.0f, 6.85f, -30.0f + i), false, false, true);
        addObject(std::make_shared<Window>(window));
    }

    for (int i = 0; i < 60; i++){
        Window window = Window(0.1f, 0.9f, 1.0f, glm::vec3(12.19f, 11.0f, -30.0f + i), false, false, true);
        addObject(std::make_shared<Window>(window));
    }

    //Add many small windows on south wall
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

    currentH = 0.8f;
    for (int i = 0; i < 8; i++)
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
        if (frustumCulling.isBoxInFrustum(object->getBoundingBoxMin(), object->getBoundingBoxMax()) || dynamic_cast<Roof*>(object.get()) != nullptr || dynamic_cast<PlainPrism*>(object.get()) != nullptr) {
            object->draw(shader);
            drawing++;
        }
    }
    std::cout << "Drawing " << drawing << " objects" << std::endl;
}

void Scene::updateFrustum(const glm::mat4& projection, const glm::mat4& view) {
    frustumCulling.updateFrustum(projection, view);
}