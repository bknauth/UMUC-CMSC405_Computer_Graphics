// Include section
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>


// Global Variable Section
// List all of your global variables, stuctures and other definition here
// Window display size
GLsizei winWidth = 800, winHeight = 400;

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
	glColor3f(0.0, 0.0, 0.0);
	// Your graphics code here 
	glBegin(GL_LINES);
		//Box
		glVertex2i(-275, 175);
		glVertex2i(-275, -175);
		glVertex2i(-275, -175);
		glVertex2i(335, -175);
		glVertex2i(335, -175);
		glVertex2i(335, 175);
		glVertex2i(335, 175);
		glVertex2i(-275, 175);

		//Internal lines
		glVertex2i(-225, 165);
		glVertex2i(-225, -165);
		glVertex2i(-230, 165);
		glVertex2i(230, 165);
		glVertex2i(-230, 132);
		glVertex2i(230, 132);
		glVertex2i(-230, 99);
		glVertex2i(230, 99);
		glVertex2i(-230, 66);
		glVertex2i(230, 66);
		glVertex2i(-230, 33);
		glVertex2i(230, 33);
		glVertex2i(-230, 0);
		glVertex2i(230, 0);
		glVertex2i(-230, -33);
		glVertex2i(230, -33);
		glVertex2i(-230, -66);
		glVertex2i(230, -66);
		glVertex2i(-230, -99);
		glVertex2i(230, -99);
		glVertex2i(-230, -132);
		glVertex2i(230, -132);
		glVertex2i(-230, -165);
		glVertex2i(230, -165);

		//Vertical dashes
		glVertex2i(-60, -66);
		glVertex2i(-60, -74);
		glVertex2i(88, -66);
		glVertex2i(88, -74);
		glVertex2i(230, -66);
		glVertex2i(230, -74);
	glEnd();

	glRasterPos2i(-260, 160);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '7');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

	glRasterPos2i(-260, 127);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '6');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

	glRasterPos2i(-260, 94);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '5');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

	glRasterPos2i(-260, 61);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '4');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

	glRasterPos2i(-260, 28);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '3');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

	glRasterPos2i(-260, -5);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '2');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

	glRasterPos2i(-260, -38);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

	glRasterPos2i(-260, -71);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

	glRasterPos2i(-270, -104);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '-');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

	glRasterPos2i(-270, -137);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '-');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '2');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

	glRasterPos2i(-270, -170);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '-');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '3');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

	glRasterPos2i(-230, -88);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
	
	glRasterPos2i(-82, -88);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '5');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

	glRasterPos2i(66, -88);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

	glRasterPos2i(214, -88);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '1');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '5');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0');

	//http://www.smartconversion.com/otherInfo/gravity_of_planets_and_the_sun.aspx

	//'E' for Earth
	glColor3f(0.0, 1.0, 0.0);
	double x;
	double y;
	int t = 0;
	double x_convert;
	double y_convert;
	do{
		x = 500 + (30 * t);
		y = 400 + (40 * t) - (0.5 * 9.8 * (t * t));
		x_convert = x / 3.2967 - 215;
		y_convert = y / 3.03 - 71;
		glRasterPos2i(x_convert, y_convert);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');
		t++;		
	} while (y >= 0);
	glRasterPos2i(250, 50);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '\'');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '\'');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'h');

	//'M' for Mercury
	glColor3f(1.0, 0.0, 0.0);
	t = 0;
	do{
		x = 500 + (30 * t);
		y = 400 + (40 * t) - (0.5 * 3.7 * (t * t));
		x_convert = x / 3.2967 - 215;
		y_convert = y / 3.03 - 71;
		glRasterPos2i(x_convert, y_convert);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'M');
		t++;
	} while (y >= 0);
	glRasterPos2i(250, 75);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '\'');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'M');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '\'');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 's');

	//'V' for Venus
	glColor3f(0.0, 0.0, 1.0);
	t = 0;
	do{
		x = 500 + (30 * t);
		y = 400 + (40 * t) - (0.5 * 8.9 * (t * t));
		x_convert = x / 3.2967 - 215;
		y_convert = y / 3.03 - 71;
		glRasterPos2i(x_convert, y_convert);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'V');
		t++;
	} while (y >= 0);
	glRasterPos2i(250, 25);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '\'');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'V');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '\'');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'n');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'u');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 's');

	//'J' for Jupiter
	glColor3f(1.0, 0.0, 1.0);
	t = 0;
	do{
		x = 500 + (30 * t);
		y = 400 + (40 * t) - (0.5 * 24.9 * (t * t));
		x_convert = x / 3.2967 - 215;
		y_convert = y / 3.03 - 71;
		glRasterPos2i(x_convert, y_convert);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'J');
		t++;
	} while (y >= 0);
	glRasterPos2i(250, 0);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '\'');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'J');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '\'');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'u');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'p');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');

	glFlush();
}
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-(GLdouble)winWidth / 2, (GLdouble)winWidth / 2, -(GLdouble)winHeight / 2, (GLdouble)winHeight / 2);
	glClear(GL_COLOR_BUFFER_BIT);
}
//
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
	glutCreateWindow("CMSC405 Template");
	// Initialize
	init();
	// Display function call
	glutDisplayFunc(displayFcn);
	// Window reshape call
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}