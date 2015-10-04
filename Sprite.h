#pragma once
#include "Image.h"
#include <vector>
using namespace std;



class Sprite
{
private:
	vector<Image*> images;
	/*
	0: idle1, 1: idle2,
	2: movingFoward1, 3: movingFoward2,
	4: movingBack1, 5: movingBack2
	6: movingLeft1, 7: movingLeft2, 8: movingLeft3
	9: movingRight1, 10: movingRight2, 11: movingRight3
	12: destroy1, 13: destroy2
	*/

public:
	void insertImagePos(Image* image, int pos);
	void insertImageLast(Image* image);
	Image * getImage(int pos);
	
	Sprite(vector<Image*> v);
	~Sprite(void);
};

