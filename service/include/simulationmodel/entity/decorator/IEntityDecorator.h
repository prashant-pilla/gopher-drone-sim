#ifndef ENTITY_DECORATOR_H_
#define ENTITY_DECORATOR_H_

#include <concepts>

#include "IEntity.h"

template <std::derived_from<IEntity> T = IEntity>
class IEntityDecorator : public T {
 public:
  IEntityDecorator(T* e) : T(e->getDetails()), sub(e) {}
  virtual ~IEntityDecorator() {
    if (sub) delete sub;
  }
  virtual void linkModel(SimulationModel* model) {
    return sub->linkModel(model);
  }
  virtual SimulationModel* getModel() { return sub->getModel(); }
  virtual int getId() const { return sub->getId(); }
  virtual Vector3 getPosition() const { return sub->getPosition(); }
  virtual Vector3 getDirection() const { return sub->getDirection(); }
  virtual const JsonObject& getDetails() const { return sub->getDetails(); }
  virtual std::string getColor() const { return sub->getColor(); }
  virtual std::string getName() const { return sub->getName(); }
  virtual double getSpeed() const { return sub->getSpeed(); }
  virtual void setSpeed(double speed) { sub->setSpeed(speed); }
  virtual void setPosition(Vector3 pos_) { return sub->setPosition(pos_); }
  virtual void setDirection(Vector3 dir_) { return sub->setDirection(dir_); }
  virtual void setColor(std::string col_) { return sub->setColor(col_); }
  virtual void rotate(double angle) { return sub->rotate(angle); }
  virtual void update(double dt) { return sub->update(dt); }

  virtual void addObserver(const IObserver* o) { return sub->addObserver(o); };
  virtual void removeObserver(const IObserver* o) {
    return sub->removeObserver(o);
  };
  virtual void notifyObservers(const std::string& message) {
    return sub->notifyObservers(message);
  };

 protected:
  T* sub = nullptr;
};

#endif
