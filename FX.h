#pragma once
#include "Sprite.h"

class FX {
private:
	Sprite * sprites;
	int posX;
	int posY;
	bool isActive;
	int imgPosCounter;
	int imgPosCounter2;	//for own spaceship effects
public:
	void FX::shoot(int x, int y);
	Sprite* getSprite();
	void fade();

	bool isActivee();
	int getPosCounter();
	int getPosCounter2();
	int getY();
	int getX();

	FX(Sprite * sprites);
	~FX(void);
};