#ifndef DATA_MANAGER_H_
#define DATA_MANAGER_H_

#include <iostream>
#include <fstream>

/**
 * @class DataManager
 * @brief Data Manager class to track event-driven data. Only one instance
 * throughout entire program (singleton pattern)
 */
class DataManager {
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

 private:
  /**
   * @brief Constructor
   */
  DataManager() {};
  /**
   * @brief Destructor
   */
  ~DataManager();

  static DataManager* instance;
};

#endif