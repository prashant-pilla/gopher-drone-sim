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
        leaders.push_back(dynamic_cast<LeaderDrone*>(baseDrone));
        for (auto ele : helpers) {
          baseDrone->addObserver(dynamic_cast<IObserver*>(ele));
        }
      } else if (role == "helper") {
        std::cout << "Made a helper" << std::endl;
        baseDrone = new HelperDrone(entity);
        helpers.push_back(dynamic_cast<HelperDrone*>(baseDrone));
        for (auto ele : leaders) {
          ele->addObserver(dynamic_cast<IObserver*>(baseDrone));
        }
      }
    }

    if (!baseDrone) {
      baseDrone = new LeaderDrone(entity);
    }

    return new DroneColorDecorator(
        new DroneDamageDecorator(baseDrone), 0, 0, 100);
  }
  return nullptr;
}
