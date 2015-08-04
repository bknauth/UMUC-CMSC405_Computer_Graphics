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
#define VERTNUM 20

// Global Variable Section
// List all of your global variables, stuctures and other definition here
// Window display size
GLsizei winWidth = 400, winHeight = 400;

int pause, inventory, map;

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
class Pt2D {
public:
	GLfloat x, y;
};
void translatePolygon(Pt2D * verts, GLint nVerts, GLfloat tx, GLfloat ty)
{
	GLint k;
	// translate each vertex
	for (k = 0; k < nVerts; k++) {
		verts[k].x = verts[k].x + tx;
		verts[k].y = verts[k].y + ty;
	}
}
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
	glBegin(GL_POLYGON);
	for (k = 0; k < nVerts; k++) {
		glVertex2i(vertsRot[k].x, vertsRot[k].y);
	}
	glEnd();
}
void scalePolygon(Pt2D * verts, GLint nVerts, Pt2D fixedPt,
	GLfloat sx, GLfloat sy)
{
	Pt2D vertsNew[VERTNUM];
	GLint k;

	for (k = 0; k < nVerts; k++) {
		vertsNew[k].x = verts[k].x * sx + fixedPt.x;
		vertsNew[k].y = verts[k].y * sy + fixedPt.y;
	}
	glBegin(GL_POLYGON);
	for (k = 0; k < nVerts; k++)
		glVertex2f(vertsNew[k].x, vertsNew[k].y);
	glEnd();
}
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
void pauseCode()
{
	// Your other code here
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(-155.0, -25.0, 0.0);
	glRecti(0, 0, 100, 20);
	glPopMatrix();

	glBegin(GL_LINES);
		glVertex2i(-25, 45);
		glVertex2i(19, 45);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(-25, 50);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'P');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'U');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(-150, -20);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'O');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'T');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'I');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'U');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');

	glRasterPos2i(-150, -40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'I');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'V');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'T');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'O');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'R');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'Y');

	glRasterPos2i(-150, -60);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'V');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');	

	glRasterPos2i(-150, -80);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'L');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'O');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'D');

	glRasterPos2i(-150, -100);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'T');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'T');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'I');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'G');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');

	glRasterPos2i(-150, -120);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'G');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'R');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'P');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'H');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'I');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');

	glRasterPos2i(-150, -140);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'Q');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'U');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'I');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'T');
}
void mapCode()
{
	//Ghosts
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	GLubyte bitShape3[72] {
		0x03, 0x18, 0xC0,
		0x07, 0xBD, 0xE0,
		0x0F, 0xFF, 0xF0,
		0x0F, 0x33, 0x30,
		0x0C, 0xCC, 0xF0,
		0x0F, 0xFF, 0xF0,
		0x0E, 0x3C, 0x70,
		0x06, 0x3C, 0x60,
		0x06, 0x3C, 0x60,
		0x07, 0xFF, 0xE0,
		0x03, 0xFF, 0xC0,
		0x03, 0xFF, 0xC0,
		0x01, 0xFF, 0x80,
		0x00, 0xFF, 0x06,
		0x00, 0x7E, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x00, 0x00,
		0x00, 0x18, 0x00,		
	};
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glRasterPos2i(0, 0);	
	glBitmap(24.0, 24.0, 0.0, 0.0, 24.0, 12.0, bitShape3);

	glColor3f(1.0, 0, 0);
	glRasterPos2i(-100, -50);
	glBitmap(24.0, 24.0, 0.0, 0.0, 24.0, 12.0, bitShape3);

	glColor3f(1.0, 1.0, 0);
	glRasterPos2i(50, 75);
	glBitmap(24.0, 24.0, 0.0, 0.0, 24.0, 12.0, bitShape3);

	glColor3f(1.0, 0.0, 1.0);
	glRasterPos2i(0, 150);
	glBitmap(24.0, 24.0, 0.0, 0.0, 24.0, 12.0, bitShape3);

	//Player
	glPushMatrix();
	glTranslatef(-150.0, 125.0, 0.0);
	glColor3f(0.5, 0.5, 0.5);
	glRecti(0, 0, 12, 22);
	glColor3f(1.0, 1.0, 0.0);
	glRecti(0, 5, 12, 10);
	glColor3f(0.0, 1.0, 1.0);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRecti(15, 10, 0, 15);
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	glRecti(-5, 23, 10, 18);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(0, -18, 0.0);	
	glColor3f(0.5, 0.5, 0.5);
	glRecti(0, 0, 12, 22);
	glColor3f(1.0, 1.0, 0.0);
	glRecti(0, 18, 12, 20);
	glColor3f(1.0, 1.0, 1.0);
	glRecti(4, 0, 8, 12);	
	glPopMatrix();
	glPushMatrix();	
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-160.0, 130.0, 0.0);
	glScalef(0.5f, 0.5f, 1.0f);
	glRecti(0, 0, 5, 15);
	glRecti(-5, 15, 10, 20);
	glPopMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();	
	glTranslatef(-160.0, 130.0, 0.0);
	glScalef(0.5f, 0.5f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex2i(-2, 20);
		glVertex2i(-2, 40);
		glVertex2i(3, 50);
		glVertex2i(8, 40);
		glVertex2i(8, 20);
	glEnd();
	glPopMatrix();

	glPushMatrix();	
	glTranslatef(-130.0, 115.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2i(0, 0);
	glVertex2i(-7, 5);
	glVertex2i(-10, 30);
	glVertex2i(0, 27);
	glVertex2i(10, 30);
	glVertex2i(7, 5);
	glEnd();
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2i(-7, 25);
	glVertex2i(-2, 25);
	glVertex2i(-4.5, 15);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2i(2, 25);
	glVertex2i(7, 25);
	glVertex2i(4.5, 15);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2i(-2, 15);
	glVertex2i(3, 15);
	glVertex2i(0.5, 5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-140.0, 130.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2i(-14, 25);
		glVertex2i(5, 25);
		glVertex2i(-4.5, 15);
	glEnd();
	
	glTranslatef(10.0, -50, 1.0);
	glBegin(GL_POLYGON);
		glVertex2i(-20, 25);
		glVertex2i(0, 25);
		glVertex2i(-15, 30);
		glVertex2i(-20, 30);
	glEnd();

	glTranslatef(5.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2i(-20, 25);
		glVertex2i(0, 25);
		glVertex2i(-15, 30);
		glVertex2i(-20, 30);
	glEnd();
	glPopMatrix();

	glPushMatrix();	
	Pt2D pivot[1];
	pivot[0].x = 0;
	pivot[0].y = 0;
	glTranslatef(-147.0, 155.0, 0.0);
	glColor3f(0.5, 0.5, 0.5);
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
	glScalef(0.5f, 0.5f, 1.0f);
	scalePolygon(myverts2, 11, pivot[0], 0.5, 0.5);
	glColor3f(1.0, 0.0, 0.0);
	circleMidpoint(-13, 14, 2);
	circleMidpoint(22, 14, 2);
	glColor3f(0.0, 1.0, 0.0);
	circleMidpoint(-5, 16, 2);
	circleMidpoint(15, 16, 2);
	glColor3f(0.0, 0.0, 1.0);
	circleMidpoint(4, 20, 3);
	glPopMatrix();

	//Walls
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslatef(-200.0, 0.0, 0.0);
	glRecti(0, 0, 50, 10);
	glTranslatef(25.0, -62.0, 0.0);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRecti(50, 0, 90, 10);
	glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(-33.0, 62.0, 0.0);	
	glRecti(90, 0, 150, 10);
	glRecti(150, 10, 140, 200);
	glPopMatrix();

	//Trees
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	GLubyte bitShape4[72] {
		0x00, 0x18, 0x00,
		0x00, 0x18, 0x00,
		0x00, 0x18, 0x00,
		0x00, 0x18, 0x00,
		0x3F, 0xFF, 0xFC,
		0x1F, 0xFF, 0xF8,
		0x0F, 0xFF, 0xF0,
		0x07, 0xFF, 0xE0,
		0x03, 0xFF, 0xC0,
		0x01, 0xFF, 0x80,
		0x00, 0xFF, 0x00,
		0x00, 0x7E, 0x00,
		0x00, 0x3C, 0x00,
		0x07, 0xFF, 0xE0,
		0x03, 0xFF, 0xC0,
		0x01, 0xFF, 0x80,
		0x00, 0xFF, 0x00,
		0x00, 0x7E, 0x00,
		0x00, 0x3C, 0x00,
		0x01, 0xFF, 0x80,
		0x00, 0xFF, 0x00,
		0x00, 0x7E, 0x00,
		0x00, 0x3C, 0x00,
		0x00, 0x18, 0x00,	
	};
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glRasterPos2i(0, -50);
	glBitmap(24.0, 24.0, 0.0, 0.0, 24.0, 12.0, bitShape4);
	glRasterPos2i(100, -25);
	glBitmap(24.0, 24.0, 0.0, 0.0, 24.0, 12.0, bitShape4);
	glRasterPos2i(-14, 0);
	glBitmap(24.0, 24.0, 0.0, 0.0, 24.0, 12.0, bitShape4);
	glRasterPos2i(55, 23);
	glBitmap(24.0, 24.0, 0.0, 0.0, 24.0, 12.0, bitShape4);
	glRasterPos2i(-70, -150);
	glBitmap(24.0, 24.0, 0.0, 0.0, 24.0, 12.0, bitShape4);
	glRasterPos2i(-150, -70);
	glBitmap(24.0, 24.0, 0.0, 0.0, 24.0, 12.0, bitShape4);
	glRasterPos2i(180, -190);
	glBitmap(24.0, 24.0, 0.0, 0.0, 24.0, 12.0, bitShape4);
	glRasterPos2i(150, 150);
	glBitmap(24.0, 24.0, 0.0, 0.0, 24.0, 12.0, bitShape4);
	glRasterPos2i(175, 75);
	glBitmap(24.0, 24.0, 0.0, 0.0, 24.0, 12.0, bitShape4);
	glRasterPos2i(75, 175);
	glBitmap(24.0, 24.0, 0.0, 0.0, 24.0, 12.0, bitShape4);
	glPopMatrix();

	//Rocks
	glPushMatrix();
	glColor3f(0.5, 0.0, 0.0);
	GLuint regPent;
	GLdouble theta2;
	GLint a, b, i;

	regPent = glGenLists(1);
	glNewList(regPent, GL_COMPILE);
	glBegin(GL_POLYGON);
	for (i = 0; i < 5; i++){
		theta2 = 2 * M_PI * i / 5.0;
		a = 150 + 30 * cos(theta2);
		b = -20 + 30 * sin(theta2);
		glVertex2i(a, b);
	}
	glEnd();
	glEndList();
	glCallList(regPent);
	glTranslatef(-200.0, -70.0, 0.0);
	glColor3f(0.1, 0.0, 0.0);
	glScalef(0.5f, 0.5f, 1.0f);
	glCallList(regPent);
	glPopMatrix();

	//Compass
	glPushMatrix();
	glTranslatef(150.0, 150.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	GLubyte bitShape5[72] {
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
	glBitmap(24.0, 24.0, 0.0, 0.0, 24.0, 12.0, bitShape5);
	circleMidpoint(10, 11, 30);
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(7, 27);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glRasterPos2i(25, 7);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');
	glRasterPos2i(7, -12);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');
	glRasterPos2i(-10, 7);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'W');
	glPopMatrix();

	//Text
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(-150, -10);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 's');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'n');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'n');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'c');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');

	glRasterPos2i(-175, 175);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'Y');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'u');

	glRasterPos2i(-125, -100);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'L');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'R');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'c');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'k');

	glRasterPos2i(110, -50);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'B');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'u');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'd');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ',');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'O');
}
// Generate the Graphics
void displayFcn(void)
{
	Pt2D pivot[1];
	pivot[0].x = 0;
	pivot[0].y = 0;
	// Clear display window.
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);
		glVertex2i(-50, 170);
		glVertex2i(30, 170);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(-50, 175);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'I');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'V');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'T');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'O');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'R');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'Y');

	glColor3f(0.5, 0.5, 0.5);
	glRecti(-130, 115, -30, 95);
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(-125, 100);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'w');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'd');

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(-125, 45);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'w');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 's');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '(');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '9');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '9');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ')');

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(-125, -20);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'h');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'd');

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(-125, -75);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'w');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'n');

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(40, 100);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'm');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(40, 45);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'P');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'n');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 's');

	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(40, -25);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'm');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'p');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 's');
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 's');

	//Sword
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);	
	glTranslatef(-155.0, 100.0, 0.0);
	glRecti(0, 0, 5, 15);
	glRecti(-5, 15, 10, 20);
	glPopMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glPushMatrix();
	glTranslatef(-155.0, 100.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex2i(-2, 20);
		glVertex2i(-2, 40);
		glVertex2i(3, 50);
		glVertex2i(8, 40);
		glVertex2i(8, 20);	
	glEnd();
	glPopMatrix();

	//Arrow
	glPushMatrix();
	glTranslatef(-155.0, 75.0, 0.0);
	Pt2D myverts[7];
	myverts[0].x = 0;
	myverts[0].y = 0;
	myverts[1].x = 30;
	myverts[1].y = -20;
	myverts[2].x = 5;
	myverts[2].y = -20;
	myverts[3].x = 5;
	myverts[3].y = -60;
	myverts[4].x = -5;
	myverts[4].y = -60;
	myverts[5].x = -5;
	myverts[5].y = -20;
	myverts[6].x = -30;
	myverts[6].y = -20;
	glColor3f(0.0, 1.0, 0.0);
	scalePolygon(myverts, 7, pivot[0], 0.5, 0.5);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2i(2, -25);
		glVertex2i(7, -30);
		glVertex2i(2, -20);
		glVertex2i(7, -25);
		glVertex2i(-3, -25);
		glVertex2i(-8, -30);
		glVertex2i(-3, -20);
		glVertex2i(-8, -25);
	glEnd();
	glPopMatrix();

	//Shield
	glPushMatrix();
	glTranslatef(-155.0, -25.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex2i(0, 0);
		glVertex2i(-7, 5);
		glVertex2i(-10, 30);
		glVertex2i(0, 27);
		glVertex2i(10, 30);
		glVertex2i(7, 5);
	glEnd();
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON); 
		glVertex2i(-7, 25);
		glVertex2i(-2, 25);
		glVertex2i(-4.5, 15);
	glEnd();	
	glBegin(GL_POLYGON);
		glVertex2i(2, 25);
		glVertex2i(7, 25);
		glVertex2i(4.5, 15);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2i(-2, 15);
		glVertex2i(3, 15);
		glVertex2i(0.5, 5);
	glEnd();
	glPopMatrix();

	//Crown
	glPushMatrix();
	glTranslatef(-155.0, -75.0, 0.0);
	glColor3f(0.5, 0.5, 0.5);
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
	scalePolygon(myverts2, 11, pivot[0], 0.5, 0.5);
	glColor3f(1.0, 0.0, 0.0);
	circleMidpoint(-13, 14, 2);
	circleMidpoint(22, 14, 2);
	glColor3f(0.0, 1.0, 0.0);
	circleMidpoint(-5, 16, 2);
	circleMidpoint(15, 16, 2);
	glColor3f(0.0, 0.0, 1.0);
	circleMidpoint(4, 20, 3);
	glPopMatrix();
	
	//Armor
	glPushMatrix();
	glTranslatef(0.0, 110.0, 0.0);
	glColor3f(0.5, 0.5, 0.5);
	glRecti(0, 0, 12, 22);
	glColor3f(1.0, 1.0, 0.0);
	glRecti(0, 5, 12, 10);
	glColor3f(0.0, 1.0, 1.0);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRecti(15, 10, 0, 15);
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	glRecti(-5, 23, 10, 18);
	glPopMatrix();

	//Pants
	glPushMatrix();
	glTranslatef(0.0, 45.0, 0.0);
	glColor3f(0.5, 0.5, 0.5);
	glRecti(0, 0, 12, 22);
	glColor3f(1.0, 1.0, 0.0);
	glRecti(0, 18, 12, 20);
	glColor3f(1.0, 1.0, 1.0);
	glRecti(4, 0, 8, 12);
	glPopMatrix();

	//Compass
	glPushMatrix();
	glTranslatef(-5.0, -25.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
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
	circleMidpoint(10, 11, 30);

	//N, S, E, W Text glutBitmapCharacter(GLUT_BITMAP_9_BY_15,'U');
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(7, 27);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
	glRasterPos2i(25, 7);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'E');
	glRasterPos2i(7, -12);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'S');
	glRasterPos2i(-10, 7);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'W');
	glPopMatrix();

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
	pause = glutCreateWindow("Pause Menu");
	glutInitWindowPosition(500, 100);
	inventory = glutCreateWindow("Inventory");
	glutInitWindowPosition(900, 100);
	map = glutCreateWindow("Map");

	glutSetWindow(inventory);

	// Initialize Inventory
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutSetWindow(pause);

	// Initialize Pause
	init();
	// Display function call
	glutDisplayFunc(pauseCode);
	// Window reshape call
	glutReshapeFunc(winReshapeFcn);
	glutSetWindow(map);

	//Initalize Map
	init();
	glutDisplayFunc(mapCode);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}