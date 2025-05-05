#include "DroneColorDecorator.h"

DroneColorDecorator::DroneColorDecorator(Drone* d, double h, double s, double l)
    : DroneDecorator(d), hue(h), saturation(s), light(l) {}

std::string DroneColorDecorator::getColor() const {
  auto sub_color = sub->getColor();
  double h, s, l;
  auto format = "hsl(%lf, %lf%%, %lf%%)";
  if (sscanf(sub_color.c_str(), format, &h, &s, &l) == 3) {
    h = (hue + h + 360 * (abs(hue - h) > 180)) / 2;
    if (h > 360) h -= 360;
    s = (saturation + s) / 2;
    l = (light + l) / 2;

  } else {
    h = hue;
    s = saturation;
    l = light;
  }
  char color[100];
  snprintf(color, sizeof(color), format, h, s, l);
  return color;
}

void DroneColorDecorator::setColor(double h, double s, double l) {
  hue = h;
  saturation = s;
  light = l;
}

// called every tick of the simulation
void DroneColorDecorator::update(double dt) {
  if (sub->getPackage()) {
    Package* p = sub->getPackage();
    if (distToPackage < 0) {
      distToPackage = (sub->getPosition() - p->getPosition()).magnitude();
    }
    if (distToDestination < 0) {
      distToDestination = (p->getPosition() - p->getDestination()).magnitude();
    }
    if (!sub->pickedUp) {
      double percentage =
          1 -
          ((sub->getPosition() - p->getPosition()).magnitude() / distToPackage);
      setColor(60 * percentage, 100, 50);
    } else if (sub->pickedUp) {
      double percentage =
          1 - ((sub->getPosition() - p->getDestination()).magnitude() /
               distToDestination);

      setColor(60 + 60 * percentage, 100, 50);
    }
  } else {
    setColor(0, 0, 100);
    distToPackage = -1;
    distToDestination = -1;
  }

  sub->update(dt);
}