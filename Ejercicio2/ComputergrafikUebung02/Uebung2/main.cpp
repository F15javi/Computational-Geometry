// Sample code for Übung 2

#include "vec.h"
#include "mat.h"
#include <iostream>

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
float Earth_speed = 0;
float Moon_speed = 0;

//
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

// display callback function
void display1 (void) 
{
	if (Earth_speed >= 359) {
		Earth_speed = 0;
	}
	if (Moon_speed >= 359) {
		Moon_speed = 0;
	}
	

	glClear (GL_COLOR_BUFFER_BIT);

	
	Color cSun(1, 0, 0);
	Color cEarth(0, 1, 0);					
	Color cMoon(1, 1, 1);
// Debería ser una línea recta roja...
	//bhamLine(p1, p2, cRed);
	Point Sun(0, 0);				
	int rS = 100;

	Point Earth(270 , 0);		
	int rE = 50;

	int rM = 20;
	bhamCircle(Sun, rS, cSun);

	Earth = rotation(Earth, Sun, Earth_speed += 0.005);
	printf("Tierra: %d,%d \n", Earth.x, Earth.y);

	Point Moon(Earth.x+100, Earth.y);
	printf("Moon: %d,%d \n", Moon.x, Moon.y);

	bhamCircle(Earth, rE, cEarth);
	bhamCircle(rotation(Moon, Earth, Moon_speed += 0.05), rM, cMoon);
	


	//
	///////

	// In double buffer mode the last
	// two lines should alsways be
	glFlush ();
	glutSwapBuffers (); // swap front and back buffer
}

// display callback function
void display2 (void) 
{
	glClear (GL_COLOR_BUFFER_BIT);

	if (Earth_speed >= 359) {
		Earth_speed = 0;
	}
	if (Moon_speed >= 359) {
		Moon_speed = 0;
	}


	Color cSun(1, 0, 0);
	Color cEarth(0, 1, 0);
	Color cMoon(1, 1, 1);
	// Debería ser una línea recta roja...
		//bhamLine(p1, p2, cRed);
	
	CMat3f Sun;
	CMat3f Earth;
	CMat3f Moon;


	float s[3][3] = { {1,0,0},{0,1,0},{0,0,1} };
	Sun.setData(s);

	float e[3][3] = { {1,0,270},{0,1,0},{0,0,1} };
	Earth.setData(e);

	

	int rS = 100;
	int rE = 50;
	int rM = 20;

	Point SunP;
	SunP.x = Sun.operator()(0, 2);
	SunP.y = Sun.operator()(1, 2);
	bhamCircle(SunP, rS, cSun);


	Earth = matrix_rotation(Earth, Sun, Earth_speed += 0.005);
	Point EarthP(Earth.operator()(0, 2), Earth.operator()(1, 2));
	
	bhamCircle(EarthP, rE, cEarth);
	printf("Tierra: %d,%d \n", EarthP.x, EarthP.y);

	
	float m[3][3] = { {1,0,EarthP.x + 100},{0,1,EarthP.y},{0,0,1} };
	Moon.setData(m);

	Moon = matrix_rotation(Moon, Earth, Moon_speed += 0.05);
	Point MoonP(Moon.operator()(0, 2), Moon.operator()(1, 2));
	
	bhamCircle(MoonP, rM, cMoon);
	printf("Moon: %d,%d \n", MoonP.x, MoonP.y);

	

	

	// In double buffer mode the last
	// two lines should alsways be
	glFlush ();
	glutSwapBuffers (); // swap front and back buffer
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
