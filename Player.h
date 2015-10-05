#pragma once
#include "GameObj.h"
enum STATE {
	IDLE,
	MOVING_FRONT,
	MOVING_FRONT_RIGHT,
	MOVING_RIGHT,
	MOVING_BOTTOM_RIGHT,
	MOVING_BOTTOM,
	MOVING_BOTTOM_LEFT,
	MOVING_LEFT,
	MOVING_TOP_LEFT
};

class Player :
	public GameObj
{
protected:
	int state;

public:
	//GameObj(int posX, int posY, Sprite * sprites);
	void update();

	Player(int posX, int posY, Sprite * sprites);
	~Player();
};



