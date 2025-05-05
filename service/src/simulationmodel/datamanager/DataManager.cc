#include "DataManager.h"

DataManager* DataManager::instance = nullptr;

DataManager& DataManager::getInstance() {
  if (!instance) {
    instance = new DataManager();
  }
  return *instance;
}