/***********************************************************************
 * Header File:
 *    BirdInterface : Everything that can be shot
 * Author:
 *    Porter Williams
 * Summary:
 *    Stuff that moves across the screen to be shot
 ************************************************************************/

#pragma once
#include "position.h"
#include "birdLogic.h"

 /**********************
  * BIRD
  * Everything that can be shot
  **********************/
class BirdInterface
{
protected:
   // takes a pointer so each derived interface can have its own derived logic 
   BirdLogic* logic;

public:
   // base BirdLogic just initializes logic attribute
   BirdInterface(BirdLogic* l) : logic(l) {}
   virtual ~BirdInterface() { delete logic; } // free logic's memory when BirdInterface or its children are destroyed
   void kill() { logic->kill(); }

   // getters
   const Position& getPosition() const { return logic->getPosition(); }
   const Velocity& getVelocity() const { return logic->getVelocity(); }  
   double getRadius()            const { return logic->getRadius(); }  
   bool isDead()                 const { return logic->isDead(); }
   int getPoints()               const { return logic->getPoints(); }

   void setPoints(int points)          { logic->setPoints(points); }

   // special functions
   virtual void advance() { logic->advance(); }
   virtual void draw() = 0;
};

/*********************************************
 * STANDARD
 * A standard bird: slows down, flies in a straight line
 *********************************************/
class Standard : public BirdInterface 
{
public:
   Standard(double radius = 25.0, double speed = 5.0, int points = 10);
   void draw();
   void advance();
};

/*********************************************
 * FLOATER
 * A bird that floats like a balloon: flies up and really slows down
 *********************************************/
class Floater : public BirdInterface 
{
public:
   Floater(double radius = 30.0, double speed = 5.0, int points = 15);
   void draw();
   void advance();
};

/*********************************************
 * CRAZY
 * A crazy flying object: randomly changes direction
 *********************************************/
class Crazy : public BirdInterface 
{
public:
   Crazy(double radius = 30.0, double speed = 4.5, int points = 30);
   void draw();
   void advance();
};

/*********************************************
 * SINKER
 * A sinker bird: honors gravity
 *********************************************/
class Sinker : public BirdInterface 
{
public:
   Sinker(double radius = 30.0, double speed = 4.5, int points = 20);
   void draw();
   void advance();
};
