#include "Player.h"



void Player::update()
{
	switch (state) {
	case STATE::IDLE: break;
	case STATE::MOVING_FRONT:
		//TODO: a implementacao que está no teclado
		break;
	}
}

Player::Player(int posX, int posY, Sprite * sprites) : GameObj(posX, posY, sprites)
{

}


Player::~Player()
{
}
