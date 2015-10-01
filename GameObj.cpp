#include "GameObj.h"


void GameObj::shoot(int x, int y)
{
}

void GameObj::hit()								
{
	if (hp > 10) {
		hp--;
		imgPosCounter = 12;
	}
	else
		destroy();
}

void GameObj::destroy(){
	if (destroyState < 5) {
		imgPosCounter = 10;
		destroyState++;
	}
	else if(destroyState < 10) {
		imgPosCounter = 11;
	}
	else {
		active = false;
	}
}

void GameObj::idle(){
	if (imgPosCounter != 0)
		imgPosCounter = 0;
	else
		imgPosCounter = 1;
}

void GameObj::left(int screenWidth, int screenHeight){
	if (posX > 5) {
		posX = posX - 5;	
		if (imgPosCounter != 6 || imgPosCounter != 7)
			imgPosCounter = 6;
		else
			imgPosCounter = 7;
	}
}

void GameObj::right(int screenWidth, int screenHeight) {
	if (posX < screenWidth - 5 - this->getSprite()->getImage(imgPosCounter)->getWidth()) {
		posX = posX + 5;
		if (imgPosCounter = 8 || imgPosCounter != 9)
			imgPosCounter = 8;
		else
			imgPosCounter = 9;
	}
}


void GameObj::up(int screenWidth, int screenHeight) {
	if (posY > 5 + this->getSprite()->getImage(imgPosCounter)->getHeight()) {
		posY = posY - 5;
		if (imgPosCounter != 2)
			imgPosCounter = 2;
		else
			imgPosCounter = 3;
	}
}

void GameObj::down(int screenWidth, int screenHeight) {
	if (posY < screenHeight){
		posY = posY + 5;
		if (imgPosCounter != 4)
			imgPosCounter = 4;
		else
			imgPosCounter = 5;
	}
}




int GameObj::getX() { return posX; }
int GameObj::getY() { return posY; }

void GameObj::setPos(int x, int y) {
	posX = x;
	posY = y;
}

Sprite * GameObj::getSprite() { return sprites; }

Sprite * GameObj::getSpriteFX() { return spritesFX; }

boolean GameObj::isActive() { return active; }

void GameObj::setActive(boolean b) { active = b; }

void GameObj::settingPosCounter(int pos) { imgPosCounter = pos; }

int GameObj::getPos() { return imgPosCounter;  }



GameObj::GameObj(int posX, int posY, Sprite * sprites, Sprite * spritesFX) {
	hp = 10;
	destroyState = 0;
	active = true;
	this->posX = posX;
	this->posY = posY;
	this->sprites = sprites;
	this->spritesFX = spritesFX;
}

GameObj::~GameObj(void){}