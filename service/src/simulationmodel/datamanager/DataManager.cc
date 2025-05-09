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

void DataManager::addEntityToData(IEntity& entity) {
  std::vector<std::string> newRow = {std::to_string(entity.getId()),entity.getName(), "0", "0"};
  data.push_back(newRow);
}

void DataManager::updateDistance(IEntity& entity) {
  for (int row = 1; row < data.size(); row++) {
    if (data[row][0] == std::to_string(entity.getId())) {
        int miles = std::stoi(data[row][2]);
        miles += 1;
        data[row][2] = std::to_string(miles);
        return;
    }
  }
  this->addEntityToData(entity);
}

void DataManager::updatePackageCount(IEntity& entity) {
  
}