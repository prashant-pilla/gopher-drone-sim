#include "Package.h"

#include "Robot.h"

#include "PriorityShippingState.h"

#include "NoRushShippingState.h"

#include "StandardShippingState.h"

#include "ExpeditedShippingState.h"

Package::Package(const JsonObject& obj) : IEntity(obj) {}

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
  requiresDelivery_ = false;
  destination = owner->getPosition();
}

void Package::handOff() {
  if (owner) {
    owner->receive(this);
  }
}

int Package::getPriority() {
  return shippingState->getPriority();
}

void Package::setPriority(int level) {
  if (shippingState) {
    delete shippingState;
  }
  
  if (level == 0) {
    shippingState = new NoRushShippingState();
  } else if (level == 1) {
    shippingState = new StandardShippingState();
  } else {
    shippingState = new ExpeditedShippingState();
  }
}
