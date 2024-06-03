#include "NorthWall.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>

NorthWall::NorthWall(float width, float height, float depth, const glm::vec3& position, float angle, bool right)
    : width(width), height(height), depth(depth), position(position) {

    float slantAngle = glm::radians(angle);  // Slant angle in radians
    float quadSize = 0.3f;  // Size of each quad

    int gridWidth = static_cast<int>(height / quadSize);  // Number of quads in width
    int gridDepth = static_cast<int>(depth / quadSize);  // Number of quads in depth

    float halfWidth = (gridWidth * quadSize) / 2.0f;
    float halfDepth = (gridDepth * quadSize) / 2.0f;

    glm::vec4 plainGrey(0.698, 0.682, 0.643, 1);
    glm::vec4 darkGrey(0.248, 0.242, 0.243, 1);

    glm::vec4 selectedColor = plainGrey;
    if(position.y > 13) selectedColor = darkGrey;

    int vertexCounter = 0;
    bool flip = false;

    glm::vec3 normal;
    if(angle == 0 && (position.y < 6.6 || (position.y < 10.7 && position.y > 10)))
        normal = glm::vec3(0.0f, 1.0f, 0.0f);
    else if(angle == 0)
        normal = glm::vec3(0.0f, -1.0f, 0.0f);
    else if(right)
        normal = glm::vec3(cos(slantAngle), sin(slantAngle), 0.0f);
    else
        normal = glm::vec3(-cos(slantAngle), sin(slantAngle), 0.0f);

    for (int z = 0; z < gridDepth; ++z) {
        for (int x = 0; x < gridWidth; ++x) {            
            float x0 = x * quadSize - halfWidth;
            float x1 = (x + 1) * quadSize - halfWidth;
            float z0 = z * quadSize - halfDepth;
            float z1 = (z + 1) * quadSize - halfDepth;

            // Apply slant to y-coordinates
            float slantOffset0 = tan(slantAngle) * (x0);
            float slantOffset1 = tan(slantAngle) * (x1);

            vertices.push_back({{x0 + position.x, slantOffset0 + position.y, z0 + position.z}, normal, {0.95f, 0.95f}, selectedColor});
            vertices.push_back({{x1 + position.x, slantOffset1 + position.y, z0 + position.z}, normal, {1.0f, 0.95f}, selectedColor});
            vertices.push_back({{x1 + position.x, slantOffset1 + position.y, z1 + position.z}, normal, {1.0f, 1.0f}, selectedColor});
            vertices.push_back({{x0 + position.x, slantOffset0 + position.y, z1 + position.z}, normal, {0.95f, 1.0f}, selectedColor});

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
    if(position.y < 2.5)
        loadTexture("/mnt/c/Users/jfmal/OneDrive/Documents/University/3rd Year/COS344/Homework Assignment/OpenGL-Kiosk-Rendering/src/Materials/wood.png");
    else
        loadTexture("/mnt/c/Users/jfmal/OneDrive/Documents/University/3rd Year/COS344/Homework Assignment/OpenGL-Kiosk-Rendering/src/Materials/tile.png");
}

void NorthWall::addPrismVertices(float x0, float y0, float x1, float y1, float z0, float z1, const glm::vec4& color) {
    unsigned int baseIndex = vertices.size();

    // Front face
    vertices.push_back({{x0 + position.x, y0 + position.y, z0 + position.z}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, color});
    vertices.push_back({{x1 + position.x, y0 + position.y, z0 + position.z}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, color});
    vertices.push_back({{x1 + position.x, y1 + position.y, z0 + position.z}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}, color});
    vertices.push_back({{x0 + position.x, y1 + position.y, z0 + position.z}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}, color});

    // Back face
    vertices.push_back({{x0 + position.x, y0 + position.y, z1 + position.z}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}, color});
    vertices.push_back({{x1 + position.x, y0 + position.y, z1 + position.z}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}, color});
    vertices.push_back({{x1 + position.x, y1 + position.y, z1 + position.z}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}, color});
    vertices.push_back({{x0 + position.x, y1 + position.y, z1 + position.z}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}, color});

    // Top face
    vertices.push_back({{x0 + position.x, y1 + position.y, z0 + position.z}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}, color});
    vertices.push_back({{x1 + position.x, y1 + position.y, z0 + position.z}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}, color});
    vertices.push_back({{x1 + position.x, y1 + position.y, z1 + position.z}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}, color});
    vertices.push_back({{x0 + position.x, y1 + position.y, z1 + position.z}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}, color});

    // Bottom face
    vertices.push_back({{x0 + position.x, y0 + position.y, z0 + position.z}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}, color});
    vertices.push_back({{x1 + position.x, y0 + position.y, z0 + position.z}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}, color});
    vertices.push_back({{x1 + position.x, y0 + position.y, z1 + position.z}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}, color});
    vertices.push_back({{x0 + position.x, y0 + position.y, z1 + position.z}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}, color});

    // Left face
    vertices.push_back({{x0 + position.x, y0 + position.y, z0 + position.z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, color});
    vertices.push_back({{x0 + position.x, y1 + position.y, z0 + position.z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, color});
    vertices.push_back({{x0 + position.x, y1 + position.y, z1 + position.z}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, color});
    vertices.push_back({{x0 + position.x, y0 + position.y, z1 + position.z}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, color});

    // Right face
    vertices.push_back({{x1 + position.x, y0 + position.y, z0 + position.z}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}, color});
    vertices.push_back({{x1 + position.x, y1 + position.y, z0 + position.z}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}, color});
    vertices.push_back({{x1 + position.x, y1 + position.y, z1 + position.z}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}, color});
    vertices.push_back({{x1 + position.x, y0 + position.y, z1 + position.z}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}, color});

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

void NorthWall::addFaceVertices(float x0, float y0, float z0, float x1, float y1, float z1, const glm::vec3& normal, const glm::vec4& color) {
    unsigned int baseIndex = vertices.size();

    // Add vertices for a face (rectangle)
    vertices.push_back({{x0 + position.x, y0 + position.y, z0 + position.z}, normal, {0.0f, 0.0f}, color});
    vertices.push_back({{x1 + position.x, y0 + position.y, z0 + position.z}, normal, {1.0f, 0.0f}, color});
    vertices.push_back({{x1 + position.x, y1 + position.y, z0 + position.z}, normal, {1.0f, 1.0f}, color});
    vertices.push_back({{x0 + position.x, y1 + position.y, z0 + position.z}, normal, {0.0f, 1.0f}, color});

    // Add indices for the two triangles of the rectangle
    indices.push_back(baseIndex + 0);
    indices.push_back(baseIndex + 1);
    indices.push_back(baseIndex + 2);
    indices.push_back(baseIndex + 2);
    indices.push_back(baseIndex + 3);
    indices.push_back(baseIndex + 0);
}


void NorthWall::draw(const Shader& shader) const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    shader.use();

    // Set material properties
    glm::vec3 matAmbient = glm::vec3(0.8f, 0.8f, 0.8f);  // Grey ambient color
    glm::vec3 matDiffuse = glm::vec3(0.8f, 0.8f, 0.8f);  // Grey diffuse color
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

void NorthWall::setupMesh() {
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

void NorthWall::loadTexture(const char* path) {
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
void NorthWall::computeBoundingBox() {
    boundingBoxMin = position - glm::vec3(width / 2.0f, height / 2.0f, depth / 2.0f);
    boundingBoxMax = position + glm::vec3(width / 2.0f, height / 2.0f, depth / 2.0f);
}

// Function to get minimum bounding box coordinates
glm::vec3 NorthWall::getBoundingBoxMin() const {
    return boundingBoxMin;
}

// Function to get maximum bounding box coordinates
glm::vec3 NorthWall::getBoundingBoxMax() const {
    return boundingBoxMax;
}