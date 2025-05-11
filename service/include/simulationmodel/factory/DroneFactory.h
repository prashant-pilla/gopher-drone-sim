#ifndef DRONE_FACTORY_H_
#define DRONE_FACTORY_H_

#include <vector>

#include "Drone.h"
#include "DroneColorDecorator.h"
#include "DroneDamageDecorator.h"
#include "HelperDrone.h"
#include "IEntityFactory.h"
#include "LeaderDrone.h"

/**
 *@brief Drone Factory to produce Drones class.
 **/
class DroneFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for DroneFactory class.
   **/
  virtual ~DroneFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* createEntity(const JsonObject& entity);

 private:
  std::vector<LeaderDrone*> leaders;
  std::vector<HelperDrone*> helpers;
};

#endif
