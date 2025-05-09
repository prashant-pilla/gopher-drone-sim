#ifndef HANDOFF_REQUEST_H
#define HANDOFF_REQUEST_H

#include "Package.h"
#include "vector3.h"

class HelperDrone;

struct HandoffRequest {
  Vector3 packagePosition;
  Package *targetPackage;
  HelperDrone *bestHelper = nullptr;  // Non-const pointer for assignment
  float minDistance = INFINITY;

  HandoffRequest(Vector3 pos, Package *pkg)
      : packagePosition(pos), targetPackage(pkg) {}

  void considerCandidate(HelperDrone *helper, float distance) {
    if (distance < minDistance) {
      minDistance = distance;
      bestHelper = helper;
    }
  }
};
#endif