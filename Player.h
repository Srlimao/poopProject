#pragma once
#include "GameObj.h"
enum STATE {
	IDLE,
	MOVING_FRONT,
	MOVING_FRONT_RIGHT,
	MOVING_RIGHT,
	MOVING_BACK_RIGHT,
	MOVING_BACK,
	MOVING_BACK_LEFT,
	MOVING_LEFT,
	MOVING_FRONT_LEFT
};

class Player :
	public GameObj
{
protected:
	int state;

public:
	//GameObj(int posX, int posY, Sprite * sprites);
	void setState(int state);
	void update();
	void checkCollision(vector<GameObj*> objects);

	Player(int posX, int posY, Sprite * sprites);
	~Player();
};



