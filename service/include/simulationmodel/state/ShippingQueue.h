#ifndef SHIPPING_QUEUE_H_
#define SHIPPING_QUEUE_H_

#include <vector>

#include "Package.h"

class Package;

/**
 * @brief class for Shipping queue structure
 */
class ShippingQueue {
 public:
  /**
   * @brief constructor
   */
  ShippingQueue(){};

  /**
   * @brief add a package to the queue
   * @param pkg package to be added to queue
   */
  void addPackage(Package* pkg);

  /**
   * @brief remove desired package
   * @param pkg pointer to package to be removed from front of queue
   */
  void removePackage(Package* pkg);

  /**
   * @brief update the priority of a package
   * @param pkg package to be updated
   * @param priority new priority shipping level
   */
  void updatePackage(Package* pkg, const std::string& priority);

  /**
   * @brief sort queue by priority
   */
  void sortQueue();

  std::vector<Package*> packages;
};

#endif
