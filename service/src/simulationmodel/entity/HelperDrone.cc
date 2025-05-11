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

  // Initialize strategy
  toPackage = new BeelineStrategy(getPosition(), package->getPosition());

  // Notify through model
  if (model) {
    std::string msg =
        "HelperDrone " + std::to_string(getId()) + " accepted handoff";
    model->notify(msg);
  }
}

bool HelperDrone::isAvailable() const {
  return available && (package == nullptr);
}