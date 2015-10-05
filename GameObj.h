#pragma once
#include "Sprite.h"

class GameObj {
protected:
	Sprite * sprites;
	int frame;
	int posX;
	int posY;
	boolean active;

	int destroyState;				//counter for sprite ongoing at destroy changes
	int hp;							//10 hp per spaceship
public:
	//positions
	int getX();
	int getY();
	void setPos(int x, int y);
	int getPos();
	void setFrame(int pos);
	Sprite* getSprite();
	boolean isActive();
	void setActive(boolean b);


	void update();

	//moves
	void shoot(int x, int y);						//TODO: check ammo, reload.	
	void hit();										//TODO: flash to red color at main!					
	void destroy();

	void idle();
	void left(int screenWidth, int screenHeight);
	void right(int screenWidth, int screenHeight);
	void up(int screenWidth, int screenHeight);
	void down(int screenWidth, int screenHeight);

	GameObj(int posX, int posY, Sprite * sprites);
	~GameObj(void);
};