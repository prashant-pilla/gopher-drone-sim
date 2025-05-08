#include "Package.h"

#include "Robot.h"

#include "PriorityShippingState.h"

#include "NoRushShippingState.h"

#include "StandardShippingState.h"

#include "ExpeditedShippingState.h"

#include <string>

Package::Package(const JsonObject& obj, const std::string& priority) : IEntity(obj) {
  setPriority(priority);
}

Vector3 Package::getDestination() const { return destination; }

std::string Package::getStrategyName() const { return strategyName; }

Robot* Package::getOwner() const { return owner; }

bool Package::requiresDelivery() const { return requiresDelivery_; }

void Package::setStrategyName(std::string strategyName_) {
  strategyName = strategyName_;
}

void Package::update(double dt) {}

void Package::initDelivery(Robot* owner) {
  this->owner = owner;
  owner->requestedDelivery = false;
  //requiresDelivery_ = false;
  destination = owner->getPosition();
}

void Package::handOff() {
  if (owner) {
    owner->receive(this);
    requiresDelivery_ = false;
  }
}

PriorityShippingState* Package::getPriorityState() const {
  return shippingState;
}

int Package::getPriorityLevel() const {
  std::string priorityLevel = shippingState->getName();
  if (priorityLevel == "Expedited") {
    return 2;
  } else if (priorityLevel == "NoRush") {
    return 0;
  } else {
    return 1;
  }
}

void Package::setPriority(const std::string& priority) {
  if (shippingState) {
    delete shippingState;
  }

  if (priority == "NoRush") {
    shippingState = new NoRushShippingState();
  } else if (priority == "Expedited") {
    shippingState = new ExpeditedShippingState();
  } else {
    shippingState = new StandardShippingState();
  }
}
