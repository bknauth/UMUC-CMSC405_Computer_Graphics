// Include section
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <math.h>
// Need Math Defines before cmath to use Math constants
#define _USE_MATH_DEFINES
#include <cmath>
// Define 3 Vertices
#define VERTNUM 7

// Global Variable Section
// List all of your global variables, stuctures and other definition here
// Window display size
GLsizei winWidth = 400, winHeight = 400;

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
// Class to store x,y 2D points
class Pt2D {
public:
	GLfloat x, y;
};
// Function to Translate 2D vertices 
void translatePolygon(Pt2D * verts, GLint nVerts, GLfloat tx, GLfloat ty)
{
	GLint k;
	// translate each vertex
	for (k = 0; k < nVerts; k++) {
		verts[k].x = verts[k].x + tx;
		verts[k].y = verts[k].y + ty;
	}	
}
// Rotate - theta is in radians - not degrees
void rotatePolygon(Pt2D * verts, GLint nVerts, Pt2D pivPt,
	GLdouble theta)
{
	Pt2D vertsRot[VERTNUM];
	GLint k;

	for (k = 0; k < nVerts; k++) {
		vertsRot[k].x = pivPt.x + (verts[k].x - pivPt.x) * cos(theta)
			- (verts[k].y - pivPt.y) * sin(theta);
		vertsRot[k].y = pivPt.y + (verts[k].x - pivPt.x) * sin(theta)
			+ (verts[k].y - pivPt.y) * cos(theta);
	}
	// Display the original Triangle
	glBegin(GL_POLYGON);
	// Loop through the struct and display triangle
	for (k = 0; k < VERTNUM; k++) {
		glVertex2i(vertsRot[k].x, vertsRot[k].y);
	}
	glEnd();
}
// Scale the polygon sx and sy factor. Note: 1.5 =150% scaling, 0.5 = 50% scaling)
// The fixed point, represents the location of the new scaled display
void scalePolygon(Pt2D * verts, GLint nVerts, Pt2D fixedPt,
	GLfloat sx, GLfloat sy)
{
	Pt2D vertsNew[11];
	GLint k;

	for (k = 0; k < 11; k++) {
		vertsNew[k].x = verts[k].x * sx + fixedPt.x;
		vertsNew[k].y = verts[k].y * sy + fixedPt.y;
	}
	glBegin(GL_POLYGON);
	for (k = 0; k < 11; k++)
		glVertex2f(vertsNew[k].x, vertsNew[k].y);
	glEnd();
}
// Generate the Graphics
void displayFcn(void)
{
	// Clear display window.
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	GLint k;
	// Arrow
	Pt2D myverts[7];
	myverts[0].x = 0;
	myverts[0].y = 0;
	myverts[1].x = -30;
	myverts[1].y = 20;
	myverts[2].x = -10;
	myverts[2].y = 20;
	myverts[3].x = -10;
	myverts[3].y = 60;
	myverts[4].x = 10;
	myverts[4].y = 60;
	myverts[5].x = 10;
	myverts[5].y = 20;
	myverts[6].x = 30;
	myverts[6].y = 20;

	translatePolygon(myverts, 7, 0, 10);
	glBegin(GL_POLYGON);
	for (k = 0; k < 7; k++) {
		glVertex2i(myverts[k].x, myverts[k].y);
	}
	glEnd();
	
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 7; k++) {
		glVertex2i(myverts[k].x, myverts[k].y);
	}
	glEnd();
	Pt2D pivot[4];
	pivot[0].x = 0;
	pivot[0].y = 0;
	pivot[1].x = 250;
	pivot[1].y = -50;
	pivot[2].x = 175;
	pivot[2].y = -200;
	pivot[3].x = 75;
	pivot[3].y = -350;

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	rotatePolygon(myverts, 7, pivot[0], M_PI / 2);
	glPopMatrix();
	glPushMatrix();	
	glColor3f(0.0, 0.0, 1.0);
	rotatePolygon(myverts, 7, pivot[0], M_PI);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0, 0.0, 1.0);
	rotatePolygon(myverts, 7, pivot[0], 3 * M_PI / 2);
	glPopMatrix();

	//Crown
	glColor3f(0.0, 0.0, 0.0);
	Pt2D myverts2[11];
	myverts2[0].x = 0;
	myverts2[0].y = 0;
	myverts2[1].x = -30;
	myverts2[1].y = 30;
	myverts2[2].x = -10;
	myverts2[2].y = 20;
	myverts2[3].x = -10;
	myverts2[3].y = 30;
	myverts2[4].x = 0;
	myverts2[4].y = 20;
	myverts2[5].x = 10;
	myverts2[5].y = 40;
	myverts2[6].x = 20;
	myverts2[6].y = 20;
	myverts2[7].x = 30;
	myverts2[7].y = 30;
	myverts2[8].x = 30;
	myverts2[8].y = 20;
	myverts2[9].x = 50;
	myverts2[9].y = 30;
	myverts2[10].x = 20;
	myverts2[10].y = 0;

	translatePolygon(myverts2, 11, -100, 100);
	glBegin(GL_POLYGON);
	for (k = 0; k < 11; k++) {
		glVertex2i(myverts2[k].x, myverts2[k].y);
	}
	glEnd();
	glColor3f(0.0, 1.0, 1.0);
	scalePolygon(myverts2, 11, pivot[1], 1.5, 1.5);	
	glColor3f(1.0, 1.0, 0.0);
	scalePolygon(myverts2, 11, pivot[2], 0.5, 0.5);
	glColor3f(0.0, 1.0, 0.0);
	scalePolygon(myverts2, 11, pivot[3], 2.0, 2.0);
	
	//Text
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(-150, 150); 
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'K');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'I');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'G');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'O');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'F');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'T');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'H');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'H');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'I');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'L');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'L');
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
	glutCreateWindow("CMSC405 Template");
	// Initialize
	init();
	// Display function call
	glutDisplayFunc(displayFcn);
	// Window reshape call
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}