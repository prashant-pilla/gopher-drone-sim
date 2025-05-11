#ifndef LEADER_DRONE_H
#define LEADER_DRONE_H

#include "Drone.h"
#include "IPublisher.h"

/**
 * @class LeaderDrone
 * @brief A specialized Drone that manages its own battery level and
 *        can delegate deliveries to helper drones when battery is low.
 *
 * Implements the Observer pattern (via IPublisher) to broadcast
 * HANDOFF_REQUEST notifications to HelperDrone observers. When its
 * battery falls below LOW_BATTERY_THRESHOLD, it initiates a handoff,
 * then returns to a fixed recharge station and resets its battery.
 */
class LeaderDrone : public Drone {
 public:
  /**
   * @brief constructor for Leader drone
   * @param obj contains details like role = leader to create drone
   */
  LeaderDrone(const JsonObject& obj);

  /**
   * @brief Main per-frame update: drains battery, triggers handoff,
   *        and, if dead, returns home to recharge.
   * @param dt Time delta since last update (seconds).
   */
  void update(double dt) override;

  /**
   * @brief Decreases battery by dt * 1% per second, clamps at zero.
   * @param dt Time delta in seconds.
   */
  void updateBattery(double dt);

  /**
   * @brief Sends a HANDOFF_REQUEST to all registered HelperDrones.
   *        Picks the nearest one to continue delivery.
   */
  void initiateHandoff();

  /**
   * @brief Moves this drone back to its recharge station. Once within
   *        1 meter, resets battery to 100% and clears handoff flags.
   */
  void returnToRechargeStation();

  bool handoffTriggered = false;
  bool handoffLogged = false;
  bool returningHome = false;

  /**
   * @brief Register a helper as an observer of handoff requests
   */
  void addObserver(IObserver* o) { publisher_.addObserver(o); }

  /**
   * @brief Unregister a helper as an observer of handoff requests
   */
  void removeObserver(IObserver* o) { publisher_.removeObserver(o); }

 private:
  IPublisher publisher_;
  float battery = 100.0f;
  static constexpr float LOW_BATTERY_THRESHOLD = 20.0f;
};
#endif