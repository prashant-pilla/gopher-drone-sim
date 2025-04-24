#ifndef PRIORITY_SHIPPING_STATE_H_
#define PRIORITY_SHIPPING_STATE_H_

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
       virtual int getPriority() = 0;
};

#endif