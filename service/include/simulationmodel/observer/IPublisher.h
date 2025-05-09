#ifndef IPUBLISHER_H_
#define IPUBLISHER_H_

#include <set>
#include <string>

#include "IObserver.h"

class IPublisher
{
public:
  virtual void addObserver(const IObserver *o) = 0;
  virtual void removeObserver(const IObserver *o) = 0;
  virtual void notifyObservers(const std::string &message, void *data = nullptr) = 0;

protected:
  std::set<const IObserver *> observers;
};

#endif // IPUBLISHER_H_
