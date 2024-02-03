///////////////////////////////////////////////// // ////////////////////
// //
// Estructura de código para gráficos de computadora de conferencias WS 2022/23 ejercicio 1 //
// //
///////////////////////////////////////////////// // ////////////////////


// Incluir archivo para entrada/salida de texto
#include <iostream>
using namespace std;


// Incluir archivo para la biblioteca GLUT
#include "glut.h"



///////////////////////////////////////////////// // /////////////////////////////////////
//
// Algunas cosas se inicializan aquí. Le invitamos a mirar el código y
// tratar de entenderlo. Eso no debería ser demasiado difícil para ti. Va a
// pero usa algunas técnicas (texturas, ...) que veremos en la lección
// no hemos discutido, pero nosotros de techn. razones necesitan aquí.
//
// Hay una nota debajo, pero desde aquí puedes leer el código completo
// debería entender!!!


// Resoluciones de toda la textura
// !!!¡¡¡PELIGRO!!! ¡No todas las resoluciones de textura funcionan!
// Palabra clave aproximadamente: problema POT2
#define TEX_RES_X 120
#define TEX_RES_Y 120
// Número de píxeles en la textura
#define TEX_RES TEX_RES_X*TEX_RES_Y
// longitud del eje de textura (los ejes son asimétricos desde -Tex Res#/2 hasta Tes Res#/2-1)
#define TEX_HALF_X TEX_RES_X/2
#define TEX_HALF_Y TEX_RES_Y/2
// Convertir índices de coordenadas (x,y) a una matriz lineal
#define TO_LINEAR(x, y) (((x)) + TEX_RES_X*((y)))

// memoria global para datos de textura
char g_Buffer[3 * TEX_RES];
// Textura ID Name
GLuint g_TexID = 0;

// resolución de la ventana principal (puede cambiar por usuario)
int g_WinWidth = 800;
int g_WinHeight = 800;

// función organiza la textura.
// No te molestes con esta función, ya que
// ¡ella es solo un mal necesario en este momento!
void manageTexture()
{
	glEnable(GL_TEXTURE_2D);
	if (g_TexID == 0) glGenTextures(1, &g_TexID);
	glBindTexture(GL_TEXTURE_2D, g_TexID);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEX_RES_X, TEX_RES_Y, 0, GL_RGB, GL_UNSIGNED_BYTE, g_Buffer);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

// Función de devolución de llamada para ajustar el tamaño de la ventana.
// ¡Esta función también es un mal necesario! Cuidar de
// no te preocupes por eso por ahora.
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


//
//
/////////////////////////////////////////////////////////////////////////////////////////
//
// Aquí es donde comienza la parte del programa que es realmente relevante para ti.
//


// Una clase de punto muy primitiva
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

// La función limpia la pantalla con el color especificado
// Uso, por ejemplo: Imagen clara (Color (1,1,1))
// borra la pantalla en blanco.
// Si no se especifica ningún color, el valor predeterminado es blanco
void clearImage(Color c = Color()) {
	for (int i = 0; i < TEX_RES; i++) {
		g_Buffer[3 * i] = 255.0 * c.r;
		g_Buffer[3 * i + 1] = 255.0 * c.g;
		g_Buffer[3 * i + 2] = 255.0 * c.b;
	}
}

// La función pinta un punto en las coordenadas especificadas
// Uso, por ejemplo: establecer Punto (Punto (10, 5), Color (1,0,0))
// pinta un punto en la coordenada (10, 5)
// Si no se especifica ningún color, el color de pintura predeterminado es negro
//
// Usa esta función...
void setPoint(Point p, Color c = Color(0, 0, 0)) {
	int x = p.x + TEX_HALF_X;
	int y = p.y + TEX_HALF_Y;
	if (x < 0 || y < 0 || x >= TEX_RES_X || y >= TEX_RES_Y) {
		cerr << "Illegal point co-ordinates (" << p.x << ", " << p.y << ")\n" << flush;
		return;
	}

	g_Buffer[3 * TO_LINEAR(x, y)] = 255.0 * c.r;
	g_Buffer[3 * TO_LINEAR(x, y) + 1] = 255.0 * c.g;
	g_Buffer[3 * TO_LINEAR(x, y) + 2] = 255.0 * c.b;
}

//
// EJERCICIO 1 TAREA 1:
//
// Se supone que esta función es una línea recta entre los puntos
// Pinta p1 y p2 de color c. Usa la función
// establecer Punto para dibujar los puntos individuales.
void bhamLine(Point p1, Point p2, Color c) {

	Point center(0, 0);
	Color cGren(0, 1, 0);					
	setPoint(center, cGren);

	int x1, y1, x2, y2, dx, dy, D, dNE, dE, xAux, yAux; // var declaration
	int sel = 1;





	x1 = p1.x; y1 = p1.y; // Set (x,y) with the values of p1
	x2 = p2.x; y2 = p2.y; // Set (x,y) with the values of p2
	printf("Point 1: %d,%d \n", x1, y1);
	printf("Point 2: %d,%d \n", x2, y2);
	x2 = x2 - x1; y2 = y2 - y1;	// Move p2 to the new position 
	x1 = 0; y1 = 0;				// Set p1 in the x,y axis 
	
	printf("Point 3: %d,%d \n", x2, y2);


	


	dx = x2 - x1; dy = y2 - y1; // Set the delta of x and y
	
	double r = (double) dy / dx;

	//check the slope of the line, to know in which octant is the line, and translate p2 to to the 1º octant
	if (0 <= r && r <= 1) {
		if (x1<x2) {	//1º octant
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
	}else if (0 >= r && r >= -1) {
		if (x2<x1) {	//4º octant
			x2 = -x2;
			dx = x2 - x1; dy = y2 - y1; // Set the delta of x and y
			sel = 4;
			printf("octant 4 \n");

		}
		else{			//8º octant
			y2 = -y2;
			dx = x2 - x1; dy = y2 - y1; // Set the delta of x and y
			sel = 8;
			printf("octant 8 \n");

		}
	}else if (r > 1) {
		if (y1<y2) {	//2º octant
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
		if (y1<y2) {	//3º octant
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
	setPoint(p1, c);

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
		switch (sel){
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
		setPoint(pbham,c);
		printf("El punto final %d,%d \n", pbham.x, pbham.y);
	}

	// ultimo punto
	setPoint(p2, c);
}

//
// EJERCICIO 1 TAREA 2:
//
// Se supone que esta función dibuja un círculo de radio r alrededor del punto p
// pintar. Use la función de punto de ajuste para configurar el individuo
// puntos a dibujar. No olvides incluir el punto central también.
// ¡dibujar!
void bhamCircle(Point p, int r, Color c) {

	// Enfoque
	setPoint(p, c);

	int x, y, d, dSE, dE, dx, dy;
	x = 0; y = r;
	d = 5 - 4 * r;

	//Circle Symmetry

	Point cSym1(x + p.x, y + p.y);
	setPoint(cSym1, c);

	Point cSym2(y + p.x, x + p.y);
	setPoint(cSym2, c);

	Point cSym3(-y + p.x, x + p.y);
	setPoint(cSym3, c);

	Point cSym4(x + p.x, -y + p.y);
	setPoint(cSym4, c);

	

	
	//bresenham's Algorithm
	while (y > x) {
			if (d >= 0) {// SE
				dSE = 4 * (2 * (x - y) + 5);
				d += dSE;
				x++;
				y--;  
			}else { // E
				dE = 4 * (2 * x + 3);
				d += dE;
				x++; 
			}

		
			

			// Symmetry, we move the circle from (0,0) to the point p
			Point cPoint1(x+p.x, y+p.y);
			setPoint(cPoint1, c);

			Point cPoint2(y+p.x, x+p.y);
			setPoint(cPoint2, c);

			Point cPoint3(-y+p.x, x+p.y);
			setPoint(cPoint3, c);

			Point cPoint4(-x+p.x, y+p.y);
			setPoint(cPoint4, c);

			Point cPoint5(-x+p.x, -y+p.y);
			setPoint(cPoint5, c);

			Point cPoint6(-y+p.x, -x+p.y);
			setPoint(cPoint6, c);

			Point cPoint7(y+p.x, -x+p.y);
			setPoint(cPoint7, c);

			Point cPoint8(x+p.x, -y+p.y);
			setPoint(cPoint8, c);
	}

	// ...
}

// La función de devolución de llamada para la pintura real
// responsable es. Esencialmente todo lo que necesitas es a ti mismo
// cuidar el espacio entre los comentarios,
// ¡Todo lo demás es un mal necesario!
void display(void)
{
	Color background(0.5, 0.5, 0.5);	// fondo gris
	clearImage(background);				// eliminar anuncio antiguo
///////////////////////////////////////////////// // //////////////
//
// Tus funciones de Bresenham deben ir aquí
// dibuja una línea y un círculo.
//
// Básicamente no necesitas hacer ningún cambio aquí,
// a menos que quieras "jugar" :-D
//
	
	Point p1(-20, -7);				// definir el primer punto de la linea
	Point p2(-5, 30);				// también el segundo punto
	Color cRed(1, 0, 0);					// Debería ser una línea recta roja...
	bhamLine(p1, p2, cRed);			// dibuja recto...

	Point p(5, 5);						// Definir el punto central del circulo
	int r = 20;								// establece el radio
	Color cBlue(0, 0, 1);					// Se supone que es un círculo azul...
	bhamCircle(p, r, cBlue);			// dibuja un circulo...

	//
	// ¡No cambies nada de aquí!
	// 
	//////////////////////////////////////////////////////////////////

	manageTexture();

	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, g_TexID);
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glTexCoord2f(0, 0);
	glVertex2f(-g_WinWidth / 2, -g_WinHeight / 2);
	glTexCoord2f(1, 0);
	glVertex2f(g_WinWidth / 2, -g_WinHeight / 2);
	glTexCoord2f(1, 1);
	glVertex2f(g_WinWidth / 2, g_WinHeight / 2);
	glTexCoord2f(0, 1);
	glVertex2f(-g_WinWidth / 2, g_WinHeight / 2);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	glFlush();
}

// La función principal
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitWindowSize(g_WinWidth, g_WinHeight);
	glutCreateWindow("Übung 1: Bresenham");

	glutReshapeFunc(reshape);	// Responsable de cambiar el tamaño de la ventana
	glutDisplayFunc(display);	// Responsable de volver a dibujar la pantalla repetidamente

	glutMainLoop();

	glDeleteTextures(1, &g_TexID); // elimina la textura creada anteriormente

	return 0;
}
