#ifndef HELPER_DRONE_H
#define HELPER_DRONE_H

#include "Drone.h"
#include "IObserver.h"

class HelperDrone : public Drone, public IObserver
{
public:
  HelperDrone(const JsonObject &obj);
  void notify(const std::string &message, void *data) const override;
  void acceptHandoff(Package *package);
  bool isAvailable() const;

private:
  bool available = true;
  float calculateDistance(Vector3 targetPos) const;
};
#endif