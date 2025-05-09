#include "WindFactory.h"

IEntity* WindFactory::createEntity(const JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("WeatherControl") == 0) {
    std::cout << "Started Weather" << std::endl;
    
    return  reinterpret_cast<IEntity*>(WeatherControl::getInstance());
  }
  return nullptr;
}
