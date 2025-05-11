#include "HelperDrone.h"

#include "BeelineStrategy.h"
#include "HandoffRequest.h"
#include "SimulationModel.h"

HelperDrone::HelperDrone(const JsonObject &obj) : Drone(obj) {}

void HelperDrone::notify(const std::string &message) const {
  if (message == "HANDOFF_REQUEST" && isAvailable()) {
    std::cout << "[Helper] " << getId()
              << " heard handoff with request: " << currentRequest << "\n";
    auto *request = currentRequest;
    if (!request) return;
    // Calculate 3D distance using existing drone position
    Vector3 helperPos = getPosition();
    float distance = (helperPos - request->packagePosition).magnitude();
    std::cout << "[Helper] Candidate " << getId() << " dist = " << distance
              << "\n";
    request->considerCandidate(const_cast<HelperDrone *>(this), distance);
  }
}

void HelperDrone::acceptHandoff(Package *package) {
  std::cout << "helper accepting handoff\n";
  this->package = package;
  available = false;
  pickedUp = false;

  handoffDropOff = package->getDestination();

  delete toFinalDestination;
  toFinalDestination = nullptr;

  if (toPackage) {
    delete toPackage;
  }
  // Initialize strategy
  toPackage = new BeelineStrategy(getPosition(), package->getPosition());

  // Notify through model
  if (model) {
    std::string msg =
        "HelperDrone " + std::to_string(getId()) + " accepted handoff";
    model->notify(msg);
  }
}

void HelperDrone::update(double dt) {
  // 1) If we haven’t picked up yet, run the toPackage phase
  if (toPackage && !pickedUp) {
    toPackage->move(this, dt);

    // when we arrive at the package
    if (toPackage->isCompleted()) {
      std::cout << "[Helper " << getId() << "] picked up " << package->getName()
                << "\n";
      delete toPackage;
      toPackage = nullptr;
      package->pickUp();
      pickedUp = true;

      // notify front end
      if (model) {
        model->notify("HelperDrone " + std::to_string(getId()) +
                      " picked up: " + package->getName());
      }
    }
  }
  // 2) Else if we’ve picked up, run the toFinalDestination (drop off) phase
  else if (pickedUp) {
    // initialize the drop-off strategy on first entry
    if (!toFinalDestination) {
      toFinalDestination = new BeelineStrategy(getPosition(), handoffDropOff);
      std::cout << "[Helper " << getId() << "] heading to drop-off at "
                << handoffDropOff << "\n";
    }
    toFinalDestination->move(this, dt);

    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    if (toFinalDestination->isCompleted()) {
      std::cout << "[Helper " << getId() << "] dropped off "
                << package->getName() << "\n";
      delete toFinalDestination;
      toFinalDestination = nullptr;
      package->handOff();

      // notify front end
      if (model) {
        model->notify("HelperDrone " + std::to_string(getId()) +
                      " dropped off: " + package->getName());
      }

      // reset helper state
      package = nullptr;
      pickedUp = false;
      available = true;
    }
  }
}

bool HelperDrone::isAvailable() const {
  return available && (package == nullptr);
}