#pragma once
#include "Layer.h"


using namespace std;



Layer::Layer(Image* image)
{
	this->image = image;
	this->status = true;
	this->taxaX = 1;
	this->taxaY = 1;
	this->posX = 0;
	this->posY = 0;
}

Layer::~Layer(void)
{
}

bool Layer::isActive()
{
	return status;
}

Image * Layer::getImage()
{
	return image;
}

int Layer::getPosX()
{
	return posY;
}

int Layer::getPosY()
{
	return posY;
}

void Layer::setPosX(int posX)
{
	this->posX = posX;
}

void Layer::setPosY(int posY)
{
	this->posY = posY;
}

int Layer::getTaxaX()
{
	return taxaX;
}

int Layer::getTaxaY()
{
	return taxaY;
}

int Layer::getCursorY()
{
	return cursorY;
}
