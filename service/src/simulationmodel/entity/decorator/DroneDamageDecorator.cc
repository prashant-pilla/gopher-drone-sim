#include "DroneDamageDecorator.h"

#include <iostream>

#include "SimulationModel.h"
#include "WeatherControl.h"
DroneDamageDecorator::DroneDamageDecorator(Drone* d) : DroneDecorator(d) {
  base_speed = d->getSpeed();
}
// called every tick of the simulation
void DroneDamageDecorator::update(double dt) {
  // hover in place, maybe indicative that we let it land on the ground.
  if (durability <= 0) return;
  sub->update(dt);
  Vector3 wind = WeatherControl::getInstance()->getWind();
  // std::cout << wind << std::endl;
  // scale by dt and a minimizing factor.
  Vector3 windDisplacement = wind * dt * 0.1;

  // handled movement here for OCP
  sub->setPosition(sub->getPosition() + windDisplacement);

  // accumulator for damage logic
  accum += dt;
  if (accum < 1) return;
  accum -= 1;

  double mag = wind.magnitude();

  notifyObservers(std::to_string(durability) + "\% durability");
  if (mag > 20) {
    durability -= mag / 50.0;
    double n_speed = base_speed * (durability / 100);
    // capped speed loss, when it allowed it to go to 0, it was hard to watch
    // lol
    if (n_speed < base_speed * 0.5) n_speed = base_speed * 0.5;
    sub->setSpeed(n_speed);
  }

  if (durability <= 0) {
    // drone broke :(
    std::cout << "drone died" << std::endl;
    if (!sub->getPackage()) {
      std::cout << "package not found" << std::endl;
    }
    if (getPackage()) {
      std::cout << "package being unclaimed" << std::endl;
      getPackage()->unclaim();
      sub->getModel()->queue.addPackage(sub->getPackage());
    }
    return;
  }
}
