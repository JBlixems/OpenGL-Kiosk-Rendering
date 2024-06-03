#include "Table.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cmath>

Table::Table(float width, float height, float depth, const glm::vec3& position, bool diff)
    : width(width), height(height), depth(depth), position(position) {

    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;

    glm::vec4 plainGrey(0.95, 0.95, 0.95, 1);

    glm::vec4 selectedColor = plainGrey;

    addCylinderVertices(width, height / 10.0f, selectedColor); // Cylinder top
    addLegsVertices(width / 10.0f, height, depth / 10.0f, selectedColor); // Four legs

    setupMesh();
    computeBoundingBox();
    if(diff)
        loadTexture("/mnt/c/Users/jfmal/OneDrive/Documents/University/3rd Year/COS344/Homework Assignment/OpenGL-Kiosk-Rendering/src/Materials/plasticTable.png");
    else 
        loadTexture("/mnt/c/Users/jfmal/OneDrive/Documents/University/3rd Year/COS344/Homework Assignment/OpenGL-Kiosk-Rendering/src/Materials/wood.png");
}

void Table::addCylinderVertices(float radius, float height, const glm::vec4& color) {
    const int segments = 72;
    const float angleStep = 2.0f * M_PI / segments;
    
    for (int i = 0; i < segments; ++i) {
        float angle = i * angleStep;
        float nextAngle = (i + 1) * angleStep;

        // Bottom circle
        vertices.push_back({{radius * cos(angle) + position.x, -height / 2.0f + position.y + this->height/2, radius * sin(angle) + position.z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, color});
        vertices.push_back({{0.0f + position.x, -height / 2.0f + position.y + this->height/2, 0.0f + position.z}, {0.0f, -1.0f, 0.0f}, {0.5f, 0.5f}, color});
        vertices.push_back({{radius * cos(nextAngle) + position.x, -height / 2.0f + position.y + this->height/2, radius * sin(nextAngle) + position.z}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, color});

        // Top circle
        vertices.push_back({{radius * cos(angle) + position.x, height / 2.0f + position.y + this->height/2, radius * sin(angle) + position.z}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, color});
        vertices.push_back({{0.0f + position.x, height / 2.0f + position.y + this->height/2, 0.0f + position.z}, {0.0f, 1.0f, 0.0f}, {0.5f, 0.5f}, color});
        vertices.push_back({{radius * cos(nextAngle) + position.x, height / 2.0f + position.y + this->height/2, radius * sin(nextAngle) + position.z}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}, color});

        // Side faces
        vertices.push_back({{radius * cos(angle) + position.x, -height / 2.0f + position.y + this->height/2, radius * sin(angle) + position.z}, {cos(angle), 0.0f, sin(angle)}, {0.0f, 0.0f}, color});
        vertices.push_back({{radius * cos(nextAngle) + position.x, -height / 2.0f + position.y + this->height/2, radius * sin(nextAngle) + position.z}, {cos(nextAngle), 0.0f, sin(nextAngle)}, {1.0f, 0.0f}, color});
        vertices.push_back({{radius * cos(nextAngle) + position.x, height / 2.0f + position.y + this->height/2, radius * sin(nextAngle) + position.z}, {cos(nextAngle), 0.0f, sin(nextAngle)}, {1.0f, 1.0f}, color});
        vertices.push_back({{radius * cos(angle) + position.x, height / 2.0f + position.y + this->height/2, radius * sin(angle) + position.z}, {cos(angle), 0.0f, sin(angle)}, {0.0f, 1.0f}, color});

        unsigned int baseIndex = vertices.size() - 6;
        std::vector<unsigned int> faceIndices = {
            // Bottom face
            baseIndex, baseIndex + 1, baseIndex + 2,
            // Top face
            baseIndex + 3, baseIndex + 4, baseIndex + 5,
            // Side face
            baseIndex + 6, baseIndex + 7, baseIndex + 8,
            baseIndex + 8, baseIndex + 9, baseIndex + 6
        };
        indices.insert(indices.end(), faceIndices.begin(), faceIndices.end());
    }
}

void Table::addLegsVertices(float legWidth, float legHeight, float legDepth, const glm::vec4& color) {
    // Define leg positions
    float halfWidth = width / 2.0f - legWidth / 2.0f;
    float halfDepth = depth / 2.0f - legDepth / 2.0f;
    float legTop = -height / 2.0f;

    std::vector<glm::vec3> legPositions = {
        { halfWidth, legTop, halfDepth },
        {-halfWidth, legTop, halfDepth },
        { halfWidth, legTop,-halfDepth },
        {-halfWidth, legTop,-halfDepth }
    };

    for (const auto& legPos : legPositions) {
        addPrismVertices(
            legPos.x - legWidth / 2.0f, legPos.y, 
            legPos.x + legWidth / 2.0f, legPos.y + legHeight, 
            legPos.z - legDepth / 2.0f, legPos.z + legDepth / 2.0f, 
            color
        );
    }
}

void Table::addPrismVertices(float x0, float y0, float x1, float y1, float z0, float z1, const glm::vec4& color) {
    unsigned int baseIndex = vertices.size();
    float start = 0.0;
    float end = 0.7;

    // Front face
    vertices.push_back({{x0 + position.x, y0 + position.y, z0 + position.z}, {0.0f, 0.0f, 1.0f}, {start, start}, color});
    vertices.push_back({{x1 + position.x, y0 + position.y, z0 + position.z}, {0.0f, 0.0f, 1.0f}, {end, start}, color});
    vertices.push_back({{x1 + position.x, y1 + position.y, z0 + position.z}, {0.0f, 0.0f, 1.0f}, {end, end}, color});
    vertices.push_back({{x0 + position.x, y1 + position.y, z0 + position.z}, {0.0f, 0.0f, 1.0f}, {start, end}, color});

    // Back face
    vertices.push_back({{x0 + position.x, y0 + position.y, z1 + position.z}, {0.0f, 0.0f, -1.0f}, {start, start}, color});
    vertices.push_back({{x1 + position.x, y0 + position.y, z1 + position.z}, {0.0f, 0.0f, -1.0f}, {end, start}, color});
    vertices.push_back({{x1 + position.x, y1 + position.y, z1 + position.z}, {0.0f, 0.0f, -1.0f}, {end, end}, color});
    vertices.push_back({{x0 + position.x, y1 + position.y, z1 + position.z}, {0.0f, 0.0f, -1.0f}, {start, end}, color});

    // Top face
    vertices.push_back({{x0 + position.x, y1 + position.y, z0 + position.z}, {0.0f, 1.0f, 0.0f}, {start, start}, color});
    vertices.push_back({{x1 + position.x, y1 + position.y, z0 + position.z}, {0.0f, 1.0f, 0.0f}, {end, start}, color});
    vertices.push_back({{x1 + position.x, y1 + position.y, z1 + position.z}, {0.0f, 1.0f, 0.0f}, {end, end}, color});
    vertices.push_back({{x0 + position.x, y1 + position.y, z1 + position.z}, {0.0f, 1.0f, 0.0f}, {start, end}, color});

    // Bottom face
    vertices.push_back({{x0 + position.x, y0 + position.y, z0 + position.z}, {0.0f, -1.0f, 0.0f}, {start, start}, color});
    vertices.push_back({{x1 + position.x, y0 + position.y, z0 + position.z}, {0.0f, -1.0f, 0.0f}, {end, start}, color});
    vertices.push_back({{x1 + position.x, y0 + position.y, z1 + position.z}, {0.0f, -1.0f, 0.0f}, {end, end}, color});
    vertices.push_back({{x0 + position.x, y0 + position.y, z1 + position.z}, {0.0f, -1.0f, 0.0f}, {start, end}, color});

    // Left face
    vertices.push_back({{x0 + position.x, y0 + position.y, z0 + position.z}, {-1.0f, 0.0f, 0.0f}, {start, start}, color});
    vertices.push_back({{x0 + position.x, y1 + position.y, z0 + position.z}, {-1.0f, 0.0f, 0.0f}, {end, start}, color});
    vertices.push_back({{x0 + position.x, y1 + position.y, z1 + position.z}, {-1.0f, 0.0f, 0.0f}, {end, end}, color});
    vertices.push_back({{x0 + position.x, y0 + position.y, z1 + position.z}, {-1.0f, 0.0f, 0.0f}, {start, end}, color});

    // Right face
    vertices.push_back({{x1 + position.x, y0 + position.y, z0 + position.z}, {1.0f, 0.0f, 0.0f}, {start, start}, color});
    vertices.push_back({{x1 + position.x, y1 + position.y, z0 + position.z}, {1.0f, 0.0f, 0.0f}, {end, start}, color});
    vertices.push_back({{x1 + position.x, y1 + position.y, z1 + position.z}, {1.0f, 0.0f, 0.0f}, {end, end}, color});
    vertices.push_back({{x1 + position.x, y0 + position.y, z1 + position.z}, {1.0f, 0.0f, 0.0f}, {start, end}, color});

    // Indices for each face
    std::vector<unsigned int> prismIndices = {
        // Front face
        baseIndex + 0, baseIndex + 1, baseIndex + 2,
        baseIndex + 2, baseIndex + 3, baseIndex + 0,
        // Back face
        baseIndex + 4, baseIndex + 5, baseIndex + 6,
        baseIndex + 6, baseIndex + 7, baseIndex + 4,
        // Top face
        baseIndex + 8, baseIndex + 9, baseIndex + 10,
        baseIndex + 10, baseIndex + 11, baseIndex + 8,
        // Bottom face
        baseIndex + 12, baseIndex + 13, baseIndex + 14,
        baseIndex + 14, baseIndex + 15, baseIndex + 12,
        // Left face
        baseIndex + 16, baseIndex + 17, baseIndex + 18,
        baseIndex + 18, baseIndex + 19, baseIndex + 16,
        // Right face
        baseIndex + 20, baseIndex + 21, baseIndex + 22,
        baseIndex + 22, baseIndex + 23, baseIndex + 20
    };
    indices.insert(indices.end(), prismIndices.begin(), prismIndices.end());
}

void Table::draw(const Shader& shader) const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    shader.use();

    // Set material properties
    glm::vec3 matAmbient = glm::vec3(0.2f, 0.2f, 0.2f);  // Grey ambient color
    glm::vec3 matDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);  // Grey diffuse color
    glm::vec3 matSpecular = glm::vec3(0.8f, 0.8f, 0.8f); // Grey specular color
    float matShininess = 10.0f;  // Shininess factor

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

void Table::setupMesh() {
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

void Table::loadTexture(const char* path) {
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
void Table::computeBoundingBox() {
    boundingBoxMin = position - glm::vec3(width / 2.0f, height / 2.0f, depth / 2.0f);
    boundingBoxMax = position + glm::vec3(width / 2.0f, height / 2.0f, depth / 2.0f);
}

// Function to get minimum bounding box coordinates
glm::vec3 Table::getBoundingBoxMin() const {
    return boundingBoxMin;
}

// Function to get maximum bounding box coordinates
glm::vec3 Table::getBoundingBoxMax() const {
    return boundingBoxMax;
}
