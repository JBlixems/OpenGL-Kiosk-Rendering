// FrustumCulling.cpp
#include "../Helpers/FrustrumCulling.h"

void FrustumCulling::updateFrustum(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) {
    glm::mat4 matrix = projectionMatrix * viewMatrix;

    // Left
    frustumPlanes[LEFT] = glm::vec4(matrix[0][3] + matrix[0][0],
                                    matrix[1][3] + matrix[1][0],
                                    matrix[2][3] + matrix[2][0],
                                    matrix[3][3] + matrix[3][0]);
    normalizePlane(frustumPlanes[LEFT]);

    // Right
    frustumPlanes[RIGHT] = glm::vec4(matrix[0][3] - matrix[0][0],
                                     matrix[1][3] - matrix[1][0],
                                     matrix[2][3] - matrix[2][0],
                                     matrix[3][3] - matrix[3][0]);
    normalizePlane(frustumPlanes[RIGHT]);

    // Bottom
    frustumPlanes[BOTTOM] = glm::vec4(matrix[0][3] + matrix[0][1],
                                      matrix[1][3] + matrix[1][1],
                                      matrix[2][3] + matrix[2][1],
                                      matrix[3][3] + matrix[3][1]);
    normalizePlane(frustumPlanes[BOTTOM]);

    // Top
    frustumPlanes[TOP] = glm::vec4(matrix[0][3] - matrix[0][1],
                                   matrix[1][3] - matrix[1][1],
                                   matrix[2][3] - matrix[2][1],
                                   matrix[3][3] - matrix[3][1]);
    normalizePlane(frustumPlanes[TOP]);

    // Near
    frustumPlanes[NEAR] = glm::vec4(matrix[0][3] + matrix[0][2],
                                    matrix[1][3] + matrix[1][2],
                                    matrix[2][3] + matrix[2][2],
                                    matrix[3][3] + matrix[3][2]);
    normalizePlane(frustumPlanes[NEAR]);

    // Far
    frustumPlanes[FAR] = glm::vec4(matrix[0][3] - matrix[0][2],
                                   matrix[1][3] - matrix[1][2],
                                   matrix[2][3] - matrix[2][2],
                                   matrix[3][3] - matrix[3][2]);
    normalizePlane(frustumPlanes[FAR]);
}

void FrustumCulling::normalizePlane(glm::vec4& plane) {
    float length = glm::length(glm::vec3(plane));
    plane /= length;
}

bool FrustumCulling::isBoxInFrustum(const glm::vec3& min, const glm::vec3& max) const {
    for (int i = 0; i < COUNT; i++) {
        if (frustumPlanes[i].x * min.x + frustumPlanes[i].y * min.y + frustumPlanes[i].z * min.z + frustumPlanes[i].w > 0) continue;
        if (frustumPlanes[i].x * max.x + frustumPlanes[i].y * min.y + frustumPlanes[i].z * min.z + frustumPlanes[i].w > 0) continue;
        if (frustumPlanes[i].x * min.x + frustumPlanes[i].y * max.y + frustumPlanes[i].z * min.z + frustumPlanes[i].w > 0) continue;
        if (frustumPlanes[i].x * max.x + frustumPlanes[i].y * max.y + frustumPlanes[i].z * min.z + frustumPlanes[i].w > 0) continue;
        if (frustumPlanes[i].x * min.x + frustumPlanes[i].y * min.y + frustumPlanes[i].z * max.z + frustumPlanes[i].w > 0) continue;
        if (frustumPlanes[i].x * max.x + frustumPlanes[i].y * min.y + frustumPlanes[i].z * max.z + frustumPlanes[i].w > 0) continue;
        if (frustumPlanes[i].x * min.x + frustumPlanes[i].y * max.y + frustumPlanes[i].z * max.z + frustumPlanes[i].w > 0) continue;
        if (frustumPlanes[i].x * max.x + frustumPlanes[i].y * max.y + frustumPlanes[i].z * max.z + frustumPlanes[i].w > 0) continue;
        return false;
    }
    return true;
}
