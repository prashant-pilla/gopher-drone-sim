#ifndef HANDOFF_REQUEST_H
#define HANDOFF_REQUEST_H

#pragma once

#include "Package.h"
#include "vector3.h"

class HelperDrone;

struct HandoffRequest;

extern thread_local HandoffRequest* currentRequest;

struct HandoffRequest {
  Vector3 packagePosition;
  Package* targetPackage;
  HelperDrone* bestHelper = nullptr;  // Non-const pointer for assignment
  float minDistance = std::numeric_limits<float>::infinity();

  HandoffRequest(const Vector3& pos, Package* pkg)
      : packagePosition(pos), targetPackage(pkg) {
    currentRequest = this;
  }

  ~HandoffRequest() { currentRequest = nullptr; }

  void considerCandidate(HelperDrone* helper, float distance) {
    if (distance < minDistance) {
      minDistance = distance;
      bestHelper = helper;
    }
  }
};
#endif