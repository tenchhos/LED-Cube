#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QtGui>
#include <QtOpenGL/QtOpenGL>
#include <cmath>
#include <QTimer>
#include <QFile>

class MyGLWidget : public QGLWidget{

  Q_OBJECT

public:
    MyGLWidget(QWidget *parent = NULL)
        : QGLWidget(parent) {}

protected:

    void drawCube();
    void drawPoint();
    int  hashKey(double x, double y, double z);
    int  maxDimension();
    bool drawFace(double x, double y, double z);
    void loadFile();
    bool drawSine(double x, double y, double z,double t, bool on);
    void initializeGL();
    void paintGL();
    void resizeGL (int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *);

public slots:
    void setxDimensions(int size);
    void setyDimensions(int size);
    void setzDimensions(int size);
    void fitToWindow(int x);
    void loadZoomScales();
    void setLedSize(int size);
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setScale(int scaleFactor);
    void setSpacing(double spaceFactor);
    void setTransparency(int transpValue);
    void setColorRed(bool x);
    void setColorWhite(bool x);
    void setColorBlue(bool x);
    void setColorYellow(bool x);
    void setColorGreen(bool x);
    void animate(int index);
    void modeChanged(int index);
    void advance();

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void scaleChanged(int scaleFactor);
    void transparencyChanged(int transpValue);
    void colorChange(QColor x);

private:
    int    m_xRot;
    int    m_yRot;
    int    m_zRot;
    int    m_xDimension;
    int    m_yDimension;
    int    m_zDimension;
    double m_maxDimX;
    double m_maxDimY;
    double m_maxDimZ;
    double m_transpVal;
    double m_scale;
    double m_spacing;
    double m_ledSize;
    double m_color_x;
    double m_color_y;
    double m_color_z;
    double m_currentTrans;
    double m_time;
    double m_timeshift;
    bool   m_animate_sin;
    bool   m_animate_face;
    bool   m_fileLoaded;
    bool   m_points;
    bool   m_cubes;
    bool   m_fittowindow;
    QPoint m_lastPos;
    QHash <int,int> m_hash;
    QHash <int,int> m_zoomhash;

};

#endif // MYGLWIDGET_H

