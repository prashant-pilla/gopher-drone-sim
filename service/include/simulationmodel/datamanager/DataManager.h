#ifndef DATA_MANAGER_H_
#define DATA_MANAGER_H_

#include <fstream>
#include <iostream>
#include <vector>

#include "IEntity.h"
#include "IPublisher.h"

/**
 * @class DataManager
 * @brief Data Manager class to track event-driven data. Only one instance
 * throughout entire program (singleton pattern)
 */
class DataManager : public IPublisher {
 public:
  /**
   * @brief Controls access to the DataManager instance. Initially creates
   * a DataManager instance and places it into static field. Subsequently
   * returns existing DataManager object.
   */
  static DataManager& getInstance();
  /**
   * @brief Removing the copy constructor operator so that
   * DataManager cannot be copied.
   */
  DataManager(const DataManager&) = delete;
  /**
   * @brief Removing the assignment operator so that
   * DataManager cannot be copied.
   */
  DataManager& operator=(const DataManager&) = delete;
  /**
   * @brief Write data to a csv file for export/persistance
   */
  void writeToFile();
  /**
   * @brief Enter/update distance traveled of Entity
   * @param entity IEntity object that we want to update distance of
   * @param dist double of newly acquired distance
   */
  void updateDistance(IEntity& entity, double dist);
  /**
   * @brief Enter/update number of packages dropped of by an entity
   * @param entity IEntity object that we want to update package count of
   */
  void updatePackageCount(IEntity& entity);

 private:
  /**
   * @brief Constructor
   */
  DataManager() {
    data = {{"Entity Type", "Name", "Distance Traveled (miles)",
             "Packages Delivered"}};
  }
  /**
   * @brief Destructor
   */
  ~DataManager();

  static DataManager* instance;
  std::vector<std::vector<std::string>> data;
};

#endif