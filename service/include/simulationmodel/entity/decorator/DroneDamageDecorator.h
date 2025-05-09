#ifndef DRONE_DAMAGE_DECORATOR_H
#define DRONE_DAMAGE_DECORATOR_H

#include "Drone.h"
#include "DroneDecorator.h"

class DroneDamageDecorator : public DroneDecorator {
 private:
  double accum = 0;
  double durability = 100;
  double base_speed;

 public:
  DroneDamageDecorator(Drone* d);
  void update(double dt);
};

#endif  // DRONE_DAMAGE_DECORATOR_H
