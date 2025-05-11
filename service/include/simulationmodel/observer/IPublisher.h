#ifndef IPUBLISHER_H_
#define IPUBLISHER_H_

#include <set>
#include <string>

#include "IObserver.h"

class IPublisher {
 public:
  virtual void addObserver(const IObserver *o);
  virtual void removeObserver(const IObserver *o);
  virtual void notifyObservers(const std::string &message);

 protected:
  std::set<const IObserver *> observers;
};

#endif  // IPUBLISHER_H_
