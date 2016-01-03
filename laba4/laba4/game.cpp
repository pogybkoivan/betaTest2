#include "game.h"

/////////////////////////////////
// 'Game' class implementation //
/////////////////////////////////

game::game(int wheigth, int wWidth)
{
	window_heigth = wheigth;
	window_width = wWidth;
}
game::~game() {}

vector<game::Apple> game::apples;	// Stores entities that represent apples

game::Igel game::igel;				// Stores entity that represents igel
bool game::igelPosChanged = false;	// true if igel moved since last refresh, otherwise false
bool game::igelGoesLeft = true;		// Represents igel direction
int game::window_heigth = 100;
int game::window_width = 100;

GLuint game::textures[5];			// Array used to store textures

void game::loadTextures() {

	// Igel texture when it walks right
	textures[0] = SOIL_load_OGL_texture(
		"IgelToRight.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_INVERT_Y
		);

	// Igel texture when it walks left
	textures[1] = SOIL_load_OGL_texture(
		"IgelToLeft.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_INVERT_Y
		);

	// Red apple texture
	textures[2] = SOIL_load_OGL_texture(
		"RedApple.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_INVERT_Y
		);

	// Grin apple texture
	textures[3] = SOIL_load_OGL_texture(
		"GrinApple.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_INVERT_Y
		);

	// Grass texture
	textures[4] = SOIL_load_OGL_texture(
		"Grass.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_INVERT_Y
		);
}

//////////////////////////////////////
// 'entity' subclass implementation //
//////////////////////////////////////

game::entity::entity() {
	x = 15;
	y = 15;
	z = 15;
}
game::entity::entity(int _x, int _y, int _z) {
	x = _x;
	y = _y;
	z = _z;
}
game::entity::~entity() {};

float game::entity::distanceTo(entity &another) {
	return sqrt(pow(x - another.x, 2.0) + pow(y - another.y, 2.0) + pow(z - another.z, 2.0));
}

///////////////////////////////////////
// 'Apple' and 'Igel' implementation //
///////////////////////////////////////

void game::Apple::drawApple() {
	// Enable texture and transparency
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Switch to corresponding texture
	glBindTexture(GL_TEXTURE_2D, game::textures[color]);

	// Draw apple
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(x - 30, y - 30, 0);
	glTexCoord2f(0, 1); glVertex3f(x - 30, y + 30, 0);
	glTexCoord2f(1, 1); glVertex3f(x + 30, y + 30, 0);
	glTexCoord2f(1, 0); glVertex3f(x + 30, y - 30, 0);
	glEnd();

	// Disable modes
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}
void game::Igel::drawIgel() {
	// Enable texture and transparency
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Switch to corresponding texture
	glBindTexture(GL_TEXTURE_2D, game::textures[(int)game::igelGoesLeft]);

	// Draw igel
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(x - 45, y - 45, 0);
	glTexCoord2f(0, 1); glVertex3f(x - 45, y + 45, 0);
	glTexCoord2f(1, 1); glVertex3f(x + 45, y + 45, 0);
	glTexCoord2f(1, 0); glVertex3f(x + 45, y - 45, 0);
	glEnd();

	// Disable modes
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

}

/////////////////////////////////////
// Global functions implementation //
/////////////////////////////////////

void drawPlane() {
	glPushMatrix();

	// Enable texture and transparency
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Switch to corresponding texture
	glBindTexture(GL_TEXTURE_2D, game::textures[4]);

	// Draw plane
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-game::window_width / 2, -game::window_heigth / 2, 0);
	glTexCoord2f(0, 1); glVertex3f(-game::window_width / 2, game::window_heigth / 2, 0);
	glTexCoord2f(1, 1); glVertex3f(game::window_width / 2, game::window_heigth / 2, 0);
	glTexCoord2f(1, 0); glVertex3f(game::window_width / 2, -game::window_heigth / 2, 0);
	glEnd();

	// Disable modes
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
void drawApples() {

	glPushMatrix();

	for (auto i = game::apples.begin(); i != game::apples.end(); i++) {
		i->drawApple();
	}

	glPopMatrix();
}
void drawIgel() {
	glPushMatrix();

	game::igel.drawIgel();

	glPopMatrix();
}

// Environment creation
void initialize()
{
	// Background fill color
	glClearColor(0, 0, 0, 1.0);

	// Create grid for objects
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-game::window_width / 2, game::window_width / 2, -game::window_heigth / 2, game::window_heigth / 2, -500, 500);

	// Plant apples
	plantApples();
}

// Handles igel movement
void movement(unsigned char key, int x, int y)
{

	switch (key) {
	case 'd':
		if (game::igel.x < game::window_width / 2) game::igel.x += 10;
		game::igelGoesLeft = false;
		break;

	case 'a':
		if (game::igel.x > -game::window_width / 2) game::igel.x -= 10;
		game::igelGoesLeft = true;
		break;

	case 's':
		if (game::igel.y > -game::window_heigth / 2) game::igel.y -= 10;
		game::igelGoesLeft = true;
		break;

	case 'w':
		if (game::igel.y < game::window_heigth / 2) game::igel.y += 10;
		game::igelGoesLeft = false;
		break;

	default:
		return;
	}

	// Tell game that igel moved
	game::igelPosChanged = true;
}

// Timer function that checks for apples being eaten
void redrawTimer(int)
{
	if (game::igelPosChanged)
	{
		checkApples();
		glutPostRedisplay();
	}
	glutTimerFunc(50, redrawTimer, 0);
}

// Main display function
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawPlane();
	drawApples();
	drawIgel();

	glutSwapBuffers();
}

// Apple handling
void plantApples() {
	bool flag = true;

	for (int i = 0; game::apples.size() < 15; i++) {
		srand(i * time(NULL));
		int x = ((game::window_width - 60) / 20) *(rand() % 20) - game::window_width / 2 + 60;
		int y = ((game::window_heigth - 60) / 20) * (rand() % 20) - game::window_heigth / 2 + 60;
		game::Apple new_apple(x, y, 15, rand() % 2 + 2);

		for (auto j = game::apples.begin(); j != game::apples.end(); j++) {
			if (j->distanceTo(new_apple) < 60) {
				flag = false;
				break;
			}
		}
		if (flag) {
			game::apples.push_back(new_apple);
		}
		else flag = true;
	}

}
void checkApples()
{
	for (auto i = game::apples.begin(); i != game::apples.end();) {
		if (i->distanceTo(game::igel) < 17) {
			game::apples.erase(i);
			break;
		}
		else ++i;
	}
	game::igelPosChanged = false;
	if (game::apples.empty())
	{
		plantApples();
		drawApples();
	}
}