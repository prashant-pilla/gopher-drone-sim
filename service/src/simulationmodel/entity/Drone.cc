#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "BfsStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "Package.h"
#include "SimulationModel.h"

Drone::Drone(const JsonObject& obj) : IEntity(obj) { available = true; }

Drone::~Drone() {
  if (toPackage) delete toPackage;
  if (toFinalDestination) delete toFinalDestination;
}

void Drone::getNextDelivery() {
  if (!model) return;

  for (auto pkg : model->queue.packages) {
    if (!pkg->isClaimed()) {
      package = pkg;
      package->claim();

      std::string message = getName() + " heading to: " + package->getName();
      notifyObservers(message);
      available = false;
      pickedUp = false;

      Vector3 packagePosition = package->getPosition();
      Vector3 finalDestination = package->getDestination();

      toPackage = new BeelineStrategy(position, packagePosition);

      std::string strat = package->getStrategyName();
      if (strat == "astar") {
        toFinalDestination = new AstarStrategy(
            packagePosition, finalDestination, model->getGraph());
      } else if (strat == "dfs") {
        toFinalDestination = new DfsStrategy(packagePosition, finalDestination,
                                             model->getGraph());
      } else if (strat == "bfs") {
        toFinalDestination = new BfsStrategy(packagePosition, finalDestination,
                                             model->getGraph());
      } else if (strat == "dijkstra") {
        toFinalDestination = new DijkstraStrategy(
            packagePosition, finalDestination, model->getGraph());
      } else {
        toFinalDestination =
            new BeelineStrategy(packagePosition, finalDestination);
      }

      return;
    }
  }
}

void Drone::update(double dt) {
  if (available) getNextDelivery();

  if (toPackage) {
    toPackage->move(this, dt);

    // Calculate how far it moved since last frame
    double diff = this->lastPosition.dist(this->position);

    // Update the position for next time
    this->lastPosition = this->position;

    // Update distance traveled
    this->distanceTraveled += diff;
    this->tenth_distanceTraveled += diff;

    // if traveled one tenth of a mile
    if (this->tenth_distanceTraveled > 162.5) {
      // Increment tenth_mile
      DataManager::getInstance().updateDistance(*this);

      // Reset distance traveled this tenth_mile
      this->tenth_distanceTraveled = 0;
    }

    if (toPackage->isCompleted()) {
      std::string message = getName() + " picked up: " + package->getName();
      notifyObservers(message);
      package->pickUp();
      delete toPackage;
      toPackage = nullptr;
      pickedUp = true;
      DataManager::getInstance().updatePackageCount();
      std::cout << model->queue.packages.size() << std::endl;
    }
  } else if (toFinalDestination) {
    toFinalDestination->move(this, dt);

    if (package && pickedUp) {
      package->setPosition(position);
      package->setDirection(direction);
    }

    if (toFinalDestination->isCompleted()) {
      std::string message = getName() + " dropped off: " + package->getName();
      notifyObservers(message);
      delete toFinalDestination;
      toFinalDestination = nullptr;
      package->handOff();
      model->queue.removePackage(package);
      package = nullptr;
      available = true;
      pickedUp = false;
    }
  }
}
Package* Drone::getPackage() { return package; };
