#include "PlantPot.h"
#include <iostream>
#include <algorithm>
#include <limits>

PlantPot::PlantPot(float width, float height, float depth, const glm::vec3& position)
    : width(width), height(height), depth(depth), position(position) {

    glm::vec4 black(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 green(0.3f, 0.7f, 0.3f, 1.0f);
    glm::vec4 green2(0.3f, 0.5f, 0.3f, 1.0f);

    // Add vertices for the pot
    addPotVertices(width, height, depth, black);

    // Add vertices for the plants, positioned above the pot
    glm::vec3 plantPosition = glm::vec3(position);
    float plantHeight = height; // Make the plants taller
    addPlantVertices(width/2, plantHeight*0.81, depth/2, green2);
    this->position.z -= depth/3;
    addPlantVertices(width/2, plantHeight, depth/2, green);
    this->position = glm::vec3(plantPosition);
    this->position.x += width/3;
    this->position.z -= depth/3;
    addPlantVertices(width/2, plantHeight*0.8, depth/2, green2);
    this->position = glm::vec3(plantPosition);
    this->position.x -= width/3;
    this->position.z -= depth/4;
    addPlantVertices(width/2, plantHeight*0.9, depth/2, green2);
    this->position = glm::vec3(plantPosition);
    this->position.x += width/4;
    this->position.z += depth/3;
    addPlantVertices(width/2, plantHeight*0.85, depth/2, green);
    this->position = glm::vec3(plantPosition);
    this->position.x -= width/3;
    this->position.z += depth/4;
    addPlantVertices(width/2, plantHeight*0.93, depth/2, green);

    setupMesh();
    computeBoundingBox();
}

void PlantPot::addPotVertices(float width, float height, float depth, const glm::vec4& color) {
    float halfWidth = width / 2.0f;
    float halfDepth = depth / 2.0f;

    addPrismVertices(-halfWidth, 0.0f, halfWidth, height, -halfDepth, halfDepth, color);
}

void PlantPot::addPlantVertices(float width, float height, float depth, const glm::vec4& color) {
    float halfWidth = width / 2.0f;
    float halfDepth = depth / 2.0f;

    // Plant 1
    addTriangleVertices({-halfWidth / 2, height, -halfDepth / 2}, {halfWidth / 2, height, -halfDepth / 2}, {0, height * 1.5f, 0}, color);
    // Plant 2
    addTriangleVertices({-halfWidth / 2, height, halfDepth / 2}, {halfWidth / 2, height, halfDepth / 2}, {0, height * 1.5f, 0}, color);
    // Plant 3
    addTriangleVertices({halfWidth / 2, height, -halfDepth / 2}, {halfWidth / 2, height, halfDepth / 2}, {0, height * 1.5f, 0}, color);
    // Plant 4
    addTriangleVertices({-halfWidth / 2, height, -halfDepth / 2}, {-halfWidth / 2, height, halfDepth / 2}, {0, height * 1.5f, 0}, color);
}

void PlantPot::addTriangleVertices(const glm::vec3& base1, const glm::vec3& base2, const glm::vec3& top, const glm::vec4& color) {
    unsigned int baseIndex = vertices.size();

    glm::vec3 normal = glm::normalize(glm::cross(base2 - base1, top - base1));

    vertices.push_back({base1 + position, normal, {0.0f, 0.0f}, color});
    vertices.push_back({base2 + position, normal, {1.0f, 0.0f}, color});
    vertices.push_back({top + position, normal, {0.5f, 1.0f}, color});

    indices.push_back(baseIndex);
    indices.push_back(baseIndex + 1);
    indices.push_back(baseIndex + 2);
}

void PlantPot::addPrismVertices(float x0, float y0, float x1, float y1, float z0, float z1, const glm::vec4& color) {
    unsigned int baseIndex = vertices.size();
    float start = 0.0f;
    float end = 1.0f;

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

    for (int i = 0; i < 6; ++i) {
        indices.push_back(baseIndex + i * 4 + 0);
        indices.push_back(baseIndex + i * 4 + 1);
        indices.push_back(baseIndex + i * 4 + 2);
        indices.push_back(baseIndex + i * 4 + 2);
        indices.push_back(baseIndex + i * 4 + 3);
        indices.push_back(baseIndex + i * 4 + 0);
    }
}

void PlantPot::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Vertex Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // Vertex Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);
    // Vertex Texture Coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);
    // Vertex Colors
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

void PlantPot::loadTexture(const char* path) {
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

void PlantPot::computeBoundingBox() {
    glm::vec3 minVertex = glm::vec3(std::numeric_limits<float>::max());
    glm::vec3 maxVertex = glm::vec3(std::numeric_limits<float>::lowest());

    for (const auto& vertex : vertices) {
        minVertex = glm::min(minVertex, vertex.Position);
        maxVertex = glm::max(maxVertex, vertex.Position);
    }

    boundingBoxMin = minVertex;
    boundingBoxMax = maxVertex;
}

void PlantPot::draw(const Shader& shader) const {
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, textureID);

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
    shader.setBool("useColor", true);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

glm::vec3 PlantPot::getBoundingBoxMin() const {
    return boundingBoxMin;
}

glm::vec3 PlantPot::getBoundingBoxMax() const {
    return boundingBoxMax;
}
