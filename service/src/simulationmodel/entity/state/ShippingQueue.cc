#include "ShippingQueue.h"
#include "Package.h"
#include <queue>

void ShippingQueue::addPackage(Package* pkg) {
    packages.push_back(pkg);
    ShippingQueue::sortQueue();
}

Package* ShippingQueue::removePackage() {
    if (packages.empty()) return nullptr;
    Package* front = packages.front();
    packages.erase(packages.begin());
    return front;
}

void ShippingQueue::updatePackage(Package* pkg, int level) {
    pkg->setPriority(level);
    ShippingQueue::sortQueue();
}

void ShippingQueue::sortQueue() {
    std::stable_sort(packages.begin(), packages.end(), [](Package* a, Package* b) {
        return a->getPriority() > b->getPriority(); 
    });
}