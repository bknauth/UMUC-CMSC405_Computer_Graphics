// Include section
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <cmath>
#endif
#include <stdio.h>

#define SLEEPMS 100 // sleep in miliseconds


/* Global variables */
char title[] = "The Teapot Robot";
// Window display size
GLsizei winWidth = 800, winHeight = 600;
// Angle for animation
GLfloat llTrans = -1.3f;
GLfloat rlTrans = -1.0f;
GLfloat teaRot = 0.0;
GLfloat headRot = 0.0;
GLfloat R = 0.0f;
GLfloat G = 1.0f;
GLfloat legPos = -2.0;
GLfloat midPos = -0.7;
GLfloat headPos = 0.5;
GLfloat MASS = 100.0;
GLfloat time = 0.00;
GLboolean moveLeft = true;
GLboolean pouring = true;
GLboolean allGreen = true;
GLfloat langle = 0.0f;

int font = (int)GLUT_BITMAP_8_BY_13;

/* Initialize OpenGL Graphics */
void init() {
	// Get and display your OpenGL version
	const GLubyte *Vstr;
	Vstr = glGetString(GL_VERSION);
	fprintf(stderr, "Your OpenGL version is %s\n", Vstr);

	// Set background color to black 
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	// Maximize depth display
	glClearDepth(1.0f);
	// Enable depth testing for z-culling
	glEnable(GL_DEPTH_TEST);
	// Set the type of depth-test
	glDepthFunc(GL_LEQUAL);
	// Provide smooth shading
	glShadeModel(GL_SMOOTH);
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

void rotateHead(void){
	Sleep(SLEEPMS);
	headRot += 5.0;
	glutPostRedisplay();
}
void pourTea(void){
	Sleep(SLEEPMS);
	if (pouring == true){
		teaRot -= 2.0f;
		if (teaRot < -50.0){
			pouring = false;
		}
	}
	else if (pouring == false){
		teaRot += 2.0f;
		if (teaRot > 0.0){
			pouring = true;
		}
	}
	glutPostRedisplay();
}
void moveLegs(void){
	Sleep(SLEEPMS);
	if (moveLeft == true){
		llTrans += 0.01f;
		rlTrans -= 0.01f;
		if (llTrans >= -1.0){
			moveLeft = false;
		}
	}
	else if (moveLeft == false){
		llTrans -= 0.01f;
		rlTrans += 0.01f;
		if (llTrans <= -1.3){
			moveLeft = true;
		}
	}

	glutPostRedisplay();
}
void changeColors(void){
	Sleep(SLEEPMS);
	if (allGreen == true){
		R += 0.05;
		G -= 0.05;
		if (R > 1.0){
			allGreen = false;
		}
	}
	else if (allGreen == false){
		R -= 0.05;
		G += 0.05;
		if (R < 0.0){
			allGreen = true;
		}
	}
	glutPostRedisplay();
}
void doAll(void)
{
	Sleep(SLEEPMS);
	if (moveLeft == true){
		llTrans += 0.01f;
		rlTrans -= 0.01f;
		if (llTrans >= -1.0){
			moveLeft = false;
		}
	}
	else if (moveLeft == false){
		llTrans -= 0.01f;
		rlTrans += 0.01f;
		if (llTrans <= -1.3){
			moveLeft = true;
		}
	}
	if (pouring == true){
		teaRot -= 2.0f;
		if (teaRot < -50.0){
			pouring = false;
		}
	}
	else if (pouring == false){
		teaRot += 2.0f;
		if (teaRot > 0.0){
			pouring = true;
		}
	}
	headRot += 5.0;
	if (allGreen == true){
		R += 0.05;
		G -= 0.05;
		if (R > 1.0){
			allGreen = false;
		}
	}
	else if (allGreen == false){
		R -= 0.05;
		G += 0.05;
		if (R < 0.0){
			allGreen = true;
		}
	}
	glutPostRedisplay();
}
void dropRobot(void){
	Sleep(SLEEPMS);
	GLfloat accel = 9.8 * MASS * pow(time,2.0);
	if (time < 0.03){
		time += 0.001;
	}
	legPos -= accel;
	midPos -= accel;
	headPos -= accel;
	if (headPos < -4.0){
		legPos += 10.0;
		midPos += 10.0;
		headPos += 10.0;	
	}
	glutPostRedisplay();
}

void displayDirections(void){
	// Directions 
	glColor3f(1.0f, 1.0f, 0.0f);
	renderBitmapString(-0.8, 2.7, (void *)font, "The Teapot Robot");
	renderBitmapString(-0.8, 2.55, (void *)font, "press t to Pour Tea");
	renderBitmapString(-0.8, 2.4, (void *)font, "press w to Walk");
	renderBitmapString(-0.8, 2.25, (void *)font, "press h to Rotate Head");
	renderBitmapString(-0.8, 2.1, (void *)font, "press c to Change Colors");
	renderBitmapString(-0.8, 1.95, (void *)font, "press a for All");
	renderBitmapString(-0.8, 1.8, (void *)font, "press s to Stop");
	renderBitmapString(-0.8, 1.65, (void *)font, "press d to Drop");
}
// Display Function
void displayfcn() {
	// Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Model view matrix mode
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Call Display Directions function
	displayDirections();

	// Left leg
	glColor3f(0.0, 1.0, 0.0);
	glLoadIdentity();
	glTranslatef(llTrans, legPos, -7.0);
	glScalef(0.2, 1.0, 0.5);
	glRotatef(-50.0, 0.0f, 0.0f, 1.0f);
	glutWireCube(1.0);

	// Right leg
	glLoadIdentity();
	glTranslatef(rlTrans, legPos, -7.0);
	glScalef(0.2, 1.0, 0.5);
	glRotatef(50.0, 0.0f, 0.0f, 1.0f);
	glutWireCube(1.0);

	// Body
	glColor3f(R, G, 0.0);
	glLoadIdentity();
	glTranslatef(-1.15f, midPos, -7.0f);
	glScalef(0.5f, 1.0f, 0.5f);
	glRotatef(0.0, 1.0f, 0.0f, 1.0f);
	glutWireSphere(0.75, 15, 15);

	// Left teapot
	glColor3f(0.5, 0.5, 0.5);
	glLoadIdentity();
	glTranslatef(-1.8f, midPos, -7.0f);
	glScalef(0.3f, 0.3f, 0.3f);
	glRotatef(180.0, 0.0f, 1.0f, 0.0f);
	glRotatef(teaRot, 0.0f, 0.0f, 1.0f);
	glutWireTeapot(1.0);

	// Right teapot
	glLoadIdentity();
	glTranslatef(-0.5f, midPos, -7.0f);
	glScalef(0.3f, 0.3f, 0.3f);
	glRotatef(0.0, 0.0f, 0.0f, 0.0f);
	glRotatef(teaRot, 0.0f, 0.0f, 1.0f);
	glutWireTeapot(1.0);

	// Head
	glColor3f(1.0, 0.0, 0.0);
	glLoadIdentity();
	glTranslatef(-1.1f, headPos, -7.0f);
	glScalef(0.2f, 0.2f, 0.2f);
	glRotatef(70.0, 1.0f, 0.0f, 0.0f);
	glRotatef(headRot, 1.0f, 0.0f, 1.0f);
	glutWireTorus(0.5,1.5,10,10);
	
	// Double buffering
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 't'://Pour Tea
		glutIdleFunc(pourTea);
		break;
	case 'w'://Walk
		glutIdleFunc(moveLegs);
		break;
	case 'h':
		//Rotate Head
		glutIdleFunc(rotateHead);
		break;
	case 'c':
		// Change colors
		glutIdleFunc(changeColors);
		break;
	case 'a':
		//All
		glutIdleFunc(doAll);
		break;
	case 'd':
		//All
		glutIdleFunc(dropRobot);
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