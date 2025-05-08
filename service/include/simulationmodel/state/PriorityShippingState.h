#ifndef PRIORITY_SHIPPING_STATE_H_
#define PRIORITY_SHIPPING_STATE_H_

#include <string>

/**
 * @brief Priority Shipping State Interface
*/
class PriorityShippingState {
    public:
        /**
         * @brief Destructor for Priority Shipping State class
        */
       virtual ~PriorityShippingState() {}

        /**
         * @brief Gets the priority value of the current package
         * @return int value representing priority level
        */
       virtual std::string getName() = 0;
};

#endif