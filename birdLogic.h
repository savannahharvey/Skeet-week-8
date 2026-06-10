/***********************************************************************
 * Header File:
 *    BirdLogic : Everything that can be shot, but logic
 * Author:
 *    Savannah Harvey
 * Summary:
 *    Stuff that moves across the screen to be shot, the logic
 ************************************************************************/

#pragma once

#include <cassert>  // for assert
#include "position.h"
#include "BirdStorage.h"

// helper function for calculating starting y position for birds
inline double randomFloat(double min, double max)
{
	assert(min <= max);
	double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
	assert(min <= num && num <= max);
	return num;
}

inline int randomInt(int min, int max)
{
	assert(min <= max);
	int num = min + rand() % (max - min + 1);
	assert(min <= num && num <= max);
	return num;
}

 /**********************
  * BIRD LOGIC
  * Everything that can be shot, the logic
  **********************/
class BirdLogic
{
protected:
	BirdStorage birdStorage;

public:
	BirdLogic(double radius, int points, const Position& dimensions) : birdStorage(radius, points, dimensions) {}
	// made virtual to prevent memory leaks from derived children
	virtual ~BirdLogic() {}

	// added getters for Interface (to minimize changing how Skeet currently works)
	const Position& getPosition() const  { return birdStorage.getPosition(); }  // for collision checking 
	const Velocity& getVelocity() const  { return birdStorage.getVelocity(); }  // for minimumDistance() in Skeet collision checking
	double getRadius()            const  { return birdStorage.getRadius();   }  // for collision checking
	int getPoints()               const  { return birdStorage.getPoints(); }    // for updating score and points spawning
	bool isDead()                 const  { return birdStorage.isDead();      }  // to know whether to remove bird
	bool isOutOfBounds()          const
	{
		return (getPosition().getX() < -getRadius() || getPosition().getX() >= birdStorage.getDimensions().getX() + getRadius() ||
			     getPosition().getY() < -getRadius() || getPosition().getY() >= birdStorage.getDimensions().getY() + getRadius());
	}

	void setPoints(int points) { birdStorage.setPoints(points); }               // for zeroing out birds that we have already used the points of
	void kill() { birdStorage.kill(); }
	virtual void advance() = 0;
};

// BirdLogic and its children do not have direct access to manipulate the values of the bird. Its
// derived classes must be changed to utilize birdStorage's GETTERS and SETTERS anytime it needs to 
// retrieve or manipulate bird's values. These should also be in a .cpp file. 

//               |
//               V

// StandardLogic is done as an example, but the other derived classes must be updated to use birdStorage's methods as well.

/*********************************************
 * STANDARD LOGIC
 * A standard logic bird: slows down, flies in a straight line
 *********************************************/
class StandardLogic : public BirdLogic
{
public:
	// changed to use BirdLogic's (its parent's) constructor as it properly sets up the BirdStorage object
	StandardLogic(double radius, double speed, int points, const Position& dimensions) : BirdLogic(radius, points, dimensions) 
	{
		double randomY = randomFloat(dimensions.getY() * 0.25, dimensions.getY() * 0.75);
		Position initialPos = Position(0.0, randomY);
		// set initial starting position for StandardBird
		birdStorage.setPosition(initialPos);

		double randomDX = randomFloat(speed - 0.5, speed + 0.5);
		double randomDY = randomFloat(-speed / 5.0, speed / 5.0);
		Velocity initialVel = Velocity(randomDX, randomDY);
		// set initial velocity for StandardBird
		birdStorage.setVelocity(initialVel);
	}

	virtual void advance()
	{
		// small amount of drag
		Velocity newVel = birdStorage.getVelocity();         // now uses getVelocity to retrieve bird's current velocity
		newVel *= 0.995; 
		birdStorage.setVelocity(newVel);                     // now uses birdStorage's setVelocity to update bird's velocity

		// inertia
		Position newPos = birdStorage.getPosition();         // now gets current position with birdStorage getter
		newPos.add(newVel);                                  
		birdStorage.setPosition(newPos);                     // sets bird's position with birdStorage's setPosition setter

		// out of bounds checker
		if (isOutOfBounds())
		{
			kill();
			// points go negative when it is missed!
			int newPoints = birdStorage.getPoints() * -1;     // gets points with birdStorage's getPoints
			birdStorage.setPoints(newPoints);                 // updates bird's points with birdStorage's setPoints
		}
	}
};

// NEEDS UPDATING

/*********************************************
 * FLOATER LOGIC
 * A bird that floats like a balloon: flies up and really slows down
 *********************************************/
class FloaterLogic : public BirdLogic
{
public:
	// changed to use BirdLogic's (its parent's) constructor as it properly sets up the BirdStorage object
	FloaterLogic(double radius, double speed, int points, const Position& dimensions) : BirdLogic(radius, points, dimensions)
	{
		double randomY = randomFloat(dimensions.getY() * 0.01, dimensions.getY() * 0.5);
		Position initialPos = Position(0.0, randomY);
		// set initial starting position for FloaterBird
		birdStorage.setPosition(initialPos);

		double randomDX = randomFloat(speed - 0.5, speed + 0.5);
		double randomDY = randomFloat(0.0, speed / 3.0);
		Velocity initialVel = Velocity(randomDX, randomDY);
		// set initial velocity for FloaterBird
		birdStorage.setVelocity(initialVel);
	}
	
	virtual void advance()
	{
		// small amount of drag
		Velocity newVel = birdStorage.getVelocity();         // now uses getVelocity to retrieve bird's current velocity
		newVel *= 0.990;
		birdStorage.setVelocity(newVel);                     // now uses birdStorage's setVelocity to update bird's velocity

		// anti-gravity
		newVel.addDy(0.05);                                  // now uses addDy to update bird's velocity with anti-gravity

		// inertia
		Position newPos = birdStorage.getPosition();         // now gets current position with birdStorage getter
		newPos.add(newVel);
		birdStorage.setPosition(newPos);                     // sets bird's position with birdStorage's setPosition setter

		// out of bounds checker
		if (isOutOfBounds())
		{
			kill();
			// points go negative when it is missed!
			int newPoints = birdStorage.getPoints() * -1;     // gets points with birdStorage's getPoints
			birdStorage.setPoints(newPoints);                 // updates bird's points with birdStorage's setPoints
		}
	}
};

// NEEDS UPDATING

/*********************************************
 * CRAZY
 * A crazy flying object: randomly changes direction
 *********************************************/
class CrazyLogic : public BirdLogic
{
public:
	// changed to use BirdLogic's (its parent's) constructor as it properly sets up the BirdStorage object
	CrazyLogic(double radius, double speed, int points, const Position& dimensions) : BirdLogic(radius, points, dimensions)
	{
		double randomY = randomInt(0, 15);
		Position initialPos = Position(0.0, randomY);
		// set initial starting position for CrazyBird
		birdStorage.setPosition(initialPos);

		double randomDX = randomFloat(speed - 0.5, speed + 0.5);
		double randomDY = randomFloat(-speed / 5.0, speed / 5.0);
		Velocity initialVel = Velocity(randomDX, randomDY);
		// set initial velocity for CrazyBird
		birdStorage.setVelocity(initialVel);
	}
	
	virtual void advance()
	{
		// erratic turns eery half a second or so
		double randomNum = randomFloat(0, 15);
		Velocity newVel = birdStorage.getVelocity();         // now uses getVelocity to retrieve bird's current velocity
		if (randomNum == 0)
		{
			newVel.addDy(randomFloat(-1.5, 1.5));
			newVel.addDx(randomFloat(-1.5, 1.5));
		}
		birdStorage.setVelocity(newVel);                     // now uses birdStorage's setVelocity to update bird's velocity

		// inertia
		Position newPos = birdStorage.getPosition();         // now gets current position with birdStorage getter
		newPos.add(newVel);
		birdStorage.setPosition(newPos);                     // sets bird's position with birdStorage's setPosition setter

		// out of bounds checker
		if (isOutOfBounds())
		{
			kill();
			// points go negative when it is missed!
			int newPoints = birdStorage.getPoints() * -1;     // gets points with birdStorage's getPoints
			birdStorage.setPoints(newPoints);                 // updates bird's points with birdStorage's setPoints
		}
	}
};

// NEEDS UPDATING 

/*********************************************
 * SINKER
 * A sinker bird: honors gravity
 *********************************************/
class SinkerLogic : public BirdLogic
{
public:
	// changed to use BirdLogic's (its parent's) constructor as it properly sets up the BirdStorage object
	SinkerLogic(double radius, double speed, int points, const Position& dimensions) : BirdLogic(radius, points, dimensions)
	{
		double randomY = randomFloat(dimensions.getY() * 0.5, dimensions.getY() * 0.95);
		Position initialPos = Position(0.0, randomY);
		// set initial starting position for SinkerBird
		birdStorage.setPosition(initialPos);

		double randomDX = randomFloat(speed - 0.5, speed + 0.5);
		double randomDY = randomFloat(-speed / 3.0, 0.0);
		Velocity initialVel = Velocity(randomDX, randomDY);
		// set initial velocity for SinkerBird
		birdStorage.setVelocity(initialVel);
	}

	virtual void advance()
	{
		// gravity
		Velocity newVel = birdStorage.getVelocity();         // now uses getVelocity to retrieve bird's current velocity
		newVel *= -0.07;
		birdStorage.setVelocity(newVel);                     // now uses birdStorage's setVelocity to update bird's velocity

		// inertia
		Position newPos = birdStorage.getPosition();         // now gets current position with birdStorage getter
		newPos.add(newVel);
		birdStorage.setPosition(newPos);                     // sets bird's position with birdStorage's setPosition setter

		// out of bounds checker
		if (isOutOfBounds())
		{
			kill();
			// points go negative when it is missed!
			int newPoints = birdStorage.getPoints() * -1;     // gets points with birdStorage's getPoints
			birdStorage.setPoints(newPoints);                 // updates bird's points with birdStorage's setPoints
		}
	}
};