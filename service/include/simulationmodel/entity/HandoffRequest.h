#ifndef HANDOFF_REQUEST_H
#define HANDOFF_REQUEST_H

#pragma once

#include "Package.h"
#include "vector3.h"

class HelperDrone;

struct HandoffRequest;

/** @brief Thread‐local pointer to the active handoff request. */
extern thread_local HandoffRequest* currentRequest;

/**
 * @struct HandoffRequest
 * @brief Helper struct carrying data for a leader→helper handoff.
 *
 * On creation, sets thread_local currentRequest. HelperDrones call
 * considerCandidate() to propose themselves, and the one with the
 * minimum distance wins. On destruction, clears currentRequest.
 */
struct HandoffRequest {
  Vector3 packagePosition;
  Package* targetPackage;
  HelperDrone* bestHelper = nullptr;  // Non-const pointer for assignment
  float minDistance = std::numeric_limits<float>::infinity();

  /**
   * @brief Constructs a HandoffRequest and registers it as current.
   * @param pos Current package position.
   * @param pkg Pointer to the package needing a new courier.
   */
  HandoffRequest(const Vector3& pos, Package* pkg)
      : packagePosition(pos), targetPackage(pkg) {
    currentRequest = this;
  }

  /** @brief Destructor clears currentRequest. */
  ~HandoffRequest() { currentRequest = nullptr; }

  /**
   * @brief Called by each HelperDrone candidate to compare distances.
   * @param helper The helper drone proposing itself.
   * @param distance Distance from helper to package.
   */
  void considerCandidate(HelperDrone* helper, float distance) {
    if (distance < minDistance) {
      minDistance = distance;
      bestHelper = helper;
    }
  }
};
#endif