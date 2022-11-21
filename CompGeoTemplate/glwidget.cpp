 //
// GUI-template for CG-assignments
//
// (c) Georg Umlauf, 2014
// (c) Georg Umlauf, 2020: Qt5
// (c) Georg Umlauf, 2022: Qt6
//
#include "glwidget.h"
#include <QtGui>
#include <GL/glu.h>
#include "mainwindow.h"
#include <list>
#include <iostream>

std::vector<QPointF> Point_list;

std::vector<QPointF> Graham_list;
std::vector<QPointF> Jarvis_list;



GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{	
}

GLWidget::~GLWidget()
{
}

void GLWidget::paintGL()
{
    // clear
    glClear(GL_COLOR_BUFFER_BIT);

    // Koordinatensystem
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_LINES);
    glVertex2f(-1.0, 0.0);
    glVertex2f( 1.0, 0.0);
    glVertex2f( 0.0,-1.0);
    glVertex2f( 0.0, 1.0);
    glEnd();

    glPointSize(5);
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_POINTS);
    for (unsigned int i = 0; i < Point_list.size(); ++i){
        glVertex2f( Point_list.at(i).x(), Point_list.at(i).y());

    }

    glEnd();

    glColor3f(0.5,0.5,0.5);
    glBegin(GL_LINE_STRIP);
    for (unsigned int i = 0; i < Graham_list.size(); ++i){
        glVertex2f( Graham_list.at(i).x(), Graham_list.at(i).y());

    }

    glEnd();






    glColor3f(0.5,0.5,0.5);
    glBegin(GL_LINE_STRIP);
    for (unsigned int i = 0; i < Jarvis_list.size(); ++i){
        glVertex2f(Jarvis_list.at(i).x(), Jarvis_list.at(i).y());

    }

    glEnd();
    // TODO: Compute and draw convex hull here

	// TODO: draw convex hull using glBegin(GL_LINE_STRIP); ... glEnd();

}


void GLWidget::initializeGL()
{
    resizeGL(width(),height());
}

void GLWidget::resizeGL(int width, int height)
{
    aspectx=1.0;
    aspecty=1.0;
    if (width>height) aspectx = float(width) /height;
    else              aspecty = float(height)/ width;
    glViewport    (0,0,width,height);
    glMatrixMode  (GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D    (-aspectx,aspectx,-aspecty,aspecty);
    glMatrixMode  (GL_MODELVIEW);
    glLoadIdentity();
}

QPointF GLWidget::transformPosition(QPoint p)
{
    return QPointF( (2.0*p.x()/ width() - 1.0)*aspectx,
		           -(2.0*p.y()/height() - 1.0)*aspecty);
}

void GLWidget::keyPressEvent(QKeyEvent * event)
{
    switch (event->key()) {
    case Qt::Key_Escape:   QApplication::instance()->quit(); break;
    case Qt::Key_Q     :   QApplication::instance()->quit(); break;
    default:               QWidget::keyPressEvent(event);    break;
	}
	update();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
	QPointF posF = transformPosition(event->pos());


	if (event->buttons() & Qt::LeftButton ) {
        //add clicked point to point-list
        Point_list.push_back(posF);
        qDebug() << "Implement mousePressEvent for mous-click-input of points at" <<posF;
	}
    update(); 
}




bool compare_x (const QPointF& first, const QPointF& second)//Predicate for sorting the Vector of points
{
  return ( first.x() < second.x());
}
bool compare_y (const QPointF& first, const QPointF& second)//Predicate for sorting the Vector of points
{
  return ( first.y() < second.y());
}

int line_turn(QPointF a, QPointF b, QPointF c)
{
    double val = (b.y() - a.y()) * (c.x() - b.x()) - (b.x() - a.x()) * (c.y() - b.y());

    if(val == 0) {     //The linea goes straight
        return 0;
    }else if(val > 0){ //The line goes to the left
        return 1;
    }else{             //The line goes to the right
        return 2;
    }
}
double crossPoint(QPointF p1, QPointF p2)
{
    return p1.x() * p2.y() - p2.x() * p1.y();
}

QPointF subtract(QPointF p1, QPointF p2)
{
    return QPointF(p2.x() - p1.x(), p2.y() - p1.y());
}

double direction(QPointF p1, QPointF p2, QPointF p3)
{
    return crossPoint(subtract(p1, p3), subtract(p1, p2));
}

double sqrt_distance(QPointF p1, QPointF p2)
{
    return sqrt(pow(p2.x() - p1.x(), 2) + pow(p2.y() - p1.y(), 2));
}
std::vector<QPointF> Graham_scan()
{
    sort(Point_list.begin(),Point_list.end(), compare_x);
    qDebug() << "Point : "<<Point_list.front();

    std::vector<QPointF> L_upper;
    std::vector<QPointF> L_lower;

    auto it_f = std::next(Point_list.begin(), 1);


    L_upper.push_back(Point_list.front());      //Point 1
    L_upper.push_back(*it_f);                     //Point 2

    for(int i=3; i<=Point_list.size(); i++){

        it_f++;
        L_upper.push_back(*it_f);
        while(L_upper.size()>2 && line_turn(L_upper[L_upper.size()-2],L_upper[L_upper.size()-1],L_upper[L_upper.size()])!=2){
            L_upper.erase(L_upper.end()-1);

        }
    }
    auto it_b = std::next(Point_list.end(), -1);

    L_lower.push_back(Point_list.back());      //Point 1
    L_lower.push_back(*it_b);                     //Point 2

    for(int i=Point_list.size()-2; i>=1; i--){

        it_b--;
        L_lower.push_back(*it_b);
        while(L_lower.size()>2 && line_turn(L_lower[L_lower.size()-2],L_lower[L_lower.size()-1],L_lower[L_lower.size()])!=2){
            L_lower.erase(L_lower.end()-1);

        }
    }

    L_lower.erase(L_lower.begin());
    L_lower.pop_back();

    L_upper.insert(L_upper.end(), L_lower.begin(), L_lower.end());
    return L_upper;




}

void GLWidget::radioButton1Clicked()
{
    // TODO: toggle to Jarvis' march
    int n = Point_list.size();
    int l = 0;
    for (int i = 1; i < n; i++) {
        if (Point_list.at(i).x() < Point_list.at(l).x()) l = i;
    }
    Jarvis_list.push_back(Point_list.at(l));

    int p = l, q;
    while (true) {
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (i == p) continue;
            double d = direction(Point_list.at(p), Point_list.at(i), Point_list.at(q));
            if ((d > 0 || (d == 0 && sqrt_distance(Point_list.at(i), Point_list.at(p)) > sqrt_distance(Point_list.at(q), Point_list.at(p))))) {
                q = i;
            }
        }
        p = q;
        Jarvis_list.push_back(Point_list.at(p));
        if (p == l) {
            break;
        }
    };
    update();
}

void GLWidget::radioButton2Clicked()
{

    int i, n;

    n = Point_list.size();
    std::vector<QPointF> L_upper;
    std::vector<QPointF> L_lower;
    //Sort points by x-coordinate
    sort(Point_list.begin(),Point_list.end(), compare_x);

    L_upper.push_back(Point_list.at(0));
    L_upper.push_back(Point_list.at(1));


    for(i = 2; i <n; ++i){
        L_upper.push_back(Point_list.at(i));
        while(L_upper.size() > 2 && direction(L_upper.end()[-3],L_upper.end()[-2], L_upper.end()[-1])<0){
            L_upper.erase(L_upper.end()-2);
        }

    }

    L_lower.push_back(Point_list.end()[-1]);
    L_lower.push_back(Point_list.end()[-2]);


    for(i = n-3; i >= 0; --i){
        L_lower.push_back(Point_list.at(i));
        while(L_lower.size() > 2 && direction(L_lower.end()[-3],L_lower.end()[-2], L_lower.end()[-1])<0){
            L_lower.erase(L_lower.end()-2);
        }

    }
    L_lower.erase(L_lower.begin());

    L_upper.insert(L_upper.end(), L_lower.begin(), L_lower.end());
    Graham_list = L_upper;


    update();
}
QPointF endPoint_finder(QPointF S_P, QPointF E_P, std::vector<QPointF> List_P,int i){

    //S_P = Start point and E_P = end point

    double min_angle = 0.0;
    QPointF qi;

    for(int j = i; j<List_P.size(); j++){


        QPointF v1;
        QPointF v2;

        v1.setX(List_P.at(i-1).x()-S_P.x());
        v1.setY(List_P.at(i-1).y()-S_P.x());

        v2.setX(E_P.x()-S_P.x());
        v2.setY(E_P.y()-S_P.x());

        double cos_angle = (v1.x()*v2.x()+v1.y()*v2.y())/((sqrt(v1.x()*v1.x()+v1.y()*v1.y()))*(v2.x()*v2.x()+v2.y()*v2.y()));
        double angle = acos(cos_angle);

        if(angle < min_angle || min_angle == 0.0){
            min_angle = angle;
            qi = List_P.at(j);
        }

    }
    return qi;




}
