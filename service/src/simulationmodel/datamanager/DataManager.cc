#include "DataManager.h"

DataManager& DataManager::getInstance() {
  if (!instance) {
    instance = new DataManager();
  }
  return *instance;
}