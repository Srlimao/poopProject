#pragma once
#include "GameObj.h"
enum BEHAVIOR {
	STATIONARY,
	MOVE_FORWARD,
	FOLLOW_PLAYER,
	FOLLOW_PLAYER_CIRCULAR
};

class Enemy :
	public GameObj
{
protected:
	float speed;
	float param1, param2, param3;
	int behavior;
	GameObj * target;


public:
	void update();

	Enemy(int posX, int posY, Sprite * sprites);
	~Enemy();
};

