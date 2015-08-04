// Include section
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES
#include <cmath>
#define SLEEPMS 25 // sleep in miliseconds


/* Global variables */
char title[] = "Animal Farm";
// Window display size
GLsizei winWidth = 800, winHeight = 600;
// Angle for animation
int font = (int)GLUT_BITMAP_8_BY_13;
GLfloat MASS = 100.0;
GLfloat time = 0.00;
GLfloat skyColor = 1.0;
GLfloat sunColor = 0.0;
GLfloat sunPos = 2.0;
GLfloat sheepHead = 0.5;
GLfloat sheepHeadRot = 0.0;
GLboolean sheepHeadDown = false;
GLfloat pigHead = 0.5;
GLboolean pigHeadDown = false;

GLfloat rainPos = 0.5;

/* Initialize OpenGL Graphics */
void init() {
	// Get and display your OpenGL version
	const GLubyte *Vstr;
	Vstr = glGetString(GL_VERSION);
	fprintf(stderr, "Your OpenGL version is %s\n", Vstr);	

	// Set background color to blue 
	glClearColor(0.0f, 0.0f, skyColor, 0.0f);
	// Maximize depth display
	glClearDepth(1.0f);
	// Enable depth testing for z-culling
	glEnable(GL_DEPTH_TEST);
	// Set the type of depth-test
	glDepthFunc(GL_LEQUAL);
	// Provide smooth shading
	
}

// convenience function for displaying strings
void renderBitmapString(float x, float y, void *font, char *string)
{
	char *c;
	glRasterPos3f(x, y, -7.0);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void doAll(void)
{
	Sleep(SLEEPMS);

	if (skyColor <= 0.0){
		// controls the specular color 
		GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 1.0 };
		GLfloat mat_shininess[] = { 100.0 };
		GLfloat light_position[] = { 4.0, sunPos, -4.0, 0.0 };
		// Apply the specular color to the front. 
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		// Apply the shininess to the front. 
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		// Apply the first light (Light0) at the assigned position 
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		// Enable lighting and Depth perception 
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	else
		glDisable(GL_LIGHTING);


	//Rain movement
	GLfloat accel = 9.8 * MASS * pow(time, 2.0);
	if (time < 0.03){
		time += 0.001;
	}
	rainPos -= accel;
	if (rainPos < -4.0){
		time = 0.0;
		rainPos = 0.5;
	}

	//Sheep movement
	if (sheepHeadDown == false){
		if (sheepHead == 0.5 && sheepHeadRot > -50.0){
			sheepHeadRot -= 1.0;
		}
		else if (sheepHeadRot == -50.0 & sheepHead > -0.3){
			sheepHead -= 0.01;
		}
		else{
			sheepHeadDown = true;
		}
	}
	else if (sheepHeadDown == true){
		if (sheepHead < 0.5){
			sheepHead += 0.01;
		}
		else if (sheepHead == 0.5 && sheepHeadRot < 0.0){
			sheepHeadRot += 1.0;
		}
		else
			sheepHeadDown = false;
	}
	//Pig movement
	if (pigHeadDown == false){
		if (pigHead > -0.3){
			pigHead -= 0.01;
		}
		else{
			pigHeadDown = true;
		}
	}
	else if (pigHeadDown == true){
		if (pigHead < 0.5){
			pigHead += 0.01;
		}
		else
			pigHeadDown = false;
	}
	//Sun movement
	if (sunPos > 0.0){
		sunPos -= 0.01;
	}
	if (sunPos <= 0.0 && sunPos > -2.2){
		sunPos -= 0.01;
		if (skyColor > 0.0){
			skyColor -= 0.005;
		}
		glClearColor(0.0f, 0.0f, skyColor, 0.0f);
	}
	if (sunPos <= -2.2 && sunColor == 0.0){
		sunPos = 6.0;
		sunColor = 1.0;
	}
	else if (sunPos <= -2.2 && sunColor == 1.0){
		sunPos = 6.0;
		sunColor = 0.0;
	}
	if (sunPos > 4.0 && sunColor == 0.0 && skyColor < 1.0){
		skyColor += 0.005;
		glClearColor(0.0f, 0.0f, skyColor, 0.0f);
	}

	glutPostRedisplay();
}

void sheep(GLdouble x, GLdouble y, GLdouble z){
	// Body
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	glTranslatef(x,y,z);
	glScalef(1.0f, 0.5f, 0.5f);
	glutSolidSphere(0.75, 15, 15);

	// Head
	glColor3f(0.7, 0.7, 0.7);
	glTranslatef(0.7f, sheepHead, 0.0f);
	glRotatef(sheepHeadRot, 0.0f, 0.0f, 1.0f);
	glScalef(0.5f, 0.3f, 0.3f);	
	glutSolidSphere(0.75, 15, 15);

	//Legs
	glLoadIdentity(); 
	glTranslatef(-1.15, -0.7, -7.0f);
	glScalef(1.0f, 0.5f, 0.5f);
	glTranslatef(0.5f, 0.5, 0.0f);
	glScalef(0.5f, 0.3f, 0.3f);
	glColor3f(0.7, 0.7, 0.7);
	glTranslatef(-2.0f, -4.0, 1.0f);
	glScalef(0.3f, 4.0f, 1.0f);
	glutSolidCube(1.0);	
	glTranslatef(1.5f, 0.0f, -1.0f);
	glutSolidCube(1.0);	
	glTranslatef(5.0f, 0.0f, 0.0f);
	glutSolidCube(1.0);
	glTranslatef(-1.5f, 0.0f, 1.0f);
	glutSolidCube(1.0);
}

void pig(GLdouble x, GLdouble y, GLdouble z){
	// Body
	glColor3f(1.0, 0.3, 0.3);
	glLoadIdentity();
	glTranslatef(x, y, z);
	glScalef(1.0f, 0.5f, 0.5f);
	glutSolidSphere(0.75, 15, 15);

	// Head
	glTranslatef(-0.7f, pigHead, 0.0f);
	glColor3f(0.7, 0.0, 0.0);
	glScalef(0.3f, 0.6f, 0.6f);
	glutSolidSphere(0.75, 15, 15);

	//Legs
	glLoadIdentity();
	glTranslatef(x, y, z);
	glScalef(1.0f, 0.5f, 0.5f);
	glTranslatef(-0.7f, 0.5, 0.0f);
	glScalef(0.3f, 0.6f, 0.6f);

	glTranslatef(0.5f, -2.0, 1.0f);
	glScalef(0.3f, 2.0f, 1.0f);
	glutSolidCube(1.0);
	glTranslatef(1.5f, 0.0f, -1.0f);
	glutSolidCube(1.0);
	glTranslatef(10.0f, 0.0f, 0.0f);
	glutSolidCube(1.0);
	glTranslatef(-1.5f, 0.0f, 1.0f);
	glutSolidCube(1.0);
}

void triangle(double x, double y, double z){
	glLoadIdentity();
	glTranslatef(x, y, z);
	glColor3f(0.0, 1.0, 0.0);
	glScalef(0.1f, 0.1f, 0.1f);
	glBegin(GL_POLYGON);
		glVertex2i(0.0, 0.0);
		glVertex2i(2.0, -2.0);
		glVertex2i(-2.0, -2.0);
	glEnd();
}

void grass(){
	for (double i = -5; i < 5; i += .1){
		glLoadIdentity();
		triangle(i, -1.0, -9.0);
	}
	for (double i = -5; i < 5; i += .1){
		glLoadIdentity();
		triangle(i, -1.0, -7.9);
	}
	for (double i = -5; i < 5; i += .1){
		glLoadIdentity();
		triangle(i, -1.0, -7.0);
	}
	for (double i = -5; i < 5; i += .1){
		glLoadIdentity();
		triangle(i, -1.0, -6.0);
	}
	for (double i = -5; i < 5; i += .1){
		glLoadIdentity();
		triangle(i, -1.0, -5.0);
	}
	for (double i = -5; i < 5; i += .1){
		glLoadIdentity();
		triangle(i, -1.0, -4.0);
	}
	for (double i = -5; i < 5; i += .1){
		glLoadIdentity();
		triangle(i, -1.0, -3.5);
	}
	for (double i = -5; i < 5; i += .1){
		glLoadIdentity();
		triangle(i, -1.0, -3.0);
	}
}

void clouds(){
	// Head
	glTranslatef(-2.0f, 1.0, -8.0f);
	glColor3f(0.5, 0.5, 0.5);
	glutSolidSphere(0.25, 15, 15);
	glTranslatef(-0.25f, 0.25, 0.0f);
	glutSolidSphere(0.25, 15, 15);
	glTranslatef(-0.25f, -0.25, 0.0f);
	glutSolidSphere(0.25, 15, 15);
	glTranslatef(-0.25f, 0.25, 0.0f);
	glutSolidSphere(0.25, 15, 15);
	glTranslatef(-0.25f, -0.25, 0.0f);
	glutSolidSphere(0.25, 15, 15);
	glTranslatef(-0.25f, 0.25, 0.0f);
	glutSolidSphere(0.25, 15, 15);
	glTranslatef(-0.25f, -0.25, 0.0f);
	glutSolidSphere(0.25, 15, 15);
}

void rainDrop(){
	glColor3f(0.0, 1.0, 1.0);
	GLubyte bitShape2[72] = {
		0x01, 0xFF, 0x80,
		0x03, 0xFF, 0xC0,
		0x07, 0xFF, 0xE0,
		0x0F, 0xFF, 0xF0,
		0x1F, 0xFF, 0xF8,
		0x3F, 0xFF, 0xFC,
		0x3F, 0xFF, 0xFC,
		0x7F, 0xFF, 0xFE,
		0x7F, 0xFF, 0xFE,
		0x7F, 0xFF, 0xFE,
		0x3F, 0xFF, 0xFC,
		0x3F, 0xFF, 0xFC,
		0x1F, 0xFF, 0xF8,
		0x0F, 0xFF, 0xF0,
		0x07, 0xFF, 0xE0,
		0x03, 0xFF, 0xC0,
		0x01, 0xFF, 0x80,
		0x00, 0xFF, 0x00,
		0x00, 0x7E, 0x00,
		0x00, 0x7E, 0x00,
		0x00, 0x3C, 0x00,
		0x00, 0x3C, 0x00,
		0x00, 0x18, 0x00,
		0x00, 0x18, 0x00,	
	};
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTranslatef(-0.1f, rainPos, -9.0f);
	glRasterPos2i(-4.0, 0.0);
	
	glBitmap(24.0, 24.0, 0.0, 0.0, 36.0, 0.0, bitShape2);
	glBitmap(24.0, 24.0, 0.0, 0.0, 36.0, 24.0, bitShape2);
	glBitmap(24.0, 24.0, 0.0, 0.0, 36.0, -24.0, bitShape2);
	glBitmap(24.0, 24.0, 0.0, 0.0, 36.0, 24.0, bitShape2);
	glBitmap(24.0, 24.0, 0.0, 0.0, 36.0, -24.0, bitShape2);
	glFlush();
}

void displayDirections(void){
	// Directions 
	glColor3f(1.0f, 1.0f, 0.0f);
	renderBitmapString(-0.8, 2.7, (void *)font, "Press \"a\" to start animation.");
	renderBitmapString(-0.8, 2.4, (void *)font, "Press \"s\" to pause animation.");
}
// Display Function
void displayfcn() {
	// Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Model view matrix mode
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	sheep(-1.15, -0.7, -7.0f);
	pig(3.0f, -0.7f, -7.0f);
	grass();

	//Ground
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -8.0);
	glColor3f(0.5, 0.5, 0.0);
	glRecti(-5.0, -5.0, 5.0, -1.99999);

	//Sun
	glLoadIdentity();
	glTranslatef(2.0, sunPos, -10.0);
	glColor3f(1.0, 1.0, sunColor);
	glutSolidSphere(1.0,15,15);

	//Clouds
	glLoadIdentity();
	clouds();

	//Rain Drop
	glLoadIdentity();
	rainDrop();

	//Message
	glLoadIdentity();
	glTranslatef(-3.0, 0.0, -5.0);
	displayDirections();

	// Double buffering
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		//All
		glutIdleFunc(doAll);
		break;
	case 's':
		// stop all
		glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

// Windows redraw function
void winReshapeFcn(GLsizei width, GLsizei height) {
	// Compute aspect ratio of the new window
	if (height == 0)
		height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport 
	// Allows for resizing without major display issues
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Enable perspective projection with fovy, aspect, zNear and zFar
	// This is the camera view and objects align with view frustum	
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

/* Main function: GLUT runs as a console application starting at main() */
void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	// Set the window's initial width & height
	glutInitWindowSize(winWidth, winHeight);
	// Position the window's initial top-left corner
	glutInitWindowPosition(50, 50);
	// Create window with the given title
	glutCreateWindow(title);
	// Display Function
	glutDisplayFunc(displayfcn);
	// Reshape function
	glutReshapeFunc(winReshapeFcn);
	// Initialize
	init();

	// Keyboard functions
	glutKeyboardFunc(keyboard);

	// Process Loop
	glutMainLoop();
}