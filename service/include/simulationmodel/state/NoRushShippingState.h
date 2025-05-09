#ifndef NO_RUSH_SHIPPING_STATE_H_
#define NO_RUSH_SHIPPING_STATE_H_

#include <string>

#include "Package.h"
#include "PriorityShippingState.h"

/**
 * @brief No-RushShipping State
 */
class NoRushShippingState : public PriorityShippingState {
 private:
  Package* package;

 public:
  /**
   * @brief Gets Shipping Prioirty of current package
   * @return string representing lowest shipping priority
   */
  std::string getName();
};

#endif