#include "DataManager.h"

DataManager* DataManager::instance = nullptr;

DataManager& DataManager::getInstance() {
  if (!instance) {
    instance = new DataManager();
  }
  return *instance;
}

void DataManager::writeToFile() {
  std::ofstream file("Simulation_Statistics.csv");

  if (!file.is_open()) {  // make sure file was successfully opened
    this->notifyObservers("Data export failure");  // notify front end that file
                                                   // wasnt exported/written
    return;
  }

  for (int row = 0; row < data.size(); row++) {
    for (int col = 0; col < data[row].size(); col++) {
      file << data[row][col];
      if (col != data[row].size() - 1) file << ',';
    }
    file << '\n';
  }

  file.close();

  this->notifyObservers("Data successfully exported");
}

void DataManager::updateDistance(IEntity& entity, double dist) {

}

void DataManager::updatePackageCount(IEntity& entity) {
  
}