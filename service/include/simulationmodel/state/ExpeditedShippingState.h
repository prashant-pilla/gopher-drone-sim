#ifndef EXPEDITED_SHIPPING_STATE_H_
#define EXPEDITED_SHIPPING_STATE_H_

#include "PriorityShippingState.h"
#include "Package.h"

/**
 * @brief Expedited Shipping State
*/
class ExpeditedShippingState : public PriorityShippingState {
    private:
        Package* package;

    public:
        /**
         * @brief Gets Shipping Prioirty of current package
         * @return int representing highest shipping priority
        */
       int getPriority();
};

#endif