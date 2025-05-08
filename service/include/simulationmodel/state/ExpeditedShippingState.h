#ifndef EXPEDITED_SHIPPING_STATE_H_
#define EXPEDITED_SHIPPING_STATE_H_

#include "PriorityShippingState.h"
#include "Package.h"
#include <string>

/**
 * @brief Expedited Shipping State
*/
class ExpeditedShippingState : public PriorityShippingState {
    private:
        Package* package;

    public:
        /**
         * @brief Gets Shipping Prioirty of current package
         * @return string representing highest shipping priority
        */
       std::string getName();
};

#endif