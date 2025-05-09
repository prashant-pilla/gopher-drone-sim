#ifndef SEVEREWEATHER_H_
#define SEVEREWEATHER_H_

#include <random>
#include <cmath>
#include "IEntity.h"
#include "vector3.h"
//made weather an entity so we can update it with the normal updates.
// also gives us access to notifications for free :)))))

/**
 * @class WeatherControl
 * @brief Represents the weather for the simulation model
 *
 */
class WeatherControl : public IEntity {
 public:
  /**
   * @brief Gets the current instance of the WeatherControl singleton. 
   */
  static WeatherControl* getInstance();

  /**
   * @brief Updates the direction and magnitude of wind based on an internal accumulator.
   * @param dt The time step of the update.
   */
  void update(double dt);
  
  /**
   * @brief getter for current wind
   */
  Vector3 getWind(){return wind;}

  /**
   * @brief Removing the copy constructor operator
   */
  WeatherControl(const WeatherControl& other) = delete;

  /**
   * @brief Removing the assignment operator
   */
  WeatherControl& operator=(const WeatherControl& other) = delete;

 private:
  /**
   * @brief private constructor for WeatherControl
   */
  WeatherControl();

  /**
   * @brief Updates the direction and magnitude of wind based on an internal accumulator.
   * @param dt The time step of the update.
   */
  void private_update(double dt);

  static WeatherControl* instance;
  double accumulator = 0;
  Vector3 wind;
  //Don't know how to make this changeable sorry :( 
  double interval = 1;

  //shamelessly stolen from https://cplusplus.com/reference/random/normal_distribution/
  std::default_random_engine generator;
  std::normal_distribution<double> distribution;
};

#endif
