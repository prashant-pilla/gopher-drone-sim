#ifndef STANDARD_SHIPPING_STATE_H_
#define STANDARD_SHIPPING_STATE_H_

#include "PriorityShippingState.h"
#include "Package.h"
#include <string>

/**
 * @brief Standard Shipping State
*/
class StandardShippingState : public PriorityShippingState {
    private:
        Package* package;

    public:
        /**
         * @brief Gets Shipping Prioirty of current package
         * @return string representing middle shipping priority
        */
       std::string getName();
};

#endif