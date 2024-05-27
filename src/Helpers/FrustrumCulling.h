// FrustumCulling.h
#ifndef FRUSTUM_CULLING_H
#define FRUSTUM_CULLING_H

#include <glm/glm.hpp>
#include <vector>

class FrustumCulling {
public:
    void updateFrustum(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
    bool isBoxInFrustum(const glm::vec3& min, const glm::vec3& max) const;

private:
    enum { TOP = 0, BOTTOM, LEFT, RIGHT, NEAR, FAR, COUNT };
    glm::vec4 frustumPlanes[COUNT];

    void normalizePlane(glm::vec4& plane);
};

#endif
