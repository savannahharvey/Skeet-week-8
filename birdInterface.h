#pragma once
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
   virtual BirdLogic& getLogic() = 0;

public:
   void kill() {}

   // getters
   bool isDead() { return getLogic().isDead(); }
   int getPoints() { return getLogic().getPoints(); }

   // special functions
   virtual void draw() = 0;
   virtual void advance() = 0;
};

/*********************************************
 * STANDARD
 * A standard bird: slows down, flies in a straight line
 *********************************************/
class Standard : public BirdInterface {
private:
   StandardLogic logic;

protected:
   BirdLogic& getLogic() override { return logic; }
public:
   Standard(double radius = 25.0, double speed = 5.0, int points = 10);
   void draw();
   void advance();
};

/*********************************************
 * FLOATER
 * A bird that floats like a balloon: flies up and really slows down
 *********************************************/
class Floater : public BirdInterface {
private:
   FloaterLogic logic;

public:
   Floater(double radius = 30.0, double speed = 5.0, int points = 15);
   void draw();
   void advance();
};

/*********************************************
 * CRAZY
 * A crazy flying object: randomly changes direction
 *********************************************/
class Crazy : public BirdInterface {
private:
   CrazyLogic logic;

public:
   Crazy(double radius = 30.0, double speed = 4.5, int points = 30);
   void draw();
   void advance();
};

/*********************************************
 * SINKER
 * A sinker bird: honors gravity
 *********************************************/
class Sinker : public BirdInterface {
private:
   SinkerLogic logic;

public:
   Sinker(double radius = 30.0, double speed = 4.5, int points = 20);
   void draw();
   void advance();
};
