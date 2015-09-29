#pragma once
#include "Image.h"
#include <vector>
using namespace std;



class Sprite
{
private:
	vector<Image*> images;
	//0: idle1, 1: idle2, 2: movingFoward1, 3: movingFoward2, 4: movingBack1, 5: movingBack2
	//6: movingLeft1, 7: movingLeft2, 8: movingRight1, 9: movingRight2. 10: destroy1, 11: destroy2

public:
	//void setInsertImage(Image* image, int pos);		//setImage? insertImage? setFrame?
	Image * getImage(int pos);
	
	Sprite();
	~Sprite(void);
};

