#include "myglwidget.h"
#include "window.h"

/* Function that creates a map, takes in a file with 2 columns of numbers.
 * The code then seperates each item with a key and value.
 */

void MyGLWidget::loadZoomScales()                           // function that creates a map
{
    double hashKey;
    int    zoomFactor;
    QString str;
    QString strTwo;

    QFile file("zoomcoords.txt");                           // locates the file
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))  // loads the file: makes for read only
        return;
    QTextStream in(&file);                                  // reading in the file
    while (!in.atEnd()) {                                   // while not at the end of the file, perform the following:

        QString line = in.readLine();                       // start reading each line
        str = line.section(" ", 0,0);                       // seperate the key and the value: 0 = key
        hashKey = str.toDouble();                           // converts string to double
        strTwo = line.section(" ", 1,1);                    // seperate the key and the value: 1 = value
        zoomFactor = strTwo.toInt();                        // converts to int
        m_zoomhash[hashKey] = zoomFactor;                   // stored values of cube dimensions to appropriate zoom level
                                                            // in to map
    }
}

/* Function that fits the cube within the window
 */
void MyGLWidget::fitToWindow(int x)                         // slot function that fits the cube to the size of the
{                                                           // gl window
  if(x)
  {
        m_fittowindow = true;
  }
  else
        m_fittowindow = false;

  updateGL();
}

/* Function that advances the sinwave by pi/2
 */
void MyGLWidget::advance()                                   // sine wave: moves sin wave by pi/2 units slot fucntion
{
    m_timeshift+=1.57079632679;
}

/* Slot function for the mode drop down menu
 */
void MyGLWidget::modeChanged(int index)
{                                                            // 1st item 0, 2nd item 1
    switch(index)
    {
    case 0:
        m_cubes = true;                                      // 1st item is cubes, turn off points
        m_points = false;
        updateGL();
        break;
    case 1:                                                  // 2nd item is points, turn off cubes
        m_cubes = false;
        m_points = true;
        updateGL();
        break;
    }
}

/* Function that finds maximum dimension and returns an int
 */
int  MyGLWidget::maxDimension()
{
    int maxDimension = 0;
    if(m_xDimension >= m_yDimension && m_xDimension >= m_zDimension)
        maxDimension = m_xDimension;
    if(m_yDimension >= m_xDimension && m_yDimension >= m_zDimension)
        maxDimension = m_yDimension;
    if(m_zDimension >= m_xDimension && m_zDimension >= m_yDimension)
        maxDimension = m_zDimension;
   return maxDimension;
}

/* Slot function for the mode drop down menu
 */
void MyGLWidget::animate(int index)                          // animate drop down menu
{
    QTimer *timer = new QTimer(this);

    switch(index)
    {
    case 0:                                                  // no animation "off"
        m_animate_sin  = false;
        m_animate_face = false;
        m_fileLoaded   = false;
        break;
    case 1:                                                  // sine wave animation
        m_animate_sin  = true;
        m_animate_face = false;
        m_fileLoaded   = false;
        connect(timer,SIGNAL(timeout()),this,
                SLOT(advance()));                           // timeout (finished time)
        connect(timer,SIGNAL(timeout()),this,
                SLOT(updateGL()));                          // updates every 50 millisec
        timer->start(50);                                   // starts timer and counts millisec
        break;
    case 2:                                                 // face animation
        m_animate_sin  = false;
        m_fileLoaded   = false;
        m_animate_face = true;
        updateGL();
        break;
    }

}

/* Function that sets all default values for the cube when the program is executed.
 */
void MyGLWidget::initializeGL()
{
    glEnable(GL_BLEND);                                     // allows blending of colors
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);      // combining colors to create transparency
    loadZoomScales();                                       // 1st & only time being called, puts values into hash
    m_scale = 1.0;                                          // initialize all private variables
    m_spacing = 0.1;
    m_ledSize = 0.020;
    m_xDimension = 9;
    m_yDimension = 9;
    m_zDimension = 9;
    m_transpVal = 0.5;
    m_color_x = 1.0;
    m_color_y = 1.0;
    m_color_z = 1.0;
    m_currentTrans = 1.0;
    m_time = 0.0;
    m_timeshift = 1.57079632679;
    m_animate_sin = false;
    m_animate_face = false;
    m_fileLoaded = false;
    m_points = false;
    m_cubes = true;
    m_fittowindow = false;
}

/* Function for the resizing of the glWidget
 */
void MyGLWidget::resizeGL (int width, int height)          // renders and scales the gl window
{
    glViewport( 0, 0, (GLint)width, (GLint)height );
    glMatrixMode(GL_PROJECTION);                           // set the matrix mode to projection
    glLoadIdentity();                                      // load the identity matrix
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1, -1);                // create a frustrum
    glMatrixMode( GL_MODELVIEW );                          // set the matrix mode to modelview
}

/* Function for drawing the sine wave
 */
bool MyGLWidget::drawSine(double x, double y,
                          double z, double t, bool on)
{
    if(z == floor(2*sin((x/2)+t/10)
                  + 2*sin((y/2)+t/10) + m_zDimension/2) && on)
        return true;
    else
        return false;
}

/* Function used to draw a cube by specifying the coordinates of each face.
 */
void MyGLWidget::drawCube()
{
    float x = m_ledSize;
    glBegin(GL_POLYGON);
    glVertex3f(  x, -x, x );
    glVertex3f(  x,  x, x );
    glVertex3f( -x,  x, x );
    glVertex3f( -x, -x, x );
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f( x, -x, -x );
    glVertex3f( x,  x, -x );
    glVertex3f( x,  x,  x );
    glVertex3f( x, -x,  x );
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f( -x, -x,  x );
    glVertex3f( -x,  x,  x );
    glVertex3f( -x,  x, -x );
    glVertex3f( -x, -x, -x );
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(  x,  x,  x );
    glVertex3f(  x,  x, -x );
    glVertex3f( -x,  x, -x );
    glVertex3f( -x,  x,  x );
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(  x, -x, -x );
    glVertex3f(  x, -x,  x );
    glVertex3f( -x, -x,  x );
    glVertex3f( -x, -x, -x );
    glEnd();
}

/* Function used to draw points instead of cubes, used in drop down menu's.
 */
void MyGLWidget::drawPoint()
{
    glPointSize(m_ledSize*100);                                  // x100 makes noticeable change in led size
    glBegin(GL_POINTS);
    glVertex3f(0,0,0);                                           // Specifying the origin
    glEnd();
}
/* Function that takes a coordinate and locates a specific cube the coordinate represents if it falls within the cube.*/
int  MyGLWidget::hashKey(double x, double y, double z)
{
    int initpoint = ((0.1*(m_xDimension-1))/2)*10;               // Our coordinate value of the first cube converted to int

    int locationInHash = 0;
    int counter = 0;                                             // Initialize counter
    for(int zi = initpoint; zi >= -initpoint; zi--)              // Getting rid of the z dimension
    {    if(zi == (z*10))                                        // Check if it is the first value we check then we want counter to be 0
            break;
         if(zi == -initpoint)
             counter = -1;                                       // Set counter to -1 if the coordinate does not fit in any of the z values
        counter++;
    }
    if(counter == -1)
        return 0;                                                // Return if counter is not any of the values z coordinate values
    else
        locationInHash = (counter*m_zDimension*m_zDimension) + 1;

    counter = 0;                                                 // Initialize counter
    for(int yi = -initpoint; yi <= initpoint; yi++)              // Getting rid of the y dimension
    {    if(yi == (y*10))                                        // Check if it is the first value we check then we want counter to be 0
            break;
         if(yi == initpoint)
             counter = -1;                                       // Set counter to -1 if the coordinate does not fit in any of the y values
         counter++;
    }
    if(counter == -1)
        return 0;                                                // Return if counter is not any of the values z coordinate values
    else
        locationInHash += counter*m_yDimension;

    counter = 0;                                                 // Initialize counter
    for(int xi = initpoint; xi >= -initpoint; xi--)              // Getting rid of the x dimension
    {    if(xi == (x*10))                                        // Check if it is the first value we check then we want counter to be 0
            break;
         if(xi == -initpoint)
             counter = -1;                                       // Set counter to -1 if the coordinate does not fit in any of the x values
        counter++;
    }
    if(counter == -1)
        return 0;                                                // Return if counter is not any of the values z coordinate values
    else
        locationInHash += counter;

    return locationInHash;                                       // Returns the location the coordinate represents in the hash
}

/* Function is used to load a file with coordinates that will be used to turn on cubes
 * in the LED cube to show an image.
 */
void MyGLWidget::loadFile()
{
    m_fileLoaded = true;

    QVector <double> vector;                                     // vector of coordinates
    QString str;
    double val;                                                  // variable to keep track of the current value
    double maxDimX = 0;                                          // variable to keep track of maximum x dimension
    double maxDimY = 0;                                          // variable to keep track of maximum y dimension
    double maxDimZ = 0;                                          // variable to keep track of maximum z dimension
    bool   ignoreLine = false;                                   // ignore the first line that tells how many points

    QFile file("facemale.xyz");
    if (!file.open(QIODevice::ReadOnly))                         // checks if we can open file and includes the flag for the file to be read only
        return;
    QTextStream in(&file);                                       // use QTextStream to read file line by line
    while (!in.atEnd()) {                                        // while we are not at the end of the file


        QString line = in.readLine();                            // read each line, seperate the three numbers
        str = line.section(" ", 0,0);                            // into 3 strings and adds the value to vector
        val = str.toDouble();
        vector.append(val);
        if(maxDimX < val && ignoreLine)
            maxDimX = val;
        ignoreLine = true;

        str = line.section(" ", 1,1);
        val = str.toDouble();
        vector.append(val);
        if(maxDimY < val)
            maxDimY = val;

        str = line.section(" ", 2,2);
        val = str.toDouble();
        vector.append(val);
        if(maxDimZ < val)
            maxDimZ = val;
    }

        for(int i = 1; i <= m_xDimension*m_yDimension*m_zDimension; i++)// for i to number of leds
            m_hash.insert(i, 0);                                        // initialize all values of the historgram to 0

        double xface;
        double yface;
        double zface;
        QString valueAsString;

        for(int i = 3; i < vector.size(); i+=3)                         // start at 3 so you dont include first line and jump by 3
        {
            xface = vector[i]/((10*m_spacing)*maxDimX/
                               ((m_spacing*(m_xDimension-1))/2));
            valueAsString = QString::number(xface,'d', 1);              // rounds the floating point number 1 decimal
            xface = valueAsString.toDouble();                           // convert to double

            yface = vector[i+1]/((10*m_spacing)*maxDimY/                // convert the coordinates given so they fall in the coordinates of the cube
                                 ((m_spacing*(m_yDimension-1))/2));
            valueAsString = QString::number(yface,'d', 1);
            yface = valueAsString.toDouble();

            zface = vector[i+2]/((10*m_spacing)*maxDimZ/
                                 ((m_spacing*(m_zDimension-1))/2));
            valueAsString = QString::number(zface,'d', 1);
            zface = valueAsString.toDouble();

            m_hash[hashKey(xface, yface, zface)]++;                      // call the hashkey function to see if the coordinate fits the cube and 
                                                                         // increment the hash if it does
        }
}

/* OpenGL function for drawing
 */
void MyGLWidget::paintGL()
{
    if(m_animate_face)
        loadFile();
    if(m_fittowindow)
    {
        double setScale = 0.0;
        setScale = (m_zoomhash[maxDimension()*10+m_spacing*10]/100.0);  // takes the maximum dimension and spacing takes the                                                                 
        m_scale = setScale;                                             // correct scale value from the hash
    }

    glLoadIdentity();                                                   // loads the identity matrix

    /* Multiplies the current matrix with the following matrixes to apply rotation and scaling in each axis */
    glRotatef(m_xRot, 1.0, 0.0, 0.0);
    glRotatef(m_yRot, 0.0, 1.0, 0.0);
    glRotatef(m_zRot, 0.0, 0.0, 1.0);
    glScalef(m_scale, m_scale, m_scale);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);                   // clears the background

    glLoadIdentity();                                                   // loads the current matrix
    glFrustum(-1.0, 1.0, -1.0, 1.0, 0.0 , 1.0);                         // frustum sets the viewing point of view
    glMatrixMode(GL_MODELVIEW);                                         // model view is used to control movement of the
                                                                        // object

    /* Multiplies the current matrix with the following matrixes to apply rotation and scaling in each axis */
    glRotatef(m_xRot, 1.0, 0.0, 0.0);
    glRotatef(m_yRot, 0.0, 1.0, 0.0);
    glRotatef(m_zRot, 0.0, 0.0, 1.0);
    glScalef(m_scale, m_scale, m_scale);

    int counter = 1;
    double initpointX = (m_spacing*(m_xDimension-1))/2;                 // initial x point to start drawing
    double initpointY = (m_spacing*(m_yDimension-1))/2;                 // initial y point to start drawing
    double initpointZ = (m_spacing*(m_zDimension-1))/2;                 // initial z point to start drawing
    glTranslatef(initpointX,-initpointY, initpointZ);                   // translate to the first cube/point to be drawn

    /* Draw the LED Cube */
    for(int z = 0; z < m_zDimension; z++){
        if(z != 0)
        {
            glTranslatef(0,-((m_yDimension-1)*m_spacing),-m_spacing);
        }
    for(int y = 0; y < m_yDimension; y++){
        if(y == 0)
            glPushMatrix();
        if(y != 0)
        {
            glTranslatef(0,m_spacing,0);
            glPushMatrix();
        }
        for(int x = 0; x < m_xDimension; x++)
        {
            if(m_hash[counter] > 0 && m_animate_face)                      // check if cube needs to be turned on and if face is enabled
                glColor4f(m_color_x, m_color_y, m_color_z, m_currentTrans);// make cube turn on
            else if(drawSine(x,y,z,m_timeshift, m_animate_sin))            // check if animate sine is on
                glColor4f(m_color_x, m_color_y, m_color_z, m_currentTrans);// make it turn on
            else
                glColor4f(m_color_x, m_color_y, m_color_z, m_transpVal);   // make cube transparent
            if(m_cubes)                                                    // check if cubes are enabled
                drawCube();
            if(m_points)                                                   // check if points are enabled
                drawPoint();
            counter++;                                                     // counter fo the hash
            glTranslatef(-m_spacing,0,0);
        }

        glPopMatrix();
    }
    }

}

/* The setDimensions functions set the amount of LED cubes in each respective axis.
 */
void MyGLWidget::setxDimensions(int size)
{
    m_xDimension = size;
    updateGL();
}

void MyGLWidget::setyDimensions(int size)
{
    m_yDimension = size;
    updateGL();
}

void MyGLWidget::setzDimensions(int size)
{
    m_zDimension = size;
    updateGL();
}

/* Function sets the appropriate aspect ratio for a given LED size.
 */
void MyGLWidget::setLedSize(int size)
{
    m_ledSize = size/1000.0;
    updateGL();
}

/* Function sets the appropriate transparency ratio.
 */
void MyGLWidget::setTransparency(int transpValue)
{
    m_transpVal = transpValue/100.0;
    updateGL();
}

/* Function sets the spacing between LED cubes.
 */
void MyGLWidget::setSpacing(double spaceFactor)
{
    m_spacing = spaceFactor;
    updateGL();
}

/* Function sets the scaling when zooming.
 */
void MyGLWidget::setScale(int scaleFactor)
{
    double setScale = 0.0;
    setScale = (scaleFactor/100.0);
    m_scale = setScale;
    updateGL();
}

/* Function sets angle to be within 0-360 range
 */
static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360;
    while (angle > 360)
        angle -= 360;
}

/* Function sets the angle of rotation in each axis.
 */
void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);                                         // Normalize the angle to be within 0-360 degrees
    if (angle != m_xRot) {                                          // set the angle to be rotated in the x axis
        m_xRot = angle;
        emit xRotationChanged(angle);                               // emit the change in the angle
        updateGL();                                                 // for signal/slot connection and update
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

/* setColor functions sets the appropriate color to the LED's
 */
void MyGLWidget::setColorRed(bool x)
{
    if(x){
            m_color_x = 1.0;
            m_color_y = 0.0;
            m_color_z = 0.0;
            updateGL();
    }
}

void MyGLWidget::setColorWhite(bool x)
{
    if(x){
            m_color_x = 1.0;
            m_color_y = 1.0;
            m_color_z = 1.0;
            updateGL();
    }
}

void MyGLWidget::setColorGreen(bool x)
{
    if(x){
            m_color_x = 0.0;
            m_color_y = 1.0;
            m_color_z = 0.0;
            updateGL();
    }
}

void MyGLWidget::setColorYellow(bool x)
{
    if(x){
            m_color_x = 1.0;
            m_color_y = 1.0;
            m_color_z = 0.0;
            updateGL();
    }
}

void MyGLWidget::setColorBlue(bool x)
{
    if(x){
            m_color_x = 0.0;
            m_color_y = 0.0;
            m_color_z = 1.0;
            updateGL();
    }
}
/* Function for when the user pressed one of the buttons
 */
void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->pos();                                       // Record the position of the mouse
}

/* Function that implements the mouse scroll for zoom
 */
void MyGLWidget::wheelEvent(QWheelEvent *scroll)
{
    if(scroll->delta() > 0)                                         // Check if the scroll is up
        m_scale += m_scale*0.1;                                     // Increase the zoom by 0.1 times the scale
    else
        m_scale -= m_scale*0.1;                                     // Else the scroll was down so decrease the zoom by the same value
    updateGL();
}

/* Function for when the user moves the mouse
 */
void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - m_lastPos.x();                            // Record the change in the x direction of the drag
    int dy = event->y() - m_lastPos.y();                            // Record the change in the y direction of the drag

    if (event->buttons() & Qt::LeftButton) {                        // Rotations for the left botton in the x and y
        setXRotation(m_xRot + dy);
        setYRotation(m_yRot + dx);
    } else if (event->buttons() & Qt::RightButton) {                // Rotations for the right botton in the z
        setXRotation(m_xRot + dy);
        setZRotation(m_zRot + dx);
    }
    m_lastPos = event->pos();                                       // Record the new last position
}



