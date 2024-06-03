#include "Floor.h"
#include <iostream>
#include <algorithm>
#include <limits>

Floor::Floor() {
    int gridWidth = 40;  // Number of quads in width
    int gridDepth = 120;  // Number of quads in depth
    float quadSize = 0.5f;  // Size of each quad

    float halfWidth = (gridWidth * quadSize) / 2.0f;
    float halfDepth = (gridDepth * quadSize) / 2.0f;

    glm::vec4 plainGrey(0.598, 0.582, 0.543, 1);
    glm::vec4 darkGrey(0.314, 0.314, 0.314, 1);
    glm::vec4 yellow(0.765, 0.569, 0.243, 1);

    glm::vec4 selectedColor = plainGrey;
    int vertexCounter = 0;
    bool flip = false;
    for (int z = 0; z < gridDepth; ++z) {
        for (int x = 0; x < gridWidth; ++x) {
            if(x < 6 && (z + 2) % 13 != 0 && (z + 1) % 13 != 0 && (z) % 13 != 0 && z < 90 && z > 13) continue;
            
            float x0 = x * quadSize - halfWidth;
            float x1 = (x + 1) * quadSize - halfWidth;
            float z0 = z * quadSize - halfDepth;
            float z1 = (z + 1) * quadSize - halfDepth;

            selectedColor = plainGrey;
            if((z + 1) % 13 == 0 && (((x < 6 || x > 9) && z < 91) || z > 91)){
                selectedColor = yellow;
                flip = !flip;
            } 
            else if(x < 10 || (x > 17 && x < 30) || x > 35) selectedColor = darkGrey;

            if(flip && selectedColor == darkGrey && (x > 17 && x < 30)){
                selectedColor = plainGrey;
            }else if(flip && selectedColor == plainGrey && (x < 17 || x > 30)){
                selectedColor = darkGrey;
            }

            vertices.push_back({{x0, 0.0f, z0}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, selectedColor});
            vertices.push_back({{x1, 0.0f, z0}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}, selectedColor});
            vertices.push_back({{x1, 0.0f, z1}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, selectedColor});
            vertices.push_back({{x0, 0.0f, z1}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}, selectedColor});

            indices.push_back(vertexCounter + 0);
            indices.push_back(vertexCounter + 1);
            indices.push_back(vertexCounter + 2);
            indices.push_back(vertexCounter + 2);
            indices.push_back(vertexCounter + 3);
            indices.push_back(vertexCounter + 0);

            vertexCounter += 4;
        }
    }

    setupMesh();
    computeBoundingBox();
    loadTexture("/mnt/c/Users/jfmal/OneDrive/Documents/University/3rd Year/COS344/Homework Assignment/OpenGL-Kiosk-Rendering/src/Materials/carpet.jpg");
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

    // Vertex Colors
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

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
    // Draw the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    shader.use();

    // Set material properties
    glm::vec3 matAmbient = glm::vec3(0.5f, 0.5f, 0.5f);  // Grey ambient color
    glm::vec3 matDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);  // Grey diffuse color
    glm::vec3 matSpecular = glm::vec3(0.5f, 0.5f, 0.5f); // Grey specular color
    float matShininess = 0.2f;  // Shininess factor

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