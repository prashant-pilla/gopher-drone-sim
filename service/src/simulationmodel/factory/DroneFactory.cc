#include "DroneFactory.h"

IEntity* DroneFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("drone") == 0) {
    std::cout << "Drone Created" << std::endl;
    return new DroneDamageDecorator(
        new DroneColorDecorator(new Drone(entity), 0, 0, 100));
  }
  return nullptr;
}
