#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"
#include "Objects/Floor.h"
#include "Objects/Camera.h"
#include "scene.h"

using namespace glm;
using namespace std;

const float SCREEN_HEIGHT = 1000;
const float SCREEN_WIDTH = 1500;

const char *getError()
{
    const char *errorDescription;
    glfwGetError(&errorDescription);
    return errorDescription;
}

inline void startUpGLFW()
{
    glewExperimental = true; // Needed for core profile
    if (!glfwInit())
    {
        throw getError();
    }
}

inline void startUpGLEW()
{
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        throw getError();
    }
}

inline GLFWwindow *setUp()
{
    startUpGLFW();
    glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
    GLFWwindow *window;                                            // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Kiosk Rendering", NULL, NULL);
    if (window == NULL)
    {
        cout << getError() << endl;
        glfwTerminate();
        throw "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n";
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    startUpGLEW();
    return window;
}

void setupLighting(Shader &shader, int time) {
    glm::vec3 lightDir = glm::vec3(0.0f, sin(time * 24 * 3.14159 / 180), cos(time * 24 * 3.14159 / 180));
    glm::vec3 lightColor = glm::vec3(0.8f*cos(time * 24 * 3.14159 / 180), 0.8f*cos(time * 24 * 3.14159 / 180), 0.8f);

    shader.use();
    shader.setVec3("dirLight.direction", lightDir);
    shader.setVec3("dirLight.ambient", lightColor);
    shader.setVec3("dirLight.diffuse", lightColor);
    shader.setVec3("dirLight.specular", lightColor);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static bool firstMouse = true;
    static float lastX = SCREEN_HEIGHT / 2.0;
    static float lastY = SCREEN_WIDTH / 2.0;

    static Camera* camera = reinterpret_cast<Camera*>(glfwGetWindowUserPointer(window));

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera->processMouseMovement(xoffset, yoffset);
}

// Process keyboard inputs to move the camera
void processInput(GLFWwindow *window, Camera &camera, float deltaTime, float &currentTime)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(GLFW_KEY_W, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(GLFW_KEY_S, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(GLFW_KEY_A, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(GLFW_KEY_D, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.processKeyboard(GLFW_KEY_LEFT_SHIFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.processKeyboard(GLFW_KEY_LEFT_CONTROL, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
        currentTime += 0.1;
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
        currentTime -= 0.1;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    static bool wireframe = false;
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        wireframe = !wireframe;
        if (wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
}

int main()
{
    GLFWwindow *window;
    try{
        window = setUp();
    }
    catch (const char *e){
        cout << e << endl;
        throw;
    }

    Shader shader("vertex.glsl", "fragment.glsl");
    Scene scene;
    Camera camera(glm::vec3(0.0f, 10.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

    glClearColor(0.79f, 0.91f, 0.97f, 1.0f);
    glfwSetKeyCallback(window, key_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetWindowUserPointer(window, &camera);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float currentDayTime = 0;

    double lastTime = glfwGetTime();

    do{
        setupLighting(shader, currentDayTime);

        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        processInput(window, camera, deltaTime, currentDayTime);

        scene.updateFrustum(camera.getProjectionMatrix(), camera.getViewMatrix());
        shader.use();
        shader.setMat4("view", camera.getViewMatrix());
        shader.setMat4("projection", camera.getProjectionMatrix());
        shader.setMat4("model", glm::mat4(1.0f));
        shader.setVec3("viewPos", camera.getPosition());

        scene.render(shader, camera);

        glfwSwapBuffers(window);
        glfwPollEvents();

        lastTime = currentTime;
        // cout << "FPS: " << 1 / deltaTime << endl;

    } while (glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
