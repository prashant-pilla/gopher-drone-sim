#include "ShippingQueue.h"

#include <queue>

#include "Package.h"

void ShippingQueue::addPackage(Package* pkg) {
  packages.push_back(pkg);
  ShippingQueue::sortQueue();
}

void ShippingQueue::removePackage(Package* pkg) {
  auto it = std::find(packages.begin(), packages.end(), pkg);
  if (it != packages.end()) {
    packages.erase(it);
  }
}

void ShippingQueue::updatePackage(Package* pkg, const std::string& priority) {
  ShippingQueue::sortQueue();
}

void ShippingQueue::sortQueue() {
  std::stable_sort(packages.begin(), packages.end(),
                   [](Package* a, Package* b) {
                     return a->getPriorityLevel() > b->getPriorityLevel();
                   });
}