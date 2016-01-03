#include "game.h"

int main(int argc, char** argv) {

	// Create game
	game igelGame(600, 800);

	// Gl window creation
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(game::window_width, game::window_heigth);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Igel");

	// Load textures
	game::loadTextures();

	// Environment creation
	initialize();

	// GL function registration

	glutDisplayFunc(display);

	glutTimerFunc(50, redrawTimer, 0);
	glutKeyboardFunc(movement);

	// Main loop
	glutMainLoop();
	system("Pause");
	return 0;
}