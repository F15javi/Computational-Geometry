//
// GUI-template for CG-assignments
//
// (c) Georg Umlauf, 2014
// (c) Georg Umlauf, 2020: Qt5
// (c) Georg Umlauf, 2022: Qt6
//
#pragma once

#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    GLWidget                  (QWidget *parent=0);
    ~GLWidget                 ();
signals:
    void continueRequest      ();
public slots:
    void radioButton1Clicked  ();
    void radioButton2Clicked  ();
protected:
    void paintGL              ();
    void initializeGL         ();
    void resizeGL             (int width, int height);
    void keyPressEvent        (QKeyEvent   *event);
    void mousePressEvent      (QMouseEvent *event);
private:
    QPointF transformPosition (QPoint p);
    double  aspectx, aspecty;




};
std::vector<QPointF> Graham_scan          ();
std::vector<QPointF> Jarvis_march         ();
QPointF endPoint_finder(QPointF Start_point, QPointF End_point, std::vector<QPointF> List_P,int i);
