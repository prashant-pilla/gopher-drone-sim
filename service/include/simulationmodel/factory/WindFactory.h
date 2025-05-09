#ifndef WIND_FACTORY_H_
#define WIND_FACTORY_H_

#include "IEntityFactory.h"
#include "WeatherControl.h"

/**
 *@brief Wind Factory to produce WeatherControl class.
 **/
class WindFactory : public IEntityFactory {
 public:
  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* createEntity(const JsonObject& entity);
};

#endif
