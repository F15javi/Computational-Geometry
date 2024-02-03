// Sample code for Übung 2

#include "vec.h"
#include "mat.h"
#include <iostream>
#include <math.h>

// might be you have to swith to
// #include "glut.h" depending on your GLUT installation
#include "Uebung2/Uebung2/glut.h"

////////////////////////////////////////////////////////////
//
// system relevant global variables
//
int g_WinWidth = 1000;
int g_WinHeight = 1000;
// window width and height (choose an appropriate size)
const int g_iWidth  = 400;
const int g_iHeight = 400;

// global variable to tune the timer interval
int g_iTimerMSecs;
/////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// private, global variables ... replace by your own ones
//
// some global state variables used to describe ...
float g_iPos;		// ... position and ...
float g_iPosIncr;	// ... position increment (used in display1)

CVec2i g_vecPos;		// same as above but in vector form ...
CVec2i g_vecPosIncr;	// (used in display2)
//
/////////////////////////////////////////////////////////////
float fFocus = -50;


CVec4f Cube1[8];
CVec4f Cube2[8];
CVec4f Cube3[8];

CVec4f ViewOrigin;
CVec4f ViewDir;
CVec4f ViewUp;
CVec4f pWorld;


/////////////////////////////////////////////////////////////
class Point {
public:

	Point(int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}

	int x, y;
};



// Una clase de color muy primitiva
class Color {
public:

	Color(float r = 1.0f, float g = 1.0f, float b = 1.0f) {
		this->r = r;
		this->g = g;
		this->b = b;
	}

	float r, g, b;
};
void reshape(int w, int h)
{

	g_WinWidth = w;
	g_WinHeight = h;
	glViewport(0, 0, w, h);					// Establish viewing area to cover entire window.

	glMatrixMode(GL_PROJECTION);			// Start modifying the projection matrix.
	glLoadIdentity();						// Reset project matrix.
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, 0, 1);	// Map abstract coords directly to window coords.

	glutPostRedisplay();
}
// function to initialize our own variables
void init () 
{

	// init timer interval
	g_iTimerMSecs = 10;

	// init variables for display1
	g_iPos     = 0;
	g_iPosIncr = 2;

	// init variables for display2
	int aiPos    [2] = {0, 0};
	int aiPosIncr[2] = {2, 2};
	g_vecPos.setData (aiPos);
	g_vecPosIncr.setData (aiPosIncr);
}

// function to initialize the view to ortho-projection
void initGL () 
{

	glViewport (0, 0, g_iWidth, g_iHeight);	// Establish viewing area to cover entire window.

	glMatrixMode (GL_PROJECTION);			// Start modifying the projection matrix.
	glLoadIdentity ();						// Reset project matrix.
	glOrtho (-g_iWidth/2, g_iWidth/2, -g_iHeight/2, g_iHeight/2, 0, 1);	// Map abstract coords directly to window coords.

	// tell GL that we draw to the back buffer and
	// swap buffers when image is ready to avoid flickering
	glDrawBuffer (GL_BACK);

	// tell which color to use to clear image
	glClearColor (0,0,0,1);
}
void resize() {

	
	glutInitWindowSize(g_WinWidth, g_WinHeight);
	glutCreateWindow("Universe Sandbox");

	glutReshapeFunc(reshape);

}

int min (int a, int b) { return a>b? a: b; }
// timer callback function
void timer (int value) 
{
	///////
	// update your variables here ...
	//

	int size2 = min (g_iWidth, g_iHeight) / 2;

	// variables for display1 ...
	if (g_iPos<=-size2 || g_iPos>=size2) g_iPosIncr = -g_iPosIncr;
	g_iPos += g_iPosIncr;

	// variables for display2 ...
	if (g_vecPos(1)<=-size2 || g_vecPos(1)>=size2) g_vecPosIncr = -g_vecPosIncr; 
	g_vecPos += g_vecPosIncr;

	//
	///////

	// the last two lines should always be
	glutPostRedisplay ();
	glutTimerFunc (g_iTimerMSecs, timer, 0);	// call timer for next iteration
}
void bhamLine(Point p1, Point p2, Color c)

{
	glBegin(GL_POINTS);
	glColor3f(c.r, c.g, c.b);
	Point center(0, 0);
	Color cGren(0, 1, 0);
	//	setPoint(center, cGren);

	int x1, y1, x2, y2, dx, dy, D, dNE, dE, xAux, yAux; // var declaration
	int sel = 1;





	x1 = p1.x; y1 = p1.y; // Set (x,y) with the values of p1
	x2 = p2.x; y2 = p2.y; // Set (x,y) with the values of p2
	//printf("Point 1: %d,%d \n", x1, y1);
	//printf("Point 2: %d,%d \n", x2, y2);
	x2 = x2 - x1; y2 = y2 - y1;	// Move p2 to the new position 
	x1 = 0; y1 = 0;				// Set p1 in the x,y axis 

	//printf("Point 3: %d,%d \n", x2, y2);





	dx = x2 - x1; dy = y2 - y1; // Set the delta of x and y

	double r = (double)dy / dx;

	//check the slope of the line, to know in which octant is the line, and translate p2 to to the 1º octant
	if (0 <= r && r <= 1) {
		if (x1 < x2) {	//1º octant
			dx = x2 - x1; dy = y2 - y1; // Set the delta of x and y
			sel = 1;
			printf("octant 1 \n");
		}
		else {			//5º octant
			x2 = -x2;
			y2 = -y2;
			dx = x2 - x1; dy = y2 - y1; // Set the delta of x and y
			sel = 5;
			printf("octant 5 \n");

		}
	}
	else if (0 >= r && r >= -1) {
		if (x2 < x1) {	//4º octant
			x2 = -x2;
			dx = x2 - x1; dy = y2 - y1; // Set the delta of x and y
			sel = 4;
			printf("octant 4 \n");

		}
		else {			//8º octant
			y2 = -y2;
			dx = x2 - x1; dy = y2 - y1; // Set the delta of x and y
			sel = 8;
			printf("octant 8 \n");

		}
	}
	else if (r > 1) {
		if (y1 < y2) {	//2º octant
			xAux = x2;
			x2 = y2;
			y2 = xAux;
			dx = x2 - x1; dy = y2 - y1; // Set the delta of x and y
			sel = 2;
			printf("octant 2 \n");

		}
		else {			//6º octant
			xAux = x2;
			x2 = -y2;
			y2 = -xAux;
			dx = x2 - x1; dy = y2 - y1; // Set the delta of x and y
			sel = 6;
			printf("octant 6 \n");

		}
	}
	else if (r < -1) {
		if (y1 < y2) {	//3º octant
			xAux = x2;
			x2 = y2;
			y2 = -xAux;
			dx = x2 - x1; dy = y2 - y1; // Set the delta of x and y
			sel = 3;
			printf("octant 3 \n");

		}
		else {			//7º octant

			xAux = x2;
			x2 = -y2;
			y2 = xAux;


			dx = x2 - x1; dy = y2 - y1; // Set the delta of x and y
			sel = 7;
			printf("octant 7 \n");
		}
	}

	dNE = 2 * (dy - dx); dE = 2 * dy;// Set the delta on NE and E
	D = 2 * dy - dx;

	// primer punto
	glVertex2i(p1.x, p1.y);

	//bresenham's Algorithm
	while (x1 < x2) {
		if (D >= 0) {
			D += dNE;
			x1++;
			y1++;
		}
		else {
			D += dE;
			x1++;

		}
		printf("The point in the first octant %d,%d \n", x1, y1);

		//
		switch (sel) {
			int aux;
		case 1: //if the line was in the 1º octant do nothing, in other case reverse the operation from before
			xAux = x1;
			yAux = y1;
			break;

		case 2:
			aux = x1;
			xAux = y1;
			yAux = aux;
			break;
		case 3:
			aux = y1;
			xAux = -aux;
			yAux = x1;

			break;
		case 4:
			xAux = -x1;
			yAux = y1;
			break;
		case 5:
			xAux = -x1;
			yAux = -y1;
			break;
		case 6:

			aux = x1;
			xAux = -y1;
			yAux = -aux;

			break;
		case 7:
			aux = x1;
			xAux = y1;
			yAux = -aux;
			break;
		case 8:
			xAux = x1;
			yAux = -y1;
			break;
		}
		xAux = xAux + p1.x;
		yAux = yAux + p1.y;

		Point pbham(xAux, yAux);
		glVertex2i(pbham.x, pbham.y);
		printf("El punto final %d,%d \n", pbham.x, pbham.y);
	}

	// ultimo punto
	glVertex2i(p2.x, p2.y);


	glEnd();

}
void bhamCircle(Point p, int r, Color c) {

	// Enfoque
	glBegin(GL_POINTS);
	glColor3f(c.r, c.g, c.b);

	glVertex2i(p.x, p.y);

	int x, y, d, dSE, dE, dx, dy;
	x = 0; y = r;
	d = 5 - 4 * r;

	//Circle Symmetry

	Point cSym1(x + p.x, y + p.y);
	glVertex2i(cSym1.x, cSym1.y);

	Point cSym2(y + p.x, x + p.y);
	glVertex2i(cSym2.x, cSym2.y);

	Point cSym3(-y + p.x, x + p.y);
	glVertex2i(cSym3.x, cSym3.y);

	Point cSym4(x + p.x, -y + p.y);
	glVertex2i(cSym4.x, cSym4.y);




	//bresenham's Algorithm
	while (y > x) {
		if (d >= 0) {// SE
			dSE = 4 * (2 * (x - y) + 5);
			d += dSE;
			x++;
			y--;
		}
		else { // E
			dE = 4 * (2 * x + 3);
			d += dE;
			x++;
		}




		// Symmetry, we move the circle from (0,0) to the point p
		Point cPoint1(x + p.x, y + p.y);
		glVertex2i(cPoint1.x, cPoint1.y);

		Point cPoint2(y + p.x, x + p.y);
		glVertex2i(cPoint2.x, cPoint2.y);

		Point cPoint3(-y + p.x, x + p.y);
		glVertex2i(cPoint3.x, cPoint3.y);

		Point cPoint4(-x + p.x, y + p.y);
		glVertex2i(cPoint4.x, cPoint4.y);

		Point cPoint5(-x + p.x, -y + p.y);
		glVertex2i(cPoint5.x, cPoint5.y);

		Point cPoint6(-y + p.x, -x + p.y);
		glVertex2i(cPoint6.x, cPoint6.y);

		Point cPoint7(y + p.x, -x + p.y);
		glVertex2i(cPoint7.x, cPoint7.y);

		Point cPoint8(x + p.x, -y + p.y);
		glVertex2i(cPoint8.x, cPoint8.y);
	}

	glEnd();

}
Point rotation(Point orbiter, Point r_axis, float r_speed) {
	int dx, dy;
	Point res;
	dx = cos(r_speed) * (orbiter.x - r_axis.x) - sin(r_speed) * (orbiter.y - r_axis.y)+r_axis.x;
	dy = sin(r_speed) * (orbiter.x - r_axis.x) + cos(r_speed) * (orbiter.y - r_axis.y)+r_axis.y;
	res.x = dx;
	res.y = dy;
	return res;

}
CMat3f matrix_rotation(CMat3f orbiter, CMat3f r_axis, float r_speed) {

	CMat3f angle;
	CMat3f Nr_axis;
	CMat3f Res;

	float a[3][3] = { {cos(r_speed),-sin(r_speed),0},{sin(r_speed),cos(r_speed),0},{0,0,1} };// Cos and Sin matrix operation
	angle.setData(a);

	float Nr[3][3] = { {1,0,-r_axis.operator()(0,2)} ,{0,1,-r_axis.operator()(1,2)},{0,0,1} };//Negation of the axis coordinates
	Nr_axis.setData(Nr);

	//Matix multiplication
	Res = r_axis.operator*(angle).operator*(Nr_axis).operator*(orbiter);


	/*Res = r_axis.operator*(angle);
	printf("%f,%f \n", Res.operator()(0, 2), Res.operator()(1, 2));

	Res = Res.operator*(Nr_axis);
	printf("%f,%f \n", Res.operator()(0, 2), Res.operator()(1, 2));

	Res = Res.operator*(orbiter);
	printf("%f,%f \n", Res.operator()(0, 2), Res.operator()(1, 2));*/

	
	return Res;






	
}
CVec4f prodVec(CVec4f ViewDir, CVec4f ViewUp){
	//Vectorial Product
	CVec4f res;
	res(0) = ViewDir(1) * ViewUp(2) - ViewDir(2) * ViewUp(1);
	res(1) = -(ViewDir(0) * ViewUp(2) - ViewDir(2) * ViewUp(0));
	res(2) = ViewDir(0) * ViewUp(1) - ViewDir(1) * ViewUp(0);
	res(3) = 0;
	return res;
}
CMat4f ProjectMat(float fFocus) {

	
	CMat4f Pro;
	Pro(0, 0) = 1;	
	Pro(0, 1) = 0;
	Pro(0, 2) = 0;
	Pro(0, 3) = 0;
	Pro(1, 0) = 0;
	Pro(1, 1) = 1;
	Pro(1, 2) = 0;
	Pro(1, 3) = 0;
	Pro(2, 0) = 0;
	Pro(2, 1) = 0;
	Pro(2, 2) = 0;
	Pro(2, 3) = 0;
	Pro(3, 0) = 0;
	Pro(3, 1) = 0;
	Pro(3, 2) = -(1/fFocus);
	Pro(3, 3) = 1;

	

	return Pro;
}

CVec4f projectZ(float fFocus, CVec4f pView) {
	CVec4f res;
	res = ProjectMat(fFocus)* pView;
	res(0) = res(0) / res(3);
	res(1) = res(1) / res(3);
	res(2) = res(2) / res(3);
	res(3) = res(3) / res(3);

	return res;
}
void drawQuader(CVec4f Cube[8], float fFocus, Color c) {

	CVec4f Points[8];

	for (int i = 0; i < 8; i++) {

		Points[i] = projectZ(fFocus, Cube[i]);
	}




	glBegin(GL_LINE_LOOP); // Draw the frontal square
	glColor3f(c.r, c.g, c.b);
	glVertex2f(Points[0](0), Points[0](1));
	glVertex2f(Points[1](0), Points[1](1));
	glVertex2f(Points[2](0), Points[2](1));
	glVertex2f(Points[3](0), Points[3](1));
	glEnd();

	glBegin(GL_LINE_LOOP); // Draw the back square
	glColor3f(c.r, c.g, c.b);
	glVertex2f(Points[4](0), Points[4](1));
	glVertex2f(Points[5](0), Points[5](1));
	glVertex2f(Points[6](0), Points[6](1));
	glVertex2f(Points[7](0), Points[7](1));
	glEnd();

	glBegin(GL_LINES);// Draw the conections between the 2 squares to create the cube
	glColor3f(c.r, c.g, c.b);
	glVertex2f(Points[0](0), Points[0](1));
	glVertex2f(Points[4](0), Points[4](1));

	glVertex2f(Points[1](0), Points[1](1));
	glVertex2f(Points[5](0), Points[5](1));

	glVertex2f(Points[2](0), Points[2](1));
	glVertex2f(Points[6](0), Points[6](1));

	glVertex2f(Points[3](0), Points[3](1));
	glVertex2f(Points[7](0), Points[7](1));
	glEnd();


}
CMat4f getTransform(CVec4f ViewOrigin, CVec4f ViewDir, CVec4f ViewUp) {
	CVec4f ViewLeft = prodVec(ViewDir, ViewUp);


	CMat3f Rt;
	CVec3f VO;
	VO(0) = ViewOrigin(0);
	VO(1) = ViewOrigin(1);
	VO(2) = ViewOrigin(2);


	Rt(0, 0) = ViewDir(0);	Rt(1, 0) = ViewUp(0);	Rt(2, 0) = ViewLeft(0);		
	Rt(0, 1) = ViewDir(1);	Rt(1, 1) = ViewUp(1);	Rt(2, 1) = ViewLeft(1);		
	Rt(0, 2) = ViewDir(2);	Rt(1, 2) = ViewUp(2);	Rt(2, 2) = ViewLeft(2);

	CVec3f mul = Rt * VO;

	CMat4f matRot;

	matRot(0, 0) = ViewDir(0);	matRot(1, 0) = ViewUp(0);	matRot(2, 0) = ViewLeft(0);		matRot(3, 0) = mul(0);
	matRot(0, 1) = ViewDir(1);	matRot(1, 1) = ViewUp(1);	matRot(2, 1) = ViewLeft(1);		matRot(3, 1) = mul(1);
	matRot(0, 2) = ViewDir(2);	matRot(1, 2) = ViewUp(2);	matRot(2, 2) = ViewLeft(2);		matRot(3, 2) = mul(2);
	matRot(0, 3) = 0;			matRot(1, 3) = 0;			matRot(2, 3) = 0;				matRot(3, 3) = 1;
	
	
	return matRot;
}

void projectZallg(CMat4f matTransf, float fFocus, CVec4f Cube[8], Color c) {

	//World to camera


	CVec4f Points[8];

	for (int i = 0; i < 8; i++) {
		CVec4f pView = matTransf * Cube[i];

		Points[i] = projectZ(fFocus, pView);
	}




	glBegin(GL_LINE_LOOP); // Draw the frontal square
	glColor3f(c.r, c.g, c.b);
	glVertex2f(Points[0](0), Points[0](1));
	glVertex2f(Points[1](0), Points[1](1));
	glVertex2f(Points[2](0), Points[2](1));
	glVertex2f(Points[3](0), Points[3](1));
	glEnd();

	glBegin(GL_LINE_LOOP); // Draw the back square
	glColor3f(c.r, c.g, c.b);
	glVertex2f(Points[4](0), Points[4](1));
	glVertex2f(Points[5](0), Points[5](1));
	glVertex2f(Points[6](0), Points[6](1));
	glVertex2f(Points[7](0), Points[7](1));
	glEnd();

	glBegin(GL_LINES);// Draw the conections between the 2 squares to create the cube
	glColor3f(c.r, c.g, c.b);
	glVertex2f(Points[0](0), Points[0](1));
	glVertex2f(Points[4](0), Points[4](1));

	glVertex2f(Points[1](0), Points[1](1));
	glVertex2f(Points[5](0), Points[5](1));

	glVertex2f(Points[2](0), Points[2](1));
	glVertex2f(Points[6](0), Points[6](1));

	glVertex2f(Points[3](0), Points[3](1));
	glVertex2f(Points[7](0), Points[7](1));
	glEnd();
}
// display callback function
void display1(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	Color c1(1, 0, 0);
	Color c2(0, 1, 0);
	Color c3(0, 0, 1);

	CVec4f Cube1[8];
	CVec4f Cube2[8];
	CVec4f Cube3[8];


	Cube1[0](0) = 20; Cube1[0](1) = 20; Cube1[0](2) = 10; Cube1[0](3) = 1;
	Cube1[1](0) = 20; Cube1[1](1) = -20; Cube1[1](2) = 10; Cube1[1](3) = 1;
	Cube1[2](0) = -20; Cube1[2](1) = -20; Cube1[2](2) = 10; Cube1[2](3) = 1;
	Cube1[3](0) = -20; Cube1[3](1) = 20; Cube1[3](2) = 10; Cube1[3](3) = 1;
	Cube1[4](0) = 20; Cube1[4](1) = 20; Cube1[4](2) = -10; Cube1[4](3) = 1;
	Cube1[5](0) = 20; Cube1[5](1) = -20; Cube1[5](2) = -10; Cube1[5](3) = 1;
	Cube1[6](0) = -20; Cube1[6](1) = -20; Cube1[6](2) = -10; Cube1[6](3) = 1;
	Cube1[7](0) = -20; Cube1[7](1) = 20; Cube1[7](2) = -10; Cube1[7](3) = 1;

	Cube2[0](0) = 50; Cube2[0](1) = 70; Cube2[0](2) = 10; Cube2[0](3) = 1;
	Cube2[1](0) = 50; Cube2[1](1) = 50; Cube2[1](2) = 10; Cube2[1](3) = 1;
	Cube2[2](0) = 30; Cube2[2](1) = 50; Cube2[2](2) = 10; Cube2[2](3) = 1;
	Cube2[3](0) = 30; Cube2[3](1) = 70; Cube2[3](2) = 10; Cube2[3](3) = 1;
	Cube2[4](0) = 50; Cube2[4](1) = 70; Cube2[4](2) = -10; Cube2[4](3) = 1;
	Cube2[5](0) = 50; Cube2[5](1) = 50; Cube2[5](2) = -10; Cube2[5](3) = 1;
	Cube2[6](0) = 30; Cube2[6](1) = 50; Cube2[6](2) = -10; Cube2[6](3) = 1;
	Cube2[7](0) = 30; Cube2[7](1) = 70; Cube2[7](2) = -10; Cube2[7](3) = 1;

	Cube3[0](0) = 0; Cube3[0](1) = 20; Cube3[0](2) = 0; Cube3[0](3) = 1;
	Cube3[1](0) = 0; Cube3[1](1) = 0; Cube3[1](2) = 0; Cube3[1](3) = 1;
	Cube3[2](0) = -20; Cube3[2](1) = 0; Cube3[2](2) = 0; Cube3[2](3) = 1;
	Cube3[3](0) = -20; Cube3[3](1) = 20; Cube3[3](2) = 0; Cube3[3](3) = 1;
	Cube3[4](0) = 0; Cube3[4](1) = 20; Cube3[4](2) = -20; Cube3[4](3) = 1;
	Cube3[5](0) = 0; Cube3[5](1) = 0; Cube3[5](2) = -20; Cube3[5](3) = 1;
	Cube3[6](0) = -20; Cube3[6](1) = 0; Cube3[6](2) = -20; Cube3[6](3) = 1;
	Cube3[7](0) = -20; Cube3[7](1) = 20; Cube3[7](2) = -20; Cube3[7](3) = 1;

	CVec4f ViewOrigin;
	ViewOrigin(0) = 0;
	ViewOrigin(1) = 0;
	ViewOrigin(2) = 0;
	ViewOrigin(3) = 1;
	CVec4f ViewDir;
	ViewDir(0) = -1;
	ViewDir(1) = 0;
	ViewDir(2) = 0;
	ViewDir(3) = 1;
	CVec4f ViewUp;
	ViewUp(0) = 0;
	ViewUp(1) = 1;
	ViewUp(2) = 0;
	ViewUp(3) = 1;
	CVec4f pWorld;
	pWorld(0) = 20;
	pWorld(1) = 15;
	pWorld(2) = 16;
	pWorld(3) = 1;

	drawQuader(Cube1, fFocus, c1);
	drawQuader(Cube2, fFocus, c2);
	drawQuader(Cube3, fFocus, c3);


	// In double buffer mode the last
	// two lines should alsways be
	glFlush();
	glutSwapBuffers(); // swap front and back buffer
	
}
void display2(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	Color c1(1, 0, 0);
	Color c2(0, 1, 0);
	Color c3(0, 0, 1);
	int i = 0;
	if (i == 0) {

		Cube1[0](0) = 20; Cube1[0](1) = 20; Cube1[0](2) = 10; Cube1[0](3) = 1;
		Cube1[1](0) = 20; Cube1[1](1) = -20; Cube1[1](2) = 10; Cube1[1](3) = 1;
		Cube1[2](0) = -20; Cube1[2](1) = -20; Cube1[2](2) = 10; Cube1[2](3) = 1;
		Cube1[3](0) = -20; Cube1[3](1) = 20; Cube1[3](2) = 10; Cube1[3](3) = 1;
		Cube1[4](0) = 20; Cube1[4](1) = 20; Cube1[4](2) = -10; Cube1[4](3) = 1;
		Cube1[5](0) = 20; Cube1[5](1) = -20; Cube1[5](2) = -10; Cube1[5](3) = 1;
		Cube1[6](0) = -20; Cube1[6](1) = -20; Cube1[6](2) = -10; Cube1[6](3) = 1;
		Cube1[7](0) = -20; Cube1[7](1) = 20; Cube1[7](2) = -10; Cube1[7](3) = 1;

		Cube2[0](0) = 50; Cube2[0](1) = 70; Cube2[0](2) = 10; Cube2[0](3) = 1;
		Cube2[1](0) = 50; Cube2[1](1) = 50; Cube2[1](2) = 10; Cube2[1](3) = 1;
		Cube2[2](0) = 30; Cube2[2](1) = 50; Cube2[2](2) = 10; Cube2[2](3) = 1;
		Cube2[3](0) = 30; Cube2[3](1) = 70; Cube2[3](2) = 10; Cube2[3](3) = 1;
		Cube2[4](0) = 50; Cube2[4](1) = 70; Cube2[4](2) = -10; Cube2[4](3) = 1;
		Cube2[5](0) = 50; Cube2[5](1) = 50; Cube2[5](2) = -10; Cube2[5](3) = 1;
		Cube2[6](0) = 30; Cube2[6](1) = 50; Cube2[6](2) = -10; Cube2[6](3) = 1;
		Cube2[7](0) = 30; Cube2[7](1) = 70; Cube2[7](2) = -10; Cube2[7](3) = 1;

		Cube3[0](0) = 0; Cube3[0](1) = 20; Cube3[0](2) = 0; Cube3[0](3) = 1;
		Cube3[1](0) = 0; Cube3[1](1) = 0; Cube3[1](2) = 0; Cube3[1](3) = 1;
		Cube3[2](0) = -20; Cube3[2](1) = 0; Cube3[2](2) = 0; Cube3[2](3) = 1;
		Cube3[3](0) = -20; Cube3[3](1) = 20; Cube3[3](2) = 0; Cube3[3](3) = 1;
		Cube3[4](0) = 0; Cube3[4](1) = 20; Cube3[4](2) = -20; Cube3[4](3) = 1;
		Cube3[5](0) = 0; Cube3[5](1) = 0; Cube3[5](2) = -20; Cube3[5](3) = 1;
		Cube3[6](0) = -20; Cube3[6](1) = 0; Cube3[6](2) = -20; Cube3[6](3) = 1;
		Cube3[7](0) = -20; Cube3[7](1) = 20; Cube3[7](2) = -20; Cube3[7](3) = 1;

		ViewOrigin(0) = 0;
		ViewOrigin(1) = 0;
		ViewOrigin(2) = 0;
		ViewOrigin(3) = 1;
		ViewDir(0) = -1;
		ViewDir(1) = 0;
		ViewDir(2) = 0;
		ViewDir(3) = 1;
		ViewUp(0) = 0;
		ViewUp(1) = 1;
		ViewUp(2) = 0;
		ViewUp(3) = 1;
		pWorld(0) = 20;
		pWorld(1) = 15;
		pWorld(2) = 16;
		pWorld(3) = 1;
		i++;
	}

	CMat4f matTransf = getTransform(ViewOrigin, ViewDir, ViewUp);

	projectZallg(matTransf, fFocus, Cube1, c1);
	projectZallg(matTransf, fFocus, Cube2, c2);
	projectZallg(matTransf, fFocus, Cube3, c3);

	// In double buffer mode the last
	// two lines should alsways be
	glFlush();
	glutSwapBuffers(); // swap front and back buffer
}

void keyboard (unsigned char key, int x, int y) 
{
	switch (key) {
		case 'q':
		case 'Q':
			exit (0); // quit program
			break;
		case '1':
			glutDisplayFunc (display1);
			//glutPostRedisplay ();	// not needed since timer triggers redisplay
			printf("Display1");
			break;
		case '2':
			glutDisplayFunc (display2);
			//glutPostRedisplay ();	// not needed since timer triggers redisplay
			printf("Display2");

			break;
		case 'f':
			fFocus++;

			break;
		case 'F':
			fFocus--;

			break;
		case 'X':
			fFocus--;

			break;
		case 'Y':
			fFocus--;

			break;
		case 'Z':
			fFocus--;

			break;
		case 'R':
			fFocus = -50;

			break;
		default:
			// do nothing ...
			break;
	};
}




int main (int argc, char **argv) 
{
	glutInit (&argc, argv);
	// we have to use double buffer to avoid flickering
	// TODO: lookup "double buffer", what is it for, how is it used ...
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

	init ();	// init my variables first
	initGL ();	// init the GL (i.e. view settings, ...)
	resize();
	// assign callbacks
	glutTimerFunc (10, timer, 0);
	glutKeyboardFunc (keyboard);
	glutDisplayFunc (display2);
	
	// you might want to add a resize function analog to
	// Übung1 using code similar to the initGL function ...

	// start main loop
	glutMainLoop ();

	return 0;
}
