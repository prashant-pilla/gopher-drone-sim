#ifndef HELPER_DRONE_H
#define HELPER_DRONE_H

#include "Drone.h"
#include "IObserver.h"

/**
 * @class HelperDrone
 * @brief A Drone that observes LeaderDrones for HANDOFF_REQUEST messages.
 *
 * Implements the Observer interface. When notified of a HANDOFF_REQUEST,
 * it computes its distance to the package via calculateDistance() and
 * calls considerCandidate() on the shared HandoffRequest. Once selected,
 * it accepts the package and continues delivery.
 */
class HelperDrone : public Drone, public IObserver {
 public:
  /**
   * @brief Constructs a HelperDrone from JSON configuration.
   * @param obj JsonObject containing position, speed, role="helper", etc.
   */
  HelperDrone(const JsonObject &obj);

  /**
   * @brief Observer callback invoked when a LeaderDrone broadcasts.
   * @param message The notification type (e.g., "HANDOFF_REQUEST").
   */
  void notify(const std::string &message) const override;

  /**
   * @brief Takes ownership of the package and begins delivery to its
   * destination.
   * @param package Pointer to the Package handed off by a LeaderDrone.
   */
  void acceptHandoff(Package *package);

  /**
   * @brief Returns whether this helper is free to take a handoff.
   * @return True if not currently handling a package.
   */
  bool isAvailable() const;

  /**
   * @brief Per-frame update: moves along its strategy path.
   * @param dt Time delta since last frame.
   */
  void update(double dt) override;

 private:
  bool available = true;
  /**
   * @brief Computes Euclidean distance from this drone to a target.
   * @param targetPos The 3D position to measure against.
   * @return The straight‐line distance.
   */
  float calculateDistance(Vector3 targetPos) const;
  Vector3 handoffDropOff;
};
#endif