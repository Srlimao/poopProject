#include <windows.h>	
#include <GL\GL.h>
#include <GL\GLU.h>
#include <GL\glut.h>

#include <iostream>	//nothing to do with gl, but to write things on the console.	
#include <time.h>	//for randoms
#include "Image.h"
#include "Sprite.h"
#include "GameObj.h"
#include <vector>
#include <string>
#include "ImageReader.h"
#include <fstream>
#include <regex>



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

void keyboard(unsigned char key, int x, int y);		//call GameObj move methods
void mouse(int button, int state, int x, int y);	//call GameObj shoot methods (sfx) and main events.	

void write(string msg, int x, int y);


//========================================
//GLOBAL VARIABLES:	
//========================================

int width = 500;
int height = 500;
int GameState = 0;		//0 menu, 1 go, 2 pause, 3 gameover.

ImageReader* imageReader;
vector<GameObj*> sceneObjects;	
vector<Layer*> sceneLayers;

Sprite * shipup;
Sprite * shipdown;
Sprite * effects;

Image *viewportStatic;
//FX * fx;


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
	write("Mouse click: move image2" , 25, 10);
}




//========================================
//METHODS IMPLEMENTATION:	
//========================================


//----------------------------------------
//Load and draw images.
//----------------------------------------

//TODO 
void loadObjects() {

	imageReader = new ImageReader();

	vector<Image*> toLoad;
	toLoad.push_back(imageReader->loadImageFile("E:\\poopProject\\Sprites\\Shipup.ptm"));
	shipup = new Sprite(toLoad);


	viewportStatic = new Image(width, height);
	sceneLayers.push_back(new Layer(imageReader->loadImageFile("E:\\poopProject\\Sprites\\SpaceBG.ptm")));
	sceneObjects.push_back(new GameObj(0, 0, shipup));


	//INNERS
	//	criar objects, criar sprites, criar imagens
	//	criar layers, criar imagens

	//fx = new FX( //criar nova sprite e criar nova image.)
}
	

void write(string msg, int x, int y) {	//Chamada GLUT para escrita	
	const char * cstr = msg.c_str();
	for (int j = 0; j < msg.size(); j++){
		glRasterPos2f(x+(j*8), y);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, (cstr[j]));
	}
}


void plotAll(){
	Image *temp;
	for (int i = 0; i < sceneLayers.size(); i++){
		if (sceneLayers[i]->isActive())
		{
			temp = imageReader->subImage(width, height, sceneLayers[i]->getImage(), sceneLayers[i]->getPosX(), sceneLayers[i]->getPosY());
			plotImage(temp);
		}
		
	}
	for (int i = 0; i < sceneObjects.size(); i++)
	{
		if (sceneObjects[i]->isActive()){
			int objY = sceneObjects[i]->getY();
			int objX = sceneObjects[i]->getX();
			Sprite * sprite01 = sceneObjects[i]->getSprite();
			Image * sprImage01 = sprite01->getImage(sceneObjects[i]->getPos());

			temp = imageReader->subImage(width, height, sprImage01, objX, objY);

			plotImage(temp);

		}
	}

	//if(gamestate==0)...
	//if(h pressed only state==1)...	
}


void plotImage(Image * overImage){
	int rgbOver = 0;
	int blueOver = 0;
	int greenOver = 0;
	int redOver = 0;
	int alphaOver = 0;

	for (int x = 0; x < width && x<overImage->getWidth(); x++)
	{
		for (int y = 0; y < height && x<overImage->getHeight(); y++)
		{
			rgbOver = overImage->getRGB(x, y);
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


void plotLayer(Layer * overLayer) {
	int rgbOver = 0;
	int blueOver = 0;
	int greenOver = 0;
	int redOver = 0;
	int alphaOver = 0;
	int a = 0;

	for (int x = 0; x < sizeof(width); x++)
	{
		for (int y = 0; y < sizeof(height); y++)
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
				rgbOver = overLayer->getImage()->getRGB(x, a);
				a++;
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
	glutMouseFunc(mouse);

	glMatrixMode(GL_MODELVIEW);			//change back mode to objects views
}

//-------------
//EVENT METHODS
//-------------


//DO EVENT BACKGROUND GOING HERE. a ideia eh com timer sempre mover o background em velocidade definida da layer. (apenas uma dimensao, a outra eh no movimento do char),
//movimento infinito! how?


//TODO DO METHOD CALL CHANGESTAT(), on it change to active objects and global variable, allowing control of the spaceship.
// at game logic up top^ (change gamestats)

void mouse(int button, int state, int x, int y) {	//what happens on mouse clicks

	int yyy = height - y;
	
	//a click :		
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		//test output on console:
		cout << "Mouse Click:" << endl;
		cout << "\tPosition: " << x << " - " << y << endl;
		
		/*
		if(GameState == 1){
			//fx.shoot(x, y);
			for (int i = 0; i < sceneObjects.size(); i++)
				if(x > sceneObjects[i]->getX() && x < sceneObjects[i]->getX() + sceneObjects[i]->getSprite()->getImage((sceneObjects[i]->getPos())).getWidth())
					sceneObjects[i].hit();
		}
		*/
	}

	glutPostRedisplay();	//recall display event
}


void keyboard(unsigned char key, int x, int y) {	//what happens on keyboard presses
	int w, h;

	switch (key){

	case 'q':		//quit
		exit(0);
		break;
		/*
	case 's':		//stop drawing
		state = 0;
		toDraw[0]->setVisibility(false);
		toDraw[1]->setVisibility(false);
		cout << state << endl;
		break;

	case 'd':		//set state to draw 
		toDraw[0]->setVisibility(true);
		state = 1;
		cout << state << endl;
		break;
	case 'f':
		toDraw[1]->setVisibility(true);
		state = 2;
		cout << state << endl;
		break;
	case 'r':		//create random image for image1 100x100
		toDraw[0]->setImage(randomImage(100, 100, toDraw[0]->getImage()));
		break;
	case 'e':		//create random image for image1 100x100
		toDraw[1]->setImage(randomImage(100, 100, toDraw[1]->getImage()));	//FIX GET POS
		break;
	case 't':		//create random image on pos1 passing sizes
		cout << "Enter a Width value: ";
		cin >> w;
		cout << endl << "Enter a Height value: ";
		cin >> h;
		toDraw[0]->setImage(randomImage(w, h, toDraw[0]->getImage()));	//FIX GET POS	
		break;
	case 'y':		//create random image on pos2 passing sizes
		cout << "Enter a Width value: ";
		cin >> w;
		cout << endl << "Enter a Height value: ";
		cin >> h;
		toDraw[1]->setImage(randomImage(w, h, toDraw[1]->getImage()));	//FIX GET POS	
		break;
		//discover how are the directions.	
	case 'j':
		toDraw[0]->left();
		break;
	case 'l':
		toDraw[0]->right();
		break;
	case 'i':
		toDraw[0]->up();
		break;
	case 'k':
		toDraw[0]->down();
		break;
	*/
	}
	
	glutPostRedisplay();
}


void RenderScene(void) {							//scene render pipeline state
	glClear(GL_COLOR_BUFFER_BIT);
	//add here method calls that has begin end to draw stuff;	
	plotAll();
	drawImage();

	glFlush();
}


void ChangeSize(int w, int h) {						//redimensioning window
	/*
	//prevent invalid size error.
	if (h == 0)
		h = 1;

	width = w;
	height = h;

	glMatrixMode(GL_PROJECTION);				//change mode to control view
	//glViewport(width, height, width + w, height + h);
	glViewport(0, 0, w, h);
	glLoadIdentity();


	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);					//change back mode to objects views
	glLoadIdentity();
	*/
}	















/*	-------------------------------------------------------------------------------------------------------------


state machine! ,the drawings can be here or at another methods,
only flush and the sub method calls that contain the begin should be here.

glColor3f(0.0, 0.0, 1.0);		//i whould make to 0 to 255; f 0.0 to 1.0
glBegin()						//Draw a shape, types : GL_TRIANGLES, GL_FAN, GL_LINE_LOOP, GL_QUADS, GL_POLYGON, STRIPS...
glVertex3f(  ,  ,  );			//f , i or v  for types
glVertex3f(  ,  ,  );
glVertex3f(  ,  ,  );
glEnd()

other possible other than color:  glNormal*(), glMaterial*(), glLight*()

*/


/*
Drawing a circle

#define PI 3.1415926535898
GLfloat circle_points = 100.0f;
GLfloat angle, raioX = 1.0f, raioY = 1.0f;			//size
glBegin(GL_LINE_LOOP);
for (int i = 0; i < circle_points; i++) {
angle = 2 * PI*i / circle_points;
glVertex2f(cos(angle)*raioX,
sin(angle)*raioY);
}
glEnd();
*/












/*




glPolygonMode(<lado>, <modo>)
!<lado>
• GL_FRONT_AND_BACK
• GL_FRONT
• GL_BACK
!<modo>
• GL_POINT
• GL_LINE
• GL_FILL






glEnable(GL_LIGHTING);



glFrustum(left, right, bottom, top, near, far)
!glOrtho(left, right, bottom, top, near, far)
!gluPerspective(fovy, aspect, zNear, zFar)
!gluOrtho2D(left, right, bottom, top)
!gluLookAt(eyex, eyey, eyez, centerx,
	centery, centerz, upx, upy, upz)
	Coordenadas de Tela
	!glViewport(x, y, width, height)




	• glTranslate {
	fd
}(x, y, z)
• glRotate {
		fd) (angle, x, y, z)
			• glScale{ fd }(x, y, z)


*/