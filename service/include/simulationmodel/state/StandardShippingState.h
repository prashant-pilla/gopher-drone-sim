#ifndef STANDARD_SHIPPING_STATE_H_
#define STANDARD_SHIPPING_STATE_H_

#include "PriorityShippingState.h"
#include "Package.h"

/**
 * @brief Standard Shipping State
*/
class StandardShippingState : public PriorityShippingState {
    private:
        Package* package;

    public:
        /**
         * @brief Constructor
        */
       StandardShippingState();

        /**
         * @brief Gets Shipping Prioirty of current package
         * @return int representing middle shipping priority
        */
       int getPriority() { return 1; }
};

#endif