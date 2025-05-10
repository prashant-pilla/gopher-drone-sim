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
        std::cout << "Made a leader" << std::endl;
        baseDrone = new LeaderDrone(entity);
      } else if (role == "helper") {
        std::cout << "Made a helper" << std::endl;
        baseDrone = new HelperDrone(entity);
      }
    }

    if (!baseDrone) {
      baseDrone = new Drone(entity);
    }

    return new DroneColorDecorator(
        new DroneDamageDecorator(baseDrone), 0, 0, 100);
  }
  return nullptr;
}
