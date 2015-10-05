#include "Enemy.h"



void Enemy::update()
{
	switch (behavior) {
	case BEHAVIOR::STATIONARY: break;
	case BEHAVIOR::MOVE_FORWARD:
		if (posY <= 0) {
			target->hit();
			active = false;
		}
		else {
			posY -= speed;
		}
		break;
	case BEHAVIOR::FOLLOW_PLAYER:
		float dx = target->getX() - posX;
		float dy = target->getY() - posY;

		float ddx = 1; //APLICAR TRIGONOMETRIA
		float ddy = 1;// APLICAR TRIGONOMETRIA

		posX += ddx*speed;
		posY += ddy*speed;
		break;
	}

	
}

Enemy::Enemy(int posX, int posY, Sprite * sprites, GameObj * target) : GameObj(posX, posY, sprites)
{
	this->target = target;
	this->speed = 5;
	this->behavior = BEHAVIOR::MOVE_FORWARD;
}
Enemy::Enemy(int posX, int posY, Sprite * sprites, GameObj * target, int speed ) : GameObj(posX, posY, sprites)
{
	this->target = target;
	this->speed = speed;
	behavior = BEHAVIOR::MOVE_FORWARD;
}

Enemy::Enemy(int posX, int posY, Sprite * sprites, GameObj * target, int speed, int hp) : GameObj(posX, posY, sprites)
{
	this->target = target;
	this->speed = speed;
	this->hp = hp;
	behavior = BEHAVIOR::MOVE_FORWARD;
}

Enemy::~Enemy()
{
}
