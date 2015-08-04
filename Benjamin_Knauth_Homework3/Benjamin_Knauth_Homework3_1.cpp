// Include section
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <math.h>

// Global Variable Section
// List all of your global variables, stuctures and other definition here
// Window display size
GLsizei winWidth = 600, winHeight = 400;

// Used for Circle and Ellipse points
class screenPt
{
private:
	GLint x, y;

public:
	/*  Default Constructor: initializes coordinate position to (0, 0).  */
	screenPt()  {
		x = y = 0;
	}
	void setCoords(GLint xCoordValue, GLint yCoordValue)  {
		x = xCoordValue;
		y = yCoordValue;
	}

	GLint getx() const  {
		return x;
	}

	GLint gety() const  {
		return y;
	}
	void incrementx()  {
		x++;
	}
	void decrementy()  {
		y--;
	}
};

// Initialize method
void init(void)
{
	// Get and display your OpenGL version
	const GLubyte *Vstr;
	Vstr = glGetString(GL_VERSION);
	fprintf(stderr, "Your OpenGL version is %s\n", Vstr);

	// White color window
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// Projection on World Coordinates 
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-(GLdouble)winWidth / 2, (GLdouble)winWidth / 2, -(GLdouble)winHeight / 2, (GLdouble)winHeight / 2);
}
void otherCode()
{
	// Your other code here
}
// Set the Pixels for the current x,y position
void setPixel(GLint xPos, GLint yPos)
{
	glBegin(GL_POINTS);
	glVertex2i(xPos, yPos);
	glEnd();
}

void circlePlotPoints(GLint xc, GLint yc, screenPt circPt)
{
	setPixel(xc + circPt.getx(), yc + circPt.gety());
	setPixel(xc - circPt.getx(), yc + circPt.gety());
	setPixel(xc + circPt.getx(), yc - circPt.gety());
	setPixel(xc - circPt.getx(), yc - circPt.gety());
	setPixel(xc + circPt.gety(), yc + circPt.getx());
	setPixel(xc - circPt.gety(), yc + circPt.getx());
	setPixel(xc + circPt.gety(), yc - circPt.getx());
	setPixel(xc - circPt.gety(), yc - circPt.getx());
}
// Circle points are based on mid-point of circle
void circleMidpoint(GLint xc, GLint yc, GLint radius)
{
	screenPt circPt;

	GLint p = 1 - radius;         //  Initial value for midpoint parameter.

	circPt.setCoords(0, radius); //  Set coordinates for top point of circle.

	/*  Plot the initial point in each circle quadrant.  */
	circlePlotPoints(xc, yc, circPt);
	/*  Calculate next point and plot in each octant.  */
	while (circPt.getx() < circPt.gety()) {
		circPt.incrementx();
		if (p < 0)
			p += 2 * circPt.getx() + 1;
		else {
			circPt.decrementy();
			p += 2 * (circPt.getx() - circPt.gety()) + 1;
		}
		circlePlotPoints(xc, yc, circPt);
	}
}

void ellipsePlotPoints(int xCenter, int yCenter, int x, int y)
{
	setPixel(xCenter + x, yCenter + y);
	setPixel(xCenter - x, yCenter + y);
	setPixel(xCenter + x, yCenter - y);
	setPixel(xCenter - x, yCenter - y);
}

void ellipseMidpoint(int xCenter, int yCenter, int Rx, int Ry)
{
	int Rx2 = Rx * Rx;
	int Ry2 = Ry * Ry;
	int twoRx2 = 2 * Rx2;
	int twoRy2 = 2 * Ry2;
	int p;
	int x = 0;
	int y = Ry;
	int px = 0;
	int py = twoRx2 * y;

	/* Plot the initial point in each quadrant. */
	ellipsePlotPoints(xCenter, yCenter, x, y);

	/* Region 1 */
	p = ceil(Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
	while (px < py) {
		x++;
		px += twoRy2;
		if (p < 0)
			p += Ry2 + px;
		else {
			y--;
			py -= twoRx2;
			p += Ry2 + px - py;
		}
		ellipsePlotPoints(xCenter, yCenter, x, y);
	}

	/* Region 2 */
	p = ceil(Ry2 * (x + 0.5) * (x + 0.5) + Rx2 * (y - 1) * (y - 1) - Rx2 * Ry2);
	while (y > 0) {
		y--;
		py -= twoRx2;
		if (p > 0)
			p += Rx2 - py;
		else {
			x++;
			px += twoRy2;
			p += Rx2 - py + px;
		}
		ellipsePlotPoints(xCenter, yCenter, x, y);
	}
}

// Generate the Graphics
void displayFcn(void)
{
	// Clear display window.
	glClear(GL_COLOR_BUFFER_BIT);
	// Set  graphic objects color to Red or change for your choice
	glColor3f(1.0, 0.0, 1.0);
	// Your graphics code here

	// Sun
	GLint xc = 0, yc = 0, radius = 25;
	circleMidpoint(xc, yc, radius);
	glRasterPos2i(0, 0);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'U');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');

	// Mercury
	glColor3f(1.0, 0.0, 0.0);
	ellipseMidpoint(xc, yc, 60, 39);
	circleMidpoint(50, 22, 3.8);
	glRasterPos2i(50, 22);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'M');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'R');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'U');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'R');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'Y');

	// Venus
	glColor3f(0.0, 0.0, 1.0);
	ellipseMidpoint(xc, yc, 112, 72);
	circleMidpoint(-112, 0, 9.5);
	glRasterPos2i(-112, 0);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'V');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'U');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');

	// Earth
	glColor3f(0.0, 1.0, 0.0);
	ellipseMidpoint(xc, yc, 155, 100);
	circleMidpoint(-75, -87, 10);
	glRasterPos2i(-75, -87);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'R');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'T');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'H');

	// Mars
	glColor3f(0.0, 1.0, 1.0);
	ellipseMidpoint(xc, yc, 233, 150);
	circleMidpoint(0, -150, 5.3);
	glRasterPos2i(0, -150);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'M');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'R');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');

	// Execute OpenGL functions
	glFlush();
}
// Windows redraw function
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-(GLdouble)winWidth / 2, (GLdouble)winWidth / 2, -(GLdouble)winHeight / 2, (GLdouble)winHeight / 2);
	glClear(GL_COLOR_BUFFER_BIT);
}
// Main function
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Set initial Window position
	glutInitWindowPosition(200, 200);
	// Set Window Size
	glutInitWindowSize(winWidth, winHeight);
	// Set Window Title
	glutCreateWindow("CMSC405 Week3_6");
	// Initialize
	init();
	// Display function call
	glutDisplayFunc(displayFcn);
	// Window reshape call
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}