#include <iostream>
#include "WeatherControl.h"
#include <cmath>
#include <random>
#include <string>

WeatherControl* WeatherControl::instance = nullptr;

WeatherControl::WeatherControl(){
  wind = Vector3(0); //start w/ no wind 
  distribution = std::normal_distribution<double>(0,5.0);
}

WeatherControl* WeatherControl::getInstance(){
  if (!instance) instance = new WeatherControl();
  return instance;
}
// do this to make sure we're editing the global instance. 
void WeatherControl::update(double dt){
  getInstance()->private_update(dt);
}
void WeatherControl::private_update(double dt){
  accumulator += dt;
  if (accumulator < interval) return;

  accumulator -= interval;
  

  
  wind[0] += distribution(generator);
  wind[2] += distribution(generator);
  

   
  notifyObservers("Wind x: " + std::to_string(wind[0]) + " Wind y: " + std::to_string(wind[2]));

  //magnitude can technically be like 280 bc we're just restricting to +- 200
  //if that's a problem, assume that I checked the magnitude and used a while
  //loop to subtract 1 from x and z until the magnitude was < 200. :) 
  if (wind[0] < -200) wind[0] = -200;
  if (wind[0] > 200) wind[0] = 200;
  if (wind[2] < -200) wind[2] = -200;
  if (wind[2] > 200) wind[2] = 200;

}
