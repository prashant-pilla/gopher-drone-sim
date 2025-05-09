#ifndef LEADER_DRONE_H
#define LEADER_DRONE_H

#include "Drone.h"
#include "IPublisher.h"

class LeaderDrone : public Drone
{
public:
  LeaderDrone(const JsonObject &obj);
  void update(double dt) override;
  void updateBattery(double dt);
  void initiateHandoff();
  void returnToRechargeStation();
  bool handoffTriggered = false;

  void addObserver(IObserver *o) { publisher_.addObserver(o); };
  void removeObserver(IObserver *o) { publisher_.removeObserver(o); };
  void notifyObservers(const std::string &message, void *data = nullptr) { publisher_.notifyObservers(message, data); };

private:
  IPublisher publisher_;
  float battery = 100.0f;
  static constexpr float LOW_BATTERY_THRESHOLD = 20.0f;
};
#endif