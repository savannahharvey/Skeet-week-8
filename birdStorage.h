#pragma once

#include "position.h"

/***********************************************************************
 * BIRD STORAGE
 * BirdStorage: The storage object for the state of a bird
 ***********************************************************************/
class BirdStorage
{
private:
   Position pt;
   Velocity v;
   double radius;
   bool dead;
   int points;
   Position dimensions;
public:
   BirdStorage(double radius, int points, Position dimensions)
      : pt(Position(0.0, 0.0)), v(Velocity(0.0, 0.0)),
      radius(radius), points(points), dimensions(dimensions),
      dead(false) {
   }

   // Getters
   const Position& getPosition() const { return pt; }
   const Velocity& getVelocity() const { return v; }
   double getRadius() const { return radius; }
   int getPoints()    const { return points; }
   bool isDead()      const { return dead; }
   const Position& getDimensions() const { return dimensions; }

   // Setters
   void setPosition(const Position& rhs) { pt = rhs; }
   void setVelocity(const Velocity& rhs) { v = rhs; }
   void setPoints(int pts) { points = pts; }
   void kill() { dead = true; }
};