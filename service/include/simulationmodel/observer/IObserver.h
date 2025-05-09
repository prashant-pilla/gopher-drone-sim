#ifndef IOBSERVER_H_
#define IOBSERVER_H_

#include <string>

class IPublisher;

class IObserver {
 public:
  virtual ~IObserver() = default;
  virtual void notify(const std::string &message, void* data) const = 0;
};

#endif  // IOBSERVER_H_
