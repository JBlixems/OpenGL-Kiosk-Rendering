#include "Window.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

Window::Window(float width, float height, float depth, const glm::vec3& position)
    : width(width), height(height), depth(depth), position(position) {

    glm::vec4 color = glm::vec4(0.5f, 1.0f, 1.0f, 0.4f); // Light blue color
    glm::vec4 frameColor = glm::vec4(0.75f, 0.75f, 0.75f, 1.0f); // Silver frame color

    // Vertices for the window
    vertices = {
        // Front face
        {{-width, -height, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, color},
        {{ width, -height, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, color},
        {{ width,  height, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, color},
        {{-width,  height, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, color},

        // Back face
        {{-width, -height, depth}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, color},
        {{ width, -height, depth}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, color},
        {{ width,  height, depth}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, color},
        {{-width,  height, depth}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, color}
    };

    // Vertices for the frame
    float frameDepth = depth + depth*1.5;

    float frameTop = height + 1;
    float frameBottom = -height - 1;

    // Front face of the top frame
    vertices.push_back({{-width, frameTop, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, frameColor});
    vertices.push_back({{ width, frameTop, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, frameColor});
    vertices.push_back({{ width, frameTop, frameDepth}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, frameColor});
    vertices.push_back({{-width, frameTop, frameDepth}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, frameColor});

    // Front face of the bottom frame
    vertices.push_back({{-width, frameBottom, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, frameColor});
    vertices.push_back({{ width, frameBottom, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, frameColor});
    vertices.push_back({{ width, frameBottom, frameDepth}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, frameColor});
    vertices.push_back({{-width, frameBottom, frameDepth}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, frameColor});

    // Side faces of the frame
    vertices.push_back({{-width, frameTop, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, frameColor});
    vertices.push_back({{-width, frameBottom, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, frameColor});
    vertices.push_back({{-width, frameBottom, frameDepth}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, frameColor});
    vertices.push_back({{-width, frameTop, frameDepth}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, frameColor});

    vertices.push_back({{width, frameTop, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, frameColor});
    vertices.push_back({{width, frameBottom, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, frameColor});
    vertices.push_back({{width, frameBottom, frameDepth}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, frameColor});
    vertices.push_back({{width, frameTop, frameDepth}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, frameColor});

    // Update indices for the window with frame
    int numVerticesWithoutFrame = 8;
    int numVerticesWithFrame = vertices.size();

    for (int i = numVerticesWithoutFrame; i < numVerticesWithFrame; i += 4) {
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
        indices.push_back(i + 2);
        indices.push_back(i + 3);
        indices.push_back(i);
    }

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);

    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(6);
    indices.push_back(6);
    indices.push_back(7);
    indices.push_back(4);


    setupMesh();
    computeBoundingBox();
    loadTexture("/mnt/c/Users/jfmal/OneDrive/Documents/University/3rd Year/COS344/Homework Assignment/OpenGL-Kiosk-Rendering/src/Materials/carpet.jpg");
}

void Window::draw(const Shader& shader) const {
    shader.use();

    // Set material properties
    glm::vec3 matAmbient = glm::vec3(0.5f, 0.5f, 0.5f);  // Grey ambient color
    glm::vec3 matDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);  // Grey diffuse color
    glm::vec3 matSpecular = glm::vec3(0.5f, 0.5f, 0.5f); // Grey specular color
    float matShininess = 10.0f;  // Shininess factor

    shader.setVec3("material.ambient", matAmbient);
    shader.setVec3("material.diffuse", matDiffuse);
    shader.setVec3("material.specular", matSpecular);
    shader.setFloat("material.shininess", matShininess);

    shader.setInt("texture_diffuse", 0); 
    shader.setBool("useColor", true);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Window::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // Vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    // Vertex Texture Coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    // Vertex Colors
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

    glBindVertexArray(0);

}

void Window::loadTexture(const char* path) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        std::cout << "Texture loaded: " << path << " (" << width << "x" << height << ", " << nrComponents << " components)" << std::endl;

        stbi_image_free(data);
    } else {
        std::cout << "Failed to load texture: " << path << std::endl;
        std::cout << "Error: " << stbi_failure_reason() << std::endl;
        stbi_image_free(data);
    }
}

// Function to compute bounding box of the window
void Window::computeBoundingBox() {
    boundingBoxMin = position - glm::vec3(width / 2.0f, height / 2.0f, depth / 2.0f);
    boundingBoxMax = position + glm::vec3(width / 2.0f, height / 2.0f, depth / 2.0f);
}

// Function to get minimum bounding box coordinates
glm::vec3 Window::getBoundingBoxMin() const {
    return boundingBoxMin;
}

// Function to get maximum bounding box coordinates
glm::vec3 Window::getBoundingBoxMax() const {
    return boundingBoxMax;
}