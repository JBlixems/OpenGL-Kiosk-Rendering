#include "Floor.h"
#include <algorithm>
#include <limits>

Floor::Floor(){
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

void Floor::draw(const Shader& shader) const {
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