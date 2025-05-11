#include "LeaderDrone.h"

#include "BeelineStrategy.h"
#include "HandoffRequest.h"
#include "HelperDrone.h"
#include "SimulationModel.h"

LeaderDrone::LeaderDrone(const JsonObject &obj) : Drone(obj) {}

void LeaderDrone::update(double dt) {
  Drone::update(dt);

  if (!available && !package && battery == 100.0f) {
    // just recharged, let getNextDelivery fire next frame
    available = true;
  }

  if (!available && handoffTriggered && package == nullptr) {
    // we’re en route home; still call the move strategy
    toPackage->move(this, dt);
    return;
  }

  updateBattery(dt);

  if (battery <= 0.0f) {
    model->notify("Leader drone " + std::to_string(getId()) + " is dead.");
    return;
  }
  if (battery <= 0.0f && !toPackage) {
    std::cout << "[Leader " << getId() << "] battery dead → returning home\n";
    returnToRechargeStation();
    return;
  }

  model->notify("Leader drone " + std::to_string(getId()) + "battery is at " +
                std::to_string(battery));

  if (battery < LOW_BATTERY_THRESHOLD && !handoffTriggered && package) {
    if (!handoffLogged) {
      std::cout << "[Leader] Requesting Handoff\n";
      handoffLogged = true;
    }
    HandoffRequest request(package->getPosition(), package);
    publisher_.notifyObservers("HANDOFF_REQUEST");

    if (request.bestHelper) {
      handoffLogged = false;
      model->notify(
          "Helper Drone" + std::to_string(request.bestHelper->getId()) +
          "accepted handoff for Leader Drone" + std::to_string(getId()));
      request.bestHelper->acceptHandoff(package);
      request.bestHelper->update(0.0);

      if (toPackage) {
        delete toPackage;
        toPackage = nullptr;
      }
      if (toFinalDestination) {
        delete toFinalDestination;
        toFinalDestination = nullptr;
      }
      toPackage =
          new BeelineStrategy(getPosition(), Vector3{64.0, 254.0, -210.0});
      std::cout << "leader going home";

      returnToRechargeStation();
      handoffTriggered = true;
    }
  }
}

void LeaderDrone::initiateHandoff() {
  if (package) {
    HandoffRequest request(package->getPosition(), package);
    IPublisher::notifyObservers("HANDOFF_REQUEST");

    if (request.bestHelper) {
      std::cout << "[Leader] assigning helper" << request.bestHelper->getId()
                << "\n";
      if (model) {
        std::string msg =
            "HelperDrone " + std::to_string(request.bestHelper->getId()) +
            " accepted handoff from LeaderDrone " + std::to_string(getId());
        model->notify(msg);
      }

      request.bestHelper->acceptHandoff(package);
      returnToRechargeStation();
      handoffTriggered = true;
    }
  }
}

void LeaderDrone::updateBattery(double dt) {
  // Battery drain rate (1% per second)
  battery -= dt * 1.0f;
  if (battery < 0.0f) {
    battery = 0.0f;
  }
}

void LeaderDrone::returnToRechargeStation() {
  Vector3 home{64.0, 254.0, -210.0};
  if ((getPosition() - home).magnitude() < 1.0f) {
    std::cout << "[Leader " << getId()
              << "] arrived at station — recharging now\n";
    battery = 100.0f;
    handoffTriggered = false;
    handoffLogged = false;
    available = true;
    package = nullptr;
    pickedUp = false;
    std::cout << "[Leader] Recharged to 100%\n";
    delete toPackage;
    toPackage = nullptr;
    delete toFinalDestination;
    toFinalDestination = nullptr;
  } else {
    delete toPackage;
    toPackage = new BeelineStrategy(getPosition(), home);
  }
}