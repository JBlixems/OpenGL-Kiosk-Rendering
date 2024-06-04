#include "PlainPrism.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

PlainPrism::PlainPrism(float width, float height, float depth, const glm::vec3& position, glm::vec4 color)
    : width(width), height(height), depth(depth), position(position) {

    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;

    addPrismVertices(-halfWidth, -halfHeight, halfWidth, halfHeight, 0.0f, depth, color);

    setupMesh();
    computeBoundingBox();
}

void PlainPrism::addPrismVertices(float x0, float y0, float x1, float y1, float z0, float z1, const glm::vec4& color) {
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

void PlainPrism::draw(const Shader& shader) const {
    shader.use();

    // Set material properties
    glm::vec3 matAmbient = glm::vec3(0.2f, 0.2f, 0.2f);  // Grey ambient color
    glm::vec3 matDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);  // Grey diffuse color
    glm::vec3 matSpecular = glm::vec3(0.8f, 0.8f, 0.8f); // Grey specular color
    float matShininess = 1.0f;  // Shininess factor

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

void PlainPrism::setupMesh() {
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

// Function to compute bounding box of the window
void PlainPrism::computeBoundingBox() {
    boundingBoxMin = position - glm::vec3(width / 2.0f, height / 2.0f, depth / 2.0f);
    boundingBoxMax = position + glm::vec3(width / 2.0f, height / 2.0f, depth / 2.0f);
}

// Function to get minimum bounding box coordinates
glm::vec3 PlainPrism::getBoundingBoxMin() const {
    return boundingBoxMin;
}

// Function to get maximum bounding box coordinates
glm::vec3 PlainPrism::getBoundingBoxMax() const {
    return boundingBoxMax;
}