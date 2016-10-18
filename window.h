#ifndef WINDOW_H
#define WINDOW_H
#include <QWidget>
#include <QtWidgets>
#include "myglwidget.h"

class GLWidget;

class Window: public QWidget
{
 Q_OBJECT

 public:
     Window(QWidget *parent = 0);

 private:
     MyGLWidget *glWidget;
     QGroupBox *createLEDCountGroup();
     QGroupBox *createLEDColorGroup();
     QGroupBox *createTransformsGroup();
    // QGraphicsView  LEDDisplay();
};

#endif // WINDOW_H
