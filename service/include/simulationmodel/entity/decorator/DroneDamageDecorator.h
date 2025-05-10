#ifndef DRONE_DAMAGE_DECORATOR_H
#define DRONE_DAMAGE_DECORATOR_H

#include "Drone.h"
#include "DroneDecorator.h"

/**
 * @class decorator class for drone damage extension
 */
class DroneDamageDecorator : public DroneDecorator {
 private:
  double accum = 0;
  double durability = 100;
  double base_speed;

 public:
  /**
   * @brief constructor
   * @param d Drone that is being decorated
   */
  DroneDamageDecorator(Drone* d);
  /**
   * @brief update durability of drone
   * @param dt time passed since last update
   */
  void update(double dt);
};

#endif  // DRONE_DAMAGE_DECORATOR_H
