#include "Player.h"



void Player::setState(int state)
{
	this->state = state;
}

void Player::update()
{
	switch (state) {
	case STATE::IDLE: idle();  break;
	case STATE::MOVING_FRONT: up(); break;
	case STATE::MOVING_BACK: down(); break;
	case STATE::MOVING_LEFT: left(); break;
	case STATE::MOVING_RIGHT: right(); break;
	}

}

void Player::checkCollision(vector<GameObj*> objects)
{
	for each(GameObj * object in objects) {
		if (object == this) {
			continue;
		}else if (object->isActive()) {
			if (testHit(object)) {
				this->hit();
				this->hit();
				object->destroy();
			}
		}
	}
}

Player::Player(int posX, int posY, Sprite * sprites) : GameObj(posX, posY, sprites)
{

}


Player::~Player()
{
}
