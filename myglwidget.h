#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QtGui>
#include <QtOpenGL/QGLWidget>

class MyGLWidget : public QGLWidget{

  Q_OBJECT

public:
    MyGLWidget(QWidget *parent = NULL)
        : QGLWidget(parent) {qtColor = Qt::white;}

protected:

   void drawCube();
   void initializeGL();
   void paintGL();
   void resizeGL (int width, int height);
   void mousePressEvent(QMouseEvent *event);
   void mouseMoveEvent(QMouseEvent *event);

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setColorRed(bool x);
    void setColorWhite(bool x);
    void setColorBlue(bool x);
    void setColorYellow(bool x);
    void setColorGreen(bool x);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void colorChange(QColor x);

private:
    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    QColor qtColor;
};



#endif // MYGLWIDGET_H

