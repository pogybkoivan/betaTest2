#include <time.h>
#include <vector>
#include <glut.h>
#include <SOIL.h>
using namespace std;

// Environment creation
void initialize();

// Objects drawing functions
void drawPlane();
void drawApples();
void drawIgel();

// Apples handling
void plantApples();
void checkApples();

// Main display function
void display();

// Timer
void redrawTimer(int);

// Igel controls
void movement(unsigned char key, int x, int y);


// Main game class
class game {
public:
	// 'entity' class represents entity in grid
	class entity {
	public:
		// Point coordinates
		int x, y, z;

		// Constructors
		entity();
		entity(int _x, int _y, int _z);
		~entity();

		// Distance function
		float distanceTo(entity &another);
	};

	class Apple : public entity {
		int color;
	public:
		Apple(int _x, int _y, int _z, int _color = 2) : entity(_x, _y, _z) {
			color = _color;
		};
		void drawApple();
	};
	class Igel : public entity {
	public:
		void drawIgel();
	};

	// Game window properties
	static int window_heigth;
	static int window_width;

	static GLuint textures[5];
	static void loadTextures();

	static vector<Apple> apples;

	static Igel igel;
	static bool igelPosChanged;
	static bool igelGoesLeft;

	// Constructor used to initialize OpenGL environment
	game(int wHeight, int wWidth);
	~game();
};