#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#include "myglwidget.h"

class GLWidget;

class Window : public QWidget
{
	Q_OBJECT

public:
	Window(QWidget *parent = 0);

private:
    MyGLWidget *glWidget;
    QGroupBox *Configurations();
	QGroupBox *Resolution();
	QGroupBox *LEDColor();
	QGroupBox *Transforms();

};

#endif
