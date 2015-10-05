#pragma once
#include "GameObj.h"
#include  <iostream>


void GameObj::shoot(int x, int y)
{
}

void GameObj::hit()
{
	if (hp > 10) {
		hp--;
		frame = 12;
	}
	else
		destroy();
}

void GameObj::destroy() {
	if (destroyState < 5) {
		frame = 10;
		destroyState++;
	}
	else if (destroyState < 10) {
		frame = 11;
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

void GameObj::left(int screenWidth, int screenHeight) {
	if (posX > 5) {
		posX = posX - 5;
		if (frame != 6 || frame != 7)
			frame = 6;
		else
			frame = 7;
	}
}

void GameObj::right(int screenWidth, int screenHeight)
{
	if (posX < screenWidth - 5 - this->getSprite()->getImage(frame)->getWidth()) {
		posX = posX + 5;
		std::cout << frame;
		if (frame != 8 || frame != 9)
			frame = 8;
		else
			frame = 9;
		std::cout << frame << endl;
	}
}


void GameObj::up(int screenWidth, int screenHeight) {
	if (posY + this->getSprite()->getImage(frame)->getHeight() + 5 < screenHeight) {
		posY = posY + 5;
		if (frame != 2)
			frame = 2;
		else
			frame = 3;
	}
}

void GameObj::down(int screenWidth, int screenHeight) {
	if (posY > 5) {
		posY = posY - 5;
		std::cout << frame;

		if (frame != 4)
			frame = 4;
		else
			frame = 5;

		std::cout << frame << endl;
	}
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

void GameObj::update()
{
}

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