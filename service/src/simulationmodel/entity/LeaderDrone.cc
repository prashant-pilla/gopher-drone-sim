#include "LeaderDrone.h"
#include "HelperDrone.h"
#include "HandoffRequest.h"
#include "SimulationModel.h"

LeaderDrone::LeaderDrone(const JsonObject &obj) : Drone(obj), publisher() {}

void LeaderDrone::addObserver(IObserver *o) { observers.insert(o); }

void LeaderDrone::removeObserver(IObserver *o) { observers.erase(o); }

void LeaderDrone::notifyObservers(const std::string &message, void *data)
{
  for (auto &o : observers)
    o->notify(message, data);
}

void LeaderDrone::update(double dt)
{
  Drone::update(dt);

  // Battery drain simulation (1% per second)
  battery -= dt * 0.01f;

  if (battery < LOW_BATTERY_THRESHOLD && !handoffTriggered && package)
  {
    HandoffRequest *request = new HandoffRequest(package->getPosition(), package);
    notifyObservers("HANDOFF_REQUEST", &request);

    if (request->bestHelper)
    {
      request->bestHelper->acceptHandoff(package);
      returnToRechargeStation();
      handoffTriggered = true;
    }
    delete request;
  }
}

void LeaderDrone::initiateHandoff()
{
  if (package)
  {
    HandoffRequest request(package->getPosition(), package);
    notifyObservers("HANDOFF_REQUEST", &request);

    if (request.bestHelper)
    {
      // Send notification through model
      if (model)
      {
        std::string msg = "HelperDrone " + std::to_string(request.bestHelper->getId()) + " accepted handoff from LeaderDrone " + std::to_string(getId());
        model->notify(msg, nullptr);
      }

      request.bestHelper->acceptHandoff(package);
      returnToRechargeStation();
      handoffTriggered = true;
    }
  }
}

void LeaderDrone::updateBattery(double dt)
{
  // Battery drain rate (1% per second)
  battery -= dt * 1.0f;
}

void LeaderDrone::returnToRechargeStation()
{
  // Implementation for returning to recharge
}