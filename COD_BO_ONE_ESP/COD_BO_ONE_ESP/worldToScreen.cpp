#include "worldToScreen.h"

bool WorldToScreenEsp(const Vec3 VecOrigin, Vec2& VecScreen, const float* Matrix) {
    Vec4 clipCoords = {};

    clipCoords.X = VecOrigin.X * Matrix[0] + VecOrigin.Y * Matrix[1] + VecOrigin.Z * Matrix[2] + Matrix[3];
    clipCoords.Y = VecOrigin.X * Matrix[4] + VecOrigin.Y * Matrix[5] + VecOrigin.Z * Matrix[6] + Matrix[7];
    clipCoords.W = VecOrigin.X * Matrix[12] + VecOrigin.Y * Matrix[13] + VecOrigin.Z * Matrix[14] + Matrix[15];

    if (clipCoords.W < 0.1f) {
        return false;
    }

    Vec3 NDC;
    NDC.X = clipCoords.X / clipCoords.W;
    NDC.Y = clipCoords.Y / clipCoords.W;

    // Convert NDC to normalized device coordinates [-1, 1]
    VecScreen.X = NDC.X;
    VecScreen.Y = NDC.Y + 0.02f;

    return true;
}