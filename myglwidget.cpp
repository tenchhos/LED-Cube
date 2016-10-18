#include "myglwidget.h"
#include "window.h"

void MyGLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void MyGLWidget::resizeGL (int width, int height)
{
    glViewport( 0, 0, (GLint)width, (GLint)height );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum( -1.0, 1.0, -1.0, 1.0, 1, -1);

    glMatrixMode( GL_MODELVIEW );
    glEnable(GL_PROGRAM_POINT_SIZE);
}

void MyGLWidget::drawCube()
{
    glBegin(GL_POINTS);
    glVertex3f(.9,0,0);
    glVertex3f(1,0,0);
    glVertex3f(1,.1,0);
    glVertex3f(.9,.1,0);

    glVertex3f(.9,0,-.1);
    glVertex3f(1,0,-.1);
    glVertex3f(1,.1,-.1);

    glVertex3f(.9,.1,-.1);
    glEnd();

 //glPopMatrix();

}


void MyGLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);
/*
   glPointSize(2);
    glBegin(GL_POINTS);
    //glColor3f(m_xcol, m_ycol, m_zcol);
    //if(Window->radio_g->isChecked())
    //    setColor(Qt::green);

    qglColor(qtColor);

    for(double i = -1; i <= 1; i+=0.125){
        for(double j = -1; j <= 1; j+=0.125){
            for(double k = -1; k <= 1; k+=0.125){
            glVertex3f(i,j,k);
    }
    }
    }

    glEnd();
*/


//3 x 3 cube
    qglColor(qtColor);
    glTranslatef(0.5,-0.5, 0.5);
    for(double z = 0; z < 3; z++){
        if(z != 0)
        {
            glTranslatef(0,-1,-0.5);
        }
    for(double y = 0; y < 3; y++){
        if(y == 0)
        glPushMatrix();
        if(y != 0)
        {
            glTranslatef(0, 0.5,0);
            glPushMatrix();
        }
        for(double x = 0; x < 3; x++)
        {
            drawCube();
            glTranslatef(-0.5,0,0);
        }

        glPopMatrix();
    }
    }


/* GRID WORKING
  for(int i = 0; i < 10; i++){
        glTranslatef(0,0,-.2);
        for(int j = 0; j < 10; j++){
            glTranslatef(-.2,0,0);
            drawCube();
            glPushMatrix();
            }
                 glPopMatrix();
                }
 */
/*
    for(int i = 0; i < 3; i++){
          glTranslatef(0,0,-.2);
          for(int k = 0; k < 3; k++){
              glTranslatef(0, -.2, 0);
          for(int j = 0; j < 3; j++){
              glTranslatef(-.2,0,0);
              drawCube();
              glPushMatrix();
              }
                   glPopMatrix();
                  }
                        glPopMatrix();
                        }   */
/*
 glPopMatrix();
glTranslatef(0,0,-.2);
 for(int i = 0; i < 10; i++){
  glTranslatef(-.2,0,0);
  drawCube();
 }

 glPopMatrix();
glTranslatef(0,0,-.2);
 for(int i = 0; i < 10; i++){
  glTranslatef(-.2,0,0);
  drawCube();
 }
*/
/*
    glPushMatrix();
    for(double i = 0; i> -1; i+=-.2){
        glPopMatrix();
        glTranslatef(0, 0 ,i);

        for(int i = 0; i < 10; i++){

            glTranslatef(-.2,0,0);
            //glPushMatrix();
            drawCube();
    }
}
*/

    /*
    for(int i = 0; i < 10; i++){
     drawCube();
     glTranslatef(-.2,0,0);
}
    glPopMatrix();
    glTranslatef(0,0,-.2);
    for(int i = 0; i < 10; i++){
     drawCube();
     glTranslatef(-.2,0,0);
    }*/
}
static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360;
    while (angle > 360)
        angle -= 360;
}

void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setColorRed(bool x)
{
    if(x){
            qtColor = Qt::red;
            emit colorChange(qtColor);
            updateGL();
    }
}

void MyGLWidget::setColorWhite(bool x)
{
    if(x){
            qtColor = Qt::white;
            emit colorChange(qtColor);
            updateGL();
    }
}

void MyGLWidget::setColorGreen(bool x)
{
    if(x){
            qtColor = Qt::green;
            emit colorChange(qtColor);
            updateGL();
    }
}

void MyGLWidget::setColorYellow(bool x)
{
    if(x){
            qtColor = Qt::yellow;
            emit colorChange(qtColor);
            updateGL();
    }
}

void MyGLWidget::setColorBlue(bool x)
{
    if(x){
            qtColor = Qt::blue;
           // emit colorChange(qtColor);
            updateGL();
    }
}


void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot +  dy);
        setYRotation(yRot +  dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot +  dy);
        setZRotation(zRot +  dx);
    }
    lastPos = event->pos();
}


