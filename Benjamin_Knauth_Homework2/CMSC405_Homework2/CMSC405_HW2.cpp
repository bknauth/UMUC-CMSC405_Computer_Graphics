// Include section
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath> 


// Global Variable Section
// List all of your global variables, stuctures and other definition here
// Window display size
GLsizei winWidth = 800, winHeight = 600;

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
// Generate the Graphics
void displayFcn(void)
{
	// Clear display window.
	glClear(GL_COLOR_BUFFER_BIT);
	// Set  graphic objects color to Red or change for your choice
	glColor3f(1.0, 0.0, 0.0);
	// Your graphics code here
	glBegin(GL_LINES);
		//Red line
		glVertex2i(-200, 300);
		glVertex2i(-200, -300);
		//Green line
		glColor3f(0.0, 1.0, 0.0);
		glVertex2i(200, 300);
		glVertex2i(200, -300);
	glEnd();

	//Red Rectangle
	glColor3f(4.0, 0.0, 0.0);
	glRecti(-350, 0, -250, 250);
	
	//Yellow Rectangle
	int vertex1[] = {-300, -250};
	int vertex2[] = {-250, -150};
	glColor3f(1.0, 1.0, 0.0);
	glRectiv(vertex1, vertex2);

	//Teal Hexagon
	glColor3f(0.0, 1.0, 1.0);
	GLuint regPent;
	GLdouble theta;
	GLint x, y, k;

	regPent = glGenLists(1);
	glNewList(regPent, GL_COMPILE);
	glBegin(GL_POLYGON);
	for (k = 0; k < 5; k++){
		theta = 2 * M_PI * k / 5.0;
		x = 300 + 72 * cos(theta);
		y = 200 + 72 * sin(theta);
		glVertex2i(x, y);
	}
	glEnd();
	glEndList();
	glCallList(regPent);

	//Purple Triangle
	glColor3f(1.0, 0.0, 1.0);
	GLuint regTri;
	GLdouble theta2;
	GLint a, b, i;

	regTri = glGenLists(1);
	glNewList(regTri, GL_COMPILE);
	glBegin(GL_POLYGON);
	for (i = 0; i < 3; i++){
		theta2 = 2 * M_PI * i / 3.0;
		a = 300 + 72 * cos(theta2);
		b = -200 + 72 * sin(theta2);
		glVertex2i(a, b);
	}
	glEnd();
	glEndList();
	glCallList(regTri);

	//Black Compass
	glColor3f(0.0, 0.0, 0.0);

	GLubyte bitShape3[72] {
		0x00, 0x18, 0x00,
		0x00, 0x3C, 0x00,
		0x00, 0x7E, 0x00,
		0x00, 0x18, 0x00,
		0x00, 0x18, 0x00,
		0x00, 0x18, 0x00,
		0x00, 0x18, 0x00,
		0x00, 0x18, 0x00,
		0x00, 0x18, 0x00,
		0x20, 0x18, 0x04,
		0x60, 0x3C, 0x06,
		0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF,
		0x60, 0x3C, 0x06,
		0x20, 0x18, 0x04,
		0x00, 0x18, 0x00,
		0x00, 0x18, 0x00,
		0x00, 0x18, 0x00,
		0x00, 0x18, 0x00,
		0x00, 0x18, 0x00,
		0x00, 0x18, 0x00,
		0x00, 0x7E, 0x00,
		0x00, 0x3C, 0x00,
		0x00, 0x18, 0x00,
	};

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glRasterPos2i(0, 0);
	glBitmap(24.0, 24.0, 0.0, 0.0, 24.0, 12.0, bitShape3);

	//N, S, E, W Text glutBitmapCharacter(GLUT_BITMAP_9_BY_15,'U');
	glRasterPos2i(7, 27);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glRasterPos2i(25, 7);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');
	glRasterPos2i(7, -12);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');
	glRasterPos2i(-10, 7);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'W');

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
	glutInitWindowPosition(100, 100);
	// Set Window Size
	glutInitWindowSize(winWidth, winHeight);
	// Set Window Title
	glutCreateWindow("Benjamin Knauth - Homework 2");
	// Initialize
	init();
	// Display function call
	glutDisplayFunc(displayFcn);
	// Window reshape call
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}