#include "DroneFactory.h"

#include "HelperDrone.h"
#include "LeaderDrone.h"

IEntity* DroneFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];

  if (type.compare("drone") == 0) {
    std::cout << "Drone Created" << std::endl;

    Drone* baseDrone = nullptr;

    if (entity.contains("role")) {
      std::string role = entity["role"];
      if (role == "leader") {
        baseDrone = new LeaderDrone(entity);
      } else if (role == "helper") {
        baseDrone = new HelperDrone(entity);
      }
    }

    if (!baseDrone) {
      baseDrone = new Drone(entity);
    }

    return new DroneColorDecorator(baseDrone, 0, 0, 100);
  }
  return nullptr;
}
