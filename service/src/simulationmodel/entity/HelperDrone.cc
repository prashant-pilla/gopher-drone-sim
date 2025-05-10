#include "HelperDrone.h"

#include "BeelineStrategy.h"
#include "HandoffRequest.h"
#include "SimulationModel.h"

HelperDrone::HelperDrone(const JsonObject &obj) : Drone(obj) {}

void HelperDrone::notify(const std::string &message, void *data) const {
  if (message == "HANDOFF_REQUEST" && isAvailable()) {
    auto *request = static_cast<HandoffRequest *>(data);

    // Calculate 3D distance using existing drone position
    Vector3 helperPos = getPosition();
    float distance = (helperPos - request->packagePosition).magnitude();

    request->considerCandidate(const_cast<HelperDrone *>(this), distance);
  }
}

void HelperDrone::acceptHandoff(Package *package) {
  this->package = package;
  available = false;

  // Initialize strategy
  toPackage = new BeelineStrategy(getPosition(), package->getPosition());

  // Notify through model
  if (model) {
    std::string msg =
        "HelperDrone " + std::to_string(getId()) + " accepted handoff";
    model->notify(msg, nullptr);
  }
}

bool HelperDrone::isAvailable() const {
  return available && (package == nullptr);
}