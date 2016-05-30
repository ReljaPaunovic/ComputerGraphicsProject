/*
* RedSquare.c
*
*   This program draws a red rectangle on a blue background.
*
*/

#include <GL/glut.h>

void display(void) {
	/* clear window */
	glClear(GL_COLOR_BUFFER_BIT);

	/* draw unit square polygon */
	glBegin(GL_POLYGON);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	// Bla bla
	/* flush GL buffers */
	glFlush();
}

/*//take keyboard input into account
void keyboard(unsigned char key, int x, int y)
{
	//printf("key %d pressed at %d,%d\n", key, x, y);
	//fflush(stdout);

	if ((key >= '1') && (key <= '9'))
	{
		//DisplayMode = (DisplayModeType)(key - '0');
		return;
	}

	switch (key)
	{
	case 27:     // touche ESC
		exit(0);
	case 'L':
		//turn lighting on
		glEnable(GL_LIGHTING);
		break;
	case 'l':
		//turn lighting off
		glDisable(GL_LIGHTING);
		break;
	case 'w':
		angle += 1;
		break;
	case 's':
		angle -= 1;
		break;
	case 'e':
		angle1 += 1;
		break;
	case 'd':
		angle1 -= 1;
		break;
	}
}*/

void init() {
	/* set clear color to blue */
	glClearColor(0.0, 0.0, 1.0, 0.0);

	/* set fill color to red */
	glColor3f(1.0, 0.0, 0.0);

	/* set up standard orthogonal view with clipping */
	/* box as cube of side 2 centered at origin */
	/* This is default view and these statement could be removed */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
	/* Initialize mode and open a window in upper left corner of screen */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("A simple GLUT program: Red Square");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
}