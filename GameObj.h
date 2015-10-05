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


	virtual void update() = 0;
	bool testHit(int x, int y, GameObj * obj);
	bool testHit(GameObj * obj);
	
	int getHp();

	//moves
	void shoot(int x, int y);						//TODO: check ammo, reload.	
	void hit();										//TODO: flash to red color at main!					
	void destroy();

	void idle();
	void left();
	void right();
	void up(); 
	void down();
	void setHp(int hp);

	GameObj(int posX, int posY, Sprite * sprites);
	~GameObj(void);
};