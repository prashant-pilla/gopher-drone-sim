#ifndef SHIPPING_QUEUE_H_
#define SHIPPING_QUEUE_H_

#include "Package.h"
#include <vector>

class Package;

/**
 * @brief class for Shipping queue structure
*/
class ShippingQueue {
    public:
        /**
         * @brief constructor
        */
       ShippingQueue() {};

       /**
        * @brief add a package to the queue
        * @param pkg package to be added to queue
       */
      void addPackage(Package* pkg);

      /**
       * @brief remove and return package at front of queue
       * @retval pointer to package to be removed from front of queue
      */
     Package* removePackage();

     /**
      * @brief update the priority of a package
      * @param pkg package to be updated
      * @param level new priority shipping level
     */
        void updatePackage(Package* pkg, int level);

        /**
         * @brief sort queue by priority
        */
    void sortQueue();

    private:
        std::vector<Package*> packages;
};

#endif
