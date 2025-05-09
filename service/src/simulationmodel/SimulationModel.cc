#include "SimulationModel.h"

#include "DroneFactory.h"
#include "HelicopterFactory.h"
#include "HumanFactory.h"
#include "PackageFactory.h"
#include "RobotFactory.h"

SimulationModel::SimulationModel(IController &controller)
    : controller(controller) {
  entityFactory.addFactory(new DroneFactory());
  entityFactory.addFactory(new PackageFactory());
  entityFactory.addFactory(new RobotFactory());
  entityFactory.addFactory(new HumanFactory());
  entityFactory.addFactory(new HelicopterFactory());
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (auto &[id, entity] : entities) {
    delete entity;
  }
  delete graph;
}

void SimulationModel::linkDroneObservers(IEntity *entity) {
  // Link new helpers to existing leaders
  if (auto helper = dynamic_cast<HelperDrone *>(entity)) {
    for (auto &[id, existing] : entities) {
      if (auto leader = dynamic_cast<LeaderDrone *>(existing)) {
        leader->addObserver(helper);
      }
    }
  }

  // Link new leaders to existing helpers
  if (auto leader = dynamic_cast<LeaderDrone *>(entity)) {
    for (auto &[id, existing] : entities) {
      if (auto helper = dynamic_cast<HelperDrone *>(existing)) {
        leader->addObserver(helper);
      }
    }
  }
}

IEntity *SimulationModel::createEntity(const JsonObject &entity) {
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  IEntity *myNewEntity = nullptr;
  if (myNewEntity = entityFactory.createEntity(entity)) {
    // Call AddEntity to add it to the view
    linkDroneObservers(myNewEntity);
    myNewEntity->linkModel(this);
    controller.addEntity(*myNewEntity);
    entities[myNewEntity->getId()] = myNewEntity;
    // Add the simulation model as a observer to myNewEntity
    myNewEntity->addObserver(this);
  }

  return myNewEntity;
}

void SimulationModel::removeEntity(int id) { removed.insert(id); }

/// Schedules a Delivery for an object in the scene
void SimulationModel::scheduleTrip(const JsonObject &details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  Robot *receiver = nullptr;

  for (auto &[id, entity] : entities) {
    if (name == entity->getName()) {
      if (Robot *r = dynamic_cast<Robot *>(entity)) {
        if (r->requestedDelivery) {
          receiver = r;
          break;
        }
      }
    }
  }

  Package *package = nullptr;

  for (auto &[id, entity] : entities) {
    if (name + "_package" == entity->getName()) {
      if (Package *p = dynamic_cast<Package *>(entity)) {
        if (p->requiresDelivery()) {
          package = p;
          break;
        }
      }
    }
  }

  if (receiver && package) {
    package->initDelivery(receiver);
    std::string strategyName = details["search"];
    package->setStrategyName(strategyName);
    scheduledDeliveries.push_back(package);
    controller.sendEventToView("DeliveryScheduled", details);
  }
}

const routing::Graph *SimulationModel::getGraph() const { return graph; }

void SimulationModel::setGraph(const routing::Graph *graph) {
  if (this->graph) delete this->graph;
  this->graph = graph;
}

/// Updates the simulation
void SimulationModel::update(double dt) {
  for (auto &[id, entity] : entities) {
    entity->update(dt);
    controller.updateEntity(*entity);
    if (auto drone = dynamic_cast<Drone *>(entity)) {
      if (auto leader = dynamic_cast<LeaderDrone *>(drone)) {
        leader->updateBattery(dt);
      }
    }
  }
  for (int id : removed) {
    removeFromSim(id);
  }
  removed.clear();
}

void SimulationModel::stop(void) {}

void SimulationModel::removeFromSim(int id) {
  IEntity *entity = entities[id];
  if (entity) {
    for (auto i = scheduledDeliveries.begin(); i != scheduledDeliveries.end();
         ++i) {
      if (*i == entity) {
        scheduledDeliveries.erase(i);
        break;
      }
    }
    controller.removeEntity(*entity);
    entities.erase(id);
    delete entity;
  }
}

void SimulationModel::notify(const std::string &message, void *data) const {
  JsonObject details;
  if (data) {
    // Handle data if needed
  }
  details["message"] = message;
  this->controller.sendEventToView("Notification", details);
}
