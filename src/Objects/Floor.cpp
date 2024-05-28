#include "Floor.h"
#include <iostream>
#include <algorithm>
#include <limits>

Floor::Floor() {
    // Define vertices and indices for the floor
    vertices = {
        // Positions          // Normals          // Texture Coords
        {{-5.0f, 0.0f, -5.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{ 5.0f, 0.0f, -5.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{ 5.0f, 0.0f,  5.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-5.0f, 0.0f,  5.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}
    };
    indices = {
        0, 1, 2,
        2, 3, 0
    };
    setupMesh();
    computeBoundingBox();
    loadTexture("/mnt/c/Users/jfmal/OneDrive/Documents/University/3rd Year/COS344/Homework Assignment/OpenGL-Kiosk-Rendering/src/Materials/HEIN.jpg");
}

Floor::Floor(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    : vertices(vertices), indices(indices) {
    setupMesh();
    computeBoundingBox();
}

void Floor::setupMesh() {
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

    glBindVertexArray(0);
}

void Floor::loadTexture(const std::string& path) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
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

void Floor::draw(const Shader& shader) const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    shader.use();
    shader.setInt("texture_diffuse", 0); 

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

glm::vec3 Floor::getBoundingBoxMin() const {
    return boundingBoxMin;
}

glm::vec3 Floor::getBoundingBoxMax() const {
    return boundingBoxMax;
}

void Floor::computeBoundingBox() {
    glm::vec3 min(std::numeric_limits<float>::max());
    glm::vec3 max(std::numeric_limits<float>::lowest());

    for (const auto& vertex : vertices) {
        min.x = std::min(min.x, vertex.Position.x);
        min.y = std::min(min.y, vertex.Position.y);
        min.z = std::min(min.z, vertex.Position.z);

        max.x = std::max(max.x, vertex.Position.x);
        max.y = std::max(max.y, vertex.Position.y);
        max.z = std::max(max.z, vertex.Position.z);
    }

    boundingBoxMin = min;
    boundingBoxMax = max;
}
