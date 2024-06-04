#include "Roof.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

Roof::Roof(float radius, float width, const glm::vec3& position, unsigned int numStrips)
    : radius(radius), width(width), position(position) {

    glm::vec4 opaqueColor = glm::vec4(0.7f, 0.7f, 0.45f, 0.95f);
    glm::vec4 transparentColor = glm::vec4(0.678f, 0.82f, 0.937f, 0.7f);

    float stripWidth = width / numStrips;
    for (unsigned int i = 0; i < numStrips; ++i) {
        glm::vec4 color = (i % 3 != 0) ? opaqueColor : transparentColor;
        addCylinderVertices(radius, stripWidth, position + glm::vec3(0.0f, 0.0f, i * stripWidth), color);
    }

    setupMesh();
    computeBoundingBox();
    loadTexture("/mnt/c/Users/jfmal/OneDrive/Documents/University/3rd Year/COS344/Homework Assignment/OpenGL-Kiosk-Rendering/src/Materials/roof3.png");
}

void Roof::addCylinderVertices(float radius, float width, const glm::vec3& position, const glm::vec4& color) {
    const unsigned int numSegments = 20; // Increase this for a smoother cylinder

    const float PI = 3.14159265358979323846/4;
    float start = 1.14;
    float angleStep = PI / numSegments;

    unsigned int startIdx = vertices.size();

    // Generate vertices for the strip
    for (unsigned int i = 0; i <= numSegments; ++i) {
        float angle = i * angleStep + start;

        glm::vec3 vertexPosition;
        vertexPosition.x = position.x + radius * glm::cos(angle);
        vertexPosition.y = position.y + radius * glm::sin(angle);
        vertexPosition.z = position.z;

        Vertex vertex;
        vertex.Position = vertexPosition;
        vertex.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
        vertex.TexCoords = glm::vec2(0.0f, static_cast<float>(i) / numSegments);
        vertex.Color = color;

        vertices.push_back(vertex);
    }

    // Generate vertices for the strip on the other side of the width
    for (unsigned int i = 0; i <= numSegments; ++i) {
        float angle = i * angleStep + start;

        glm::vec3 vertexPosition;
        vertexPosition.x = position.x + radius * glm::cos(angle);
        vertexPosition.y = position.y + radius * glm::sin(angle);
        vertexPosition.z = position.z + width;

        Vertex vertex;
        vertex.Position = vertexPosition;
        vertex.Normal = glm::vec3(0.0f, 1.0f, 0.0f);
        vertex.TexCoords = glm::vec2(1.0f, static_cast<float>(i) / numSegments);
        vertex.Color = color;

        vertices.push_back(vertex);
    }

    // Add two triangles for each segment
    for (unsigned int i = 0; i < numSegments; ++i) {
        indices.push_back(startIdx + i);
        indices.push_back(startIdx + i + 1);
        indices.push_back(startIdx + i + numSegments + 1);

        indices.push_back(startIdx + i + 1);
        indices.push_back(startIdx + i + numSegments + 2);
        indices.push_back(startIdx + i + numSegments + 1);
    }
}

void Roof::draw(const Shader& shader) const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    shader.use();

    // Set material properties
    glm::vec3 matAmbient = glm::vec3(0.5f, 0.5f, 0.5f);  // Grey ambient color
    glm::vec3 matDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);  // Grey diffuse color
    glm::vec3 matSpecular = glm::vec3(0.5f, 0.5f, 0.5f); // Grey specular color
    float matShininess = 100.0f;  // Shininess factor

    shader.setVec3("material.ambient", matAmbient);
    shader.setVec3("material.diffuse", matDiffuse);
    shader.setVec3("material.specular", matSpecular);
    shader.setFloat("material.shininess", matShininess);

    shader.setInt("texture_diffuse", 0); 
    shader.setBool("useColor", false);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Roof::setupMesh() {
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

void Roof::loadTexture(const char* path) {
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
void Roof::computeBoundingBox() {
    boundingBoxMin = position - glm::vec3(-80.0f, -80.0f, -80.0f);
    boundingBoxMax = position + glm::vec3(80.0f, 80.0f, 80.0f);
}

// Function to get minimum bounding box coordinates
glm::vec3 Roof::getBoundingBoxMin() const {
    return boundingBoxMin;
}

// Function to get maximum bounding box coordinates
glm::vec3 Roof::getBoundingBoxMax() const {
    return boundingBoxMax;
}