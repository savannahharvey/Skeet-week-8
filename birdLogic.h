/***********************************************************************
 * Header File:
 *    BirdLogic : Everything that can be shot, but logic
 * Author:
 *    Savannah Harvey
 * Summary:
 *    Stuff that moves across the screen to be shot, the logic
 ************************************************************************/

#pragma once
#include "position.h"
#include "BirdStorage.h"

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
	~BirdLogic() = 0 {}

	bool isOutOfBounds() const
	{
		return (pt.getX() < -radius || pt.getX() >= dimensions.getX() + radius ||
			pt.getY() < -radius || pt.getY() >= dimensions.getY() + radius);
	}

	virtual void advance() = 0 {}
};


/*********************************************
 * STANDARD LOGIC
 * A standard logic bird: slows down, flies in a straight line
 *********************************************/
class StandardLogic : public BirdLogic
{
public:
	StandardLogic(double radius, int points, const Position& dimensions) : birdStorage(radius, points, dimensions) {}
	virtual void advance()
	{
		// small amount of drag
		v *= 0.995;

		// inertia
		pt.add(v);

		// out of bounds checker
		if (isOutOfBounds())
		{
			kill();
			points *= -1; // points go negative when it is missed!
		}
	}
};

/*********************************************
 * FLOATER
 * A bird that floats like a balloon: flies up and really slows down
 *********************************************/
class FloaterLogic : public BirdLogic
{
public:
	FloaterLogic(double radius, int points, const Position& dimensions) : birdStorage(radius, points, dimensions) {}
	virtual void advance()
	{
		// large amount of drag
		v *= 0.990;

		// inertia
		pt.add(v);

		// anti-gravity
		v.addDy(0.05);

		// out of bounds checker
		if (isOutOfBounds())
		{
			kill();
			points *= -1; // points go negative when it is missed!
		}
	}
};

/*********************************************
 * CRAZY
 * A crazy flying object: randomly changes direction
 *********************************************/
class CrazyLogic : public BirdLogic
{
public:
	CrazyLogic(double radius, int points, const Position& dimensions) : birdStorage(radius, points, dimensions) {}
	virtual void advance()
	{
		// erratic turns eery half a second or so
		if (randomInt(0, 15) == 0)
		{
			v.addDy(randomFloat(-1.5, 1.5));
			v.addDx(randomFloat(-1.5, 1.5));
		}

		// inertia
		pt.add(v);

		// out of bounds checker
		if (isOutOfBounds())
		{
			kill();
			points *= -1; // points go negative when it is missed!
		}
	}
};

/*********************************************
 * SINKER
 * A sinker bird: honors gravity
 *********************************************/
class SinkerLogic : public BirdLogic
{
public:
	SinkerLogic(double radius, int points, const Position& dimensions) : birdStorage(radius, points, dimensions) {}
	virtual void advance()
	{
		// gravity
		v.addDy(-0.07);

		// inertia
		pt.add(v);

		// out of bounds checker
		if (isOutOfBounds())
		{
			kill();
			points *= -1; // points go negative when it is missed!
		}
	}
};