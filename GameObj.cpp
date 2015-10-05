#pragma once
#include "GameObj.h"
#include  <iostream>


bool GameObj::testHit(int x, int y, GameObj * obj)
{
	if (x >= obj->getX() && x <= obj->getX() + obj->getSprite()->getImage(0)->getWidth())
		if (y >= obj->getY() && y <= obj->getY() + obj->getSprite()->getImage(0)->getHeight())
			return true;
	return false;
}

bool GameObj::testHit(GameObj * obj)
{
	bool p1 = testHit(this->posX, this->posY, obj);
	bool p2 = testHit(this->posX,
						this->posY + this->getSprite()->getImage(0)->getHeight(), obj);
	bool p3 = testHit(this->posX + this->getSprite()->getImage(0)->getWidth(),
						this->posY + getSprite()->getImage(0)->getHeight(), obj);
	bool p4 = testHit(this->posX + this->getSprite()->getImage(0)->getWidth(),
						this->posY, obj);

	return p1 || p2 || p3 || p4;
		// NAO TESTA PIXEL :v
}

int GameObj::getHp()
{
	return hp;
}

void GameObj::shoot(int x, int y)
{
}

void GameObj::hit()
{
	if (hp > 0) {
		hp--;
		//frame = 12;
	}
	
	if(hp <= 0)
		destroy();
}

void GameObj::destroy() {
	active = false;
	if (destroyState < 5) {
		//frame = 10;
		destroyState++;
	}
	else if (destroyState < 10) {
		//frame = 11;
	}
	else {
		active = false;
	}
}

void GameObj::idle() {
	if (frame != 0)
		frame = 0;
	else
		frame = 1;
}

void GameObj::left() {
	if (posX > 5) {
		posX = posX - 5;
		if (frame != 6 || frame != 7)
			frame = 6;
		else
			frame = 7;
	}
}

void GameObj::right()
{
	if (posX < 500 - 5 - this->getSprite()->getImage(frame)->getWidth()) {
		posX = posX + 5;
		//std::cout << frame;
		if (frame != 8 || frame != 9)
			frame = 8;
		else
			frame = 9;
		//std::cout << frame << endl;
	}
}


void GameObj::up() {
	if (posY + this->getSprite()->getImage(frame)->getHeight() + 5 < 500) {
		posY = posY + 5;
		if (frame != 2)
			frame = 2;
		else
			frame = 3;
	}
}

void GameObj::down() {
	if (posY > 5) {
		posY = posY - 5;
		//std::cout << frame;

		if (frame != 4)
			frame = 4;
		else
			frame = 5;

		//std::cout << frame << endl;
	}
}

void GameObj::setHp(int hp)
{
	this->hp = hp;
}




int GameObj::getX() { return posX; }
int GameObj::getY() { return posY; }

void GameObj::setPos(int x, int y) {
	posX = x;
	posY = y;
}

Sprite * GameObj::getSprite() { return sprites; }

boolean GameObj::isActive() { return active; }

void GameObj::setActive(boolean b) { active = b; }



void GameObj::setFrame(int pos) { frame = pos; }

int GameObj::getPos() { return frame; }



GameObj::GameObj(int posX, int posY, Sprite * sprites) {
	hp = 10;
	destroyState = 0;
	active = true;
	this->posX = posX;
	this->posY = posY;
	this->sprites = sprites;
}

GameObj::~GameObj(void) {}