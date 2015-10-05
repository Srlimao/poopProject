#include "FX.h"

void FX::shoot(int x, int y)
{
	this->posX = x;
	this->posY = y;
	this->isActive = true;
	frame = 0;
	imgPosCounter2 = 2;
}

void FX::fade()
{
	frame = 1;
	imgPosCounter2 = 3;
}

Sprite * FX::getSprite()
{
	return sprites;
}


bool FX::isActivee()
{
	return isActive;
}

int FX::getFrame()
{
	return frame;
}

int FX::getPosCounter2()
{
	return imgPosCounter2;
}

int FX::getY()
{
	return posY;
}

int FX::getX()
{
	return posX;
}


FX::FX(Sprite * sprites)
{
	this->sprites = sprites;
	this->isActive = false;
}

FX::~FX(void)
{
}
