#include <windows.h>	
#include <GL\GL.h>
#include <GL\GLU.h>
#include <GL\glut.h>

#include "Enemy.h"
#include "FX.h"
#include "GameObj.h"
#include "Image.h"
#include "ImageReader.h"
#include "Player.h"
#include "Sprite.h"

#include <fstream>
#include <iostream>		//nothing to do with gl, but to write things on the console.	
#include <regex>
#include <string>
#include <time.h>		//for randoms
#include <vector>



enum GAME_STATE {
	MENU,
	GO,
	PAUSE,
	GAME_OVER
};
//0 menu, 1 go, 2 pause, 3 gameover.

//========================================
//METHODS SIGNATURES:		
//========================================
using namespace std;

void init();
int main(int argc, char * argv[]);

void ChangeSize(int w, int h);
void RenderScene();
void plotImage(Image *overImage);
void plotAll();
void plotLayer(Layer *overlayer);

void keyboard(unsigned char key, int x, int y);		//call GameObj move methods
void SpecialInput(int key, int x, int y);
void mouse(int button, int state, int x, int y);	//call GameObj shoot methods (sfx) and main events.	
void bgEvent(int a);
void write(string msg, int x, int y);
void write(string msg, int x, int y, void* font);


//========================================
//GLOBAL VARIABLES:	
//========================================

int width = 500;
int height = 500;
int GameState = GAME_STATE::MENU;

ImageReader* imageReader;
vector<GameObj*> sceneObjects;
vector<Layer*> sceneLayers;

Sprite * shipup;
Sprite * shipdown;
Sprite * effects;
Player * player;

Image *viewportStatic;
FX * fx;


/*
TODO LIST:
-	read all right imgs
-	main menu (state0) -> ifstate = 0 add coisa no plot all pra aparecer nome do game e etc ; mouse at state 0 and keyboard
-	update sigmature list declaration up^
-	do  fx
-	bg moving event
-	bg sidemove event on keyboard
*/


//========================================
//METHODS GAME LOGIC:	
//========================================


//menu
void mainMenu() {
	//TODO PRESS S TO START, Q TO QUIT, P TO PAUSE, H FOR HINTS - ONLY IN GAME! - (ADD KEY THAT CHANGE GLOBAL STATS TO DISPLAY TEXT AT PLOT [LIKE, DO NOT SHOT YOURSELF!])
}


void writeCommands() {
	write("Commands:", 20, 100);
	write("Q: quit", 25, 90);
	write("D: show 1 at screen", 25, 80);
	write("F: show 2 at screen", 25, 70);
	write("S: stop all visualizations", 25, 60);
	write("R: random image1 100x100", 25, 50);
	write("T: set random size image1", 25, 40);
	write("E: random image2 100x100", 25, 30);
	write("Y: set random size image2", 25, 20);
	write("Mouse click: move image2", 25, 10);
}




//========================================
//METHODS IMPLEMENTATION:	
//========================================


//----------------------------------------
//Load and draw images.
//----------------------------------------

//TODO 

Sprite * EnemySprite;

void loadObjects() {

	imageReader = new ImageReader();

	vector<Image*> toLoad;
	toLoad.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\Idle1.ptm"));
	toLoad.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\Idle2.ptm"));
	toLoad.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\speedUp1.ptm"));
	toLoad.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\speedUp2.ptm"));
	toLoad.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\break1.ptm"));
	toLoad.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\break2.ptm"));
	toLoad.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\left1.ptm"));
	toLoad.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\left2.ptm"));
	toLoad.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\right1.ptm"));
	toLoad.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\right2.ptm"));
	toLoad.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\break1.ptm"));//mudar pra destruir
	toLoad.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\break2.ptm"));//mudar para destruir
	shipup = new Sprite(toLoad);


	viewportStatic = new Image(width, height);
	sceneLayers.push_back(new Layer(imageReader->loadImageFile("E:\\poopProject\\Sprites\\spaaace.ptm"), 0.001, 0.001));
	sceneLayers.push_back(new Layer(imageReader->loadImageFile("E:\\poopProject\\Sprites\\planet2.ptm"), 0.005, 0.005));
	sceneLayers.push_back(new Layer(imageReader->loadImageFile("E:\\poopProject\\Sprites\\planet1.ptm"), 0.002, 0.002));
	//sceneLayers.push_back(new Layer(imageReader->loadImageFile("E:\\poopProject\\Sprites\\METEOROS.ptm"), 0.04, 0.04));
	//sceneLayers.push_back(new Layer(imageReader->loadImageFile("E:\\poopProject\\Sprites\\METEOROS.ptm"), 0.02, 0.02));
	player = new Player(width / 2, 20, shipup);
	sceneObjects.push_back(player); //new Player=>   state = STATE::MOVING_RIGHT (teclado)... sceneObject[i].Update() { switch STATE } 

	//sceneObjects.push_back(new GameObj(width / 2, 20, shipup)); //new Enemy   behavior = BEHAVIOR::follow  sceneObject[i].Update() { switch behavior - faz tal coisa } 

	//fx = new FX( //criar nova sprite e criar nova image.)

	vector<Image*> toLoad2;
	toLoad2.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\Shipup.ptm"));
	toLoad2.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\Shipup.ptm"));
	toLoad2.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\Shipup.ptm"));
	toLoad2.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\Shipup.ptm"));
	fx = new FX(new Sprite(toLoad2));

	vector<Image*> toLoadEnemies;
	toLoadEnemies.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\Shipup.ptm"));
	EnemySprite = new Sprite(toLoadEnemies);

}


void write(string msg, int x, int y) {	//Chamada GLUT para escrita	
	const char * cstr = msg.c_str();
	for (int j = 0; j < msg.size(); j++) {
		glRasterPos2f(x + (j * 8), y);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, (cstr[j]));
	}
}

void write(string msg, int x, int y, void* font) {	//Chamada GLUT para escrita	
	const char * cstr = msg.c_str();
	for (int j = 0; j < msg.size(); j++) {
		glRasterPos2f(x + (j * 8), y);
		glutBitmapCharacter(font, (cstr[j]));
	}
}

void plotAll() {
	Image *temp;
	for (int i = 0; i < sceneLayers.size(); i++) {
		if (sceneLayers[i]->isActive())
		{

			//temp = imageReader->subImage(width, height, sceneLayers[i]->getImage(), sceneLayers[i]->getPosX(), sceneLayers[i]->getPosY());
			plotLayer(sceneLayers[i]);
		}

	}
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		if (sceneObjects[i]->isActive()) {
			Sprite * sprite01 = sceneObjects[i]->getSprite();
			Image * sprImage01 = sprite01->getImage(sceneObjects[i]->getPos());

			temp = imageReader->subImage(width, height, sprImage01, sceneObjects[i]->getX(), sceneObjects[i]->getY());

			plotImage(temp);


			delete temp;
		}
	}

	if (fx->isActivee()) {
		temp = imageReader->subImage(width, height, fx->getSprite()->getImage(fx->getFrame()), fx->getX(), fx->getY());
		plotImage(temp);
		delete temp;

		temp = imageReader->subImage(width, height, fx->getSprite()->getImage(fx->getPosCounter2()), sceneObjects[0]->getX(), sceneObjects[0]->getY());
		plotImage(temp);
		delete temp;

	}


	//if(gamestate==0)...
	//if(h pressed only state==1)...	
}


void plotImage(Image * overImage) {
	int rgbOver = 0;
	int blueOver = 0;
	int greenOver = 0;
	int redOver = 0;
	int alphaOver = 0;

	for (int x = 0; x < width && x < overImage->getWidth(); x++)
	{
		for (int y = 0; y < height && x < overImage->getHeight(); y++)
		{
			rgbOver = overImage->getRGB(x, y);
			blueOver = rgbOver & 255;
			greenOver = (rgbOver >> 8) & 255;
			redOver = (rgbOver >> 16) & 255;
			alphaOver = (rgbOver >> 24) & 255;
			if (alphaOver == 255) {
				viewportStatic->setRGB(x, y, rgbOver);
			}
			else if (alphaOver == 0) continue;		//TODO else calcular alpha

		}
	}
}



void plotLayer(Layer * overLayer) {
	int rgbOver = 0;
	int blueOver = 0;
	int greenOver = 0;
	int redOver = 0;
	int alphaOver = 0;
	int a = 0;

	if (overLayer->getCursorY() >= overLayer->getImage()->getHeight()) {
		overLayer->setCursorY(overLayer->getCursorY() - overLayer->getImage()->getHeight());
	}
	for (int x = 0; x < width && x < overLayer->getImage()->getWidth(); x++)
	{
		for (int y = 0; y < height && x < overLayer->getImage()->getHeight(); y++)
		{
			if (y + overLayer->getCursorY() < overLayer->getImage()->getHeight()) {
				rgbOver = overLayer->getImage()->getRGB(x, (y + overLayer->getCursorY()));
				blueOver = rgbOver & 255;
				greenOver = (rgbOver >> 8) & 255;
				redOver = (rgbOver >> 16) & 255;
				alphaOver = (rgbOver >> 24) & 255;
				if (alphaOver == 255) {
					viewportStatic->setRGB(x, y, rgbOver);
				}
				else if (alphaOver == 0) continue;
			}
			else {
				//if (a < overLayer->getImage()->getHeight()) {
				//	rgbOver = overLayer->getImage()->getRGB(x, a);
				//	a++;
				//}
				//else {
				//	a = 0;
				//	rgbOver = overLayer->getImage()->getRGB(x, a);
				//}
				a = y + overLayer->getCursorY() - overLayer->getImage()->getHeight();
				rgbOver = overLayer->getImage()->getRGB(x, a);

				blueOver = rgbOver & 255;
				greenOver = (rgbOver >> 8) & 255;
				redOver = (rgbOver >> 16) & 255;
				alphaOver = (rgbOver >> 24) & 255;
				if (alphaOver == 255) {
					viewportStatic->setRGB(x, y, rgbOver);
				}
				else if (alphaOver == 0) continue;
			}
		}

	}
}

void drawImage() {
	glRasterPos2i(0, 0);	//these 2 methods set the start position to draw...
	glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, viewportStatic->getPixels());
}


//-------
//MAIN
//-------

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	init();								//method to start all global variables
	glutMainLoop();						// inicio do pipe-line OpenGL
	return 0;
}


int FPS = 120;

void init() {
	loadObjects();						//start objects. To be changed on the future.

	glMatrixMode(GL_PROJECTION);		//change mode to control view
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glViewport(0, 0, width, height);


	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Poop Squad!");


	//call back functions	(events)	
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialInput);
	glutMouseFunc(mouse);

	glutTimerFunc(1000 / FPS, bgEvent, 10);

	glMatrixMode(GL_MODELVIEW);			//change back mode to objects views
}



//-------------
//EVENT METHODS
//-------------


int spawnTimer;
int wave;
int minTime;
int spawnedEnemies;
int timerCount;
int points;

void reset() {
	spawnTimer = 60;
	wave = 0;
	minTime = 30;
	spawnedEnemies = 0;
	timerCount = 0;
	points = 0;

	GameState = GAME_STATE::MENU;
	player->setPos(width / 2, 20);
	player->setHp(10);
	player->setActive(true);
	player->setState(STATE::IDLE);
	sceneObjects.clear();
	sceneObjects.push_back(player);
}

void bgEvent(int a) {
	srand(time(NULL));
	if (GameState == GAME_STATE::GO) {

		timerCount++;
		if (timerCount >= spawnTimer) {
			timerCount = 0;
			int actualMinTime = minTime*(5 - wave/2);
			spawnTimer = ((actualMinTime <= 0) ? 30 : actualMinTime) + rand() % (6 * 60 - wave * 15);
			if (spawnedEnemies == wave * 3) {
				wave++;
				spawnedEnemies = 0;
			}
			//GENERATING ENEMY
			int x = 5 + rand() % (viewportStatic->getWidth() - 60);
			int y = viewportStatic->getHeight();
			int speed = 1 + (wave / 3);

			//todo: AJEITAR SPRITES
			sceneObjects.push_back(new Enemy(x, y, EnemySprite, sceneObjects[0], speed, (wave / 2) + 1));
			spawnedEnemies++;
		}

		for each(Layer * layer in sceneLayers) {
			float cursorY = a * layer->getTaxaY();
			layer->setCursorY(layer->getCursorY() + cursorY);
			//cout << layer->getCursorY() << endl;
		}

		for each(GameObj * gameObj in sceneObjects) {
			if (gameObj->isActive())
				gameObj->update();
		}

		player->checkCollision(sceneObjects);

		if (sceneObjects[0]->getHp() <= 0) {
			GameState = GAME_STATE::GAME_OVER;
		}
	}


	//sceneLayers[0]->setCursorY(a / 100);
	glutPostRedisplay();
	//1000.0 / 60.0
	glutTimerFunc(1000 / FPS, bgEvent, 10);

}


//TODO DO METHOD CALL CHANGESTAT(), on it change to active objects and global variable, allowing control of the spaceship.
// at game logic up top^ (change gamestats)

void mouse(int button, int state, int x, int y) {

	int yyy = height - y;
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		if (GameState == GAME_STATE::GO) {

			player->setState(STATE::IDLE);
		}
	}else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//test output on console:


		//if(GameState == 1){
		//fx->shoot(x, yyy);

		int a = 5;



		for (int i = 1; i < sceneObjects.size(); i++) {
			if (sceneObjects[i]->isActive()) {
				if (x > sceneObjects[i]->getX() &&
					x <	(sceneObjects[i]->getX() + sceneObjects[i]->getSprite()->getImage(sceneObjects[i]->getPos())->getWidth())
				){
					if (yyy > sceneObjects[i]->getY() &&
						yyy <	(sceneObjects[i]->getY() + sceneObjects[i]->getSprite()->getImage(0)->getHeight())
					){
						sceneObjects[i]->hit();
						points += wave;
						if (!sceneObjects[i]->isActive()) {
							points += wave*10;
						}
					}
				}
			}
		}

		//}

	}

	glutPostRedisplay();	//recall display event
}



void SpecialInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		player->setState(STATE::MOVING_FRONT);
		break;
	case GLUT_KEY_DOWN:
		player->setState(STATE::MOVING_BACK);
		break;
	case GLUT_KEY_LEFT:
		player->setState(STATE::MOVING_LEFT);
		break;
	case GLUT_KEY_RIGHT:
		player->setState(STATE::MOVING_RIGHT);
		break;
	}

	glutPostRedisplay();
}




void keyboard(unsigned char key, int x, int y) {	//what happens on keyboard presses
	int w, h;
	switch (key) {

	case 'q':		//quit
		exit(0);
		break;
	case 'w':
		player->setState(STATE::MOVING_FRONT);
		//sceneObjects[0]->up(width,height);
		break;
	case 'a':
		player->setState(STATE::MOVING_LEFT);
		//sceneObjects[0]->left(width, height);
		break;
	case 's':
		player->setState(STATE::MOVING_BACK);
		//sceneObjects[0]->down(width, height);
		break;
	case 'd':
		player->setState(STATE::MOVING_RIGHT);
		//sceneObjects[0]->right(width, height);
		break;
	case 'p':
		if (GameState == GAME_STATE::GO) GameState = GAME_STATE::PAUSE;
		else if (GameState == GAME_STATE::PAUSE) GameState = GAME_STATE::GO;
		break;
	case ' ':
		GameState = (GameState != GAME_STATE::GAME_OVER) ? GAME_STATE::GO : GAME_STATE::GAME_OVER;
		if (GameState == GAME_STATE::GO) {
			player->setState(STATE::IDLE);
		}
		break;
	case 'r':
		reset();
		break;

	}

	glutPostRedisplay();
}


void writeGameState() {
	glColor3ub(255, 255, 255);
	string hpMessage = "HP: " + to_string(sceneObjects[0]->getHp());
	string waveMessage = "Wave: " + to_string(wave);
	string pointsMessage = "Points: " + to_string(points);


	write(hpMessage, 10, viewportStatic->getHeight() - 15);
	write(waveMessage, 10, viewportStatic->getHeight() - 30);
	write(pointsMessage, 10, viewportStatic->getHeight() - 45);

	if (GameState == GAME_STATE::GAME_OVER) {
		write("-  G a m e   O v e r  -", viewportStatic->getWidth() / 2 - 80, viewportStatic->getHeight() / 2, GLUT_BITMAP_HELVETICA_18);

	}
	else if (GameState == GAME_STATE::MENU) {
		write("-  P oo p  P r o j e c t  -", viewportStatic->getWidth() / 2 - 100, viewportStatic->getHeight() / 2, GLUT_BITMAP_HELVETICA_18);
		write("Press SPACE to start", viewportStatic->getWidth() / 2 - 70, viewportStatic->getHeight() / 2 - 20);
	}
	else if (GameState == GAME_STATE::PAUSE) {
		write("- P a u s e d  -", viewportStatic->getWidth() / 2 - 50, viewportStatic->getHeight() / 2, GLUT_BITMAP_HELVETICA_18);
	}
}

void writeObjectsHP() {
	for each(GameObj * obj in sceneObjects) {
		if (obj->isActive())
			write(to_string(obj->getHp()), obj->getX() + 40, obj->getY());
	}
}

void RenderScene(void) {							//scene render pipeline state
	glClear(GL_COLOR_BUFFER_BIT);
	//add here method calls that has begin end to draw stuff;	
	plotAll();
	drawImage();
	writeObjectsHP();
	writeGameState();

	glFlush();
}


void ChangeSize(int w, int h) {						//redimensioning window

	//prevent invalid size error.
	if (h == 0)
		h = 1;


	glMatrixMode(GL_PROJECTION);				//change mode to control view
	//glViewport(width, height, width + w, height + h);
	glViewport(0, 0, w, h);
	glLoadIdentity();


	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);					//change back mode to objects views
	glLoadIdentity();
}