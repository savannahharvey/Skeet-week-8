/***********************************************************************
 * Header File:
 *    BirdInterface : Everything that can be shot
 * Author:
 *    Porter Williams
 * Summary:
 *    Stuff that moves across the screen to be shot
 ************************************************************************/

#pragma once
#include "birdLogic.h"
#include "position.h"

/**********************
 * BIRD
 * Everything that can be shot
 **********************/
class BirdInterface {
protected:
  // takes a pointer so each derived interface can have its own derived logic
  BirdLogic *logic;

public:
  // base BirdLogic just initializes logic attribute
  BirdInterface(BirdLogic *l) : logic(l) {}
  virtual ~BirdInterface() {
    delete logic;
  } // free logic's memory when BirdInterface or its children are destroyed
  void kill() { logic->kill(); }

  // getters
  const Position &getPosition() const { return logic->getPosition(); }
  const Velocity &getVelocity() const { return logic->getVelocity(); }
  double getRadius() const { return logic->getRadius(); }
  bool isDead() const { return logic->isDead(); }
  int getPoints() const { return logic->getPoints(); }

  void setPoints(int points) { logic->setPoints(points); }

  // special functions
  void advance() { logic->advance(); }
  virtual void draw() = 0;
};

/*********************************************
 * STANDARD
 * A standard bird: slows down, flies in a straight line
 *********************************************/
class StandardInterface : public BirdInterface {
public:
  StandardInterface(double radius = 25.0, double speed = 5.0, int points = 10,
                  const Position& dimensions = Position(0,0));
  void draw();
};

/*********************************************
 * FLOATER
 * A bird that floats like a balloon: flies up and really slows down
 *********************************************/
class FloaterInterface : public BirdInterface {
public:
  FloaterInterface(double radius = 30.0, double speed = 5.0, int points = 15,
                   const Position &dimensions = Position(0, 0));
  void draw();
};

/*********************************************
 * CRAZY
 * A crazy flying object: randomly changes direction
 *********************************************/
class CrazyInterface : public BirdInterface {
public:
  CrazyInterface(double radius = 30.0, double speed = 4.5, int points = 30,
                 const Position &dimensions = Position(0, 0));
  void draw();
};

/*********************************************
 * SINKER
 * A sinker bird: honors gravity
 *********************************************/
class SinkerInterface : public BirdInterface {
public:
  SinkerInterface(double radius = 30.0, double speed = 4.5, int points = 20,
                  const Position &dimensions = Position(0, 0));
  void draw();
};
