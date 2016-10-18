#include "window.h"
#include "Tetrahedron.h"
#include "myglwidget.h"

// add three grids in one column
Window::Window(QWidget *parent): QWidget(parent)
{
     glWidget = new MyGLWidget;

     QGridLayout *grid = new QGridLayout;

     grid->addWidget(glWidget, 0, 0);
     grid->addWidget(createLEDCountGroup(), 1, 0);
     grid->addWidget(createLEDColorGroup(), 2, 0);
     grid->addWidget(createTransformsGroup(), 3, 0);
     setLayout(grid);

     setWindowTitle(tr("LED Cubes"));
     // set the default size when app launches
     resize(540, 340);
}

// create Resolution GroupBox
QGroupBox *Window::createLEDCountGroup()
 {
     QGroupBox *groupBox = new QGroupBox("LED Count");

     QSpinBox *X = new QSpinBox;
     QSpinBox *Y = new QSpinBox;
     QSpinBox *Z = new QSpinBox;
     QSpinBox *Spacing = new QSpinBox;

     QLabel *x = new QLabel("X");
     QLabel *y = new QLabel("Y");
     QLabel *z = new QLabel("Z");
     QLabel *spacing = new QLabel("Spacing:");
     QLabel *inches = new QLabel("Inches");

     X->setRange(0, 100);
     Y->setRange(0, 100);
     Z->setRange(0, 100);
     Spacing->setRange(0, 50);

     // set default value
     X->setValue(30);
     Y->setValue(30);
     Z->setValue(30);
     Spacing->setValue(5);

     QHBoxLayout *hbox1 = new QHBoxLayout;
     hbox1->addWidget(x);
     hbox1->addWidget(X);
     hbox1->addSpacing(15);
     hbox1->addWidget(y);
     hbox1->addWidget(Y);
     hbox1->addSpacing(15);
     hbox1->addWidget(z);
     hbox1->addWidget(Z);
     hbox1->addSpacing(15);
     hbox1->addWidget(spacing);
     hbox1->addWidget(Spacing);
     hbox1->addWidget(inches);

     QVBoxLayout *vbox = new QVBoxLayout;
     vbox->addLayout(hbox1);

     groupBox->setLayout(vbox);
     return groupBox;
}

// create LEDColor GroupBox
QGroupBox *Window::createLEDColorGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("LED Color"));

    QRadioButton *red = new QRadioButton("Red");
    QRadioButton *blue = new QRadioButton("Blue");
    QRadioButton *green = new QRadioButton("Green");
    QRadioButton *yellow = new QRadioButton("Yellow");
    QRadioButton *white = new QRadioButton("White");

    red->setChecked(true);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(red);
    hbox->addWidget(blue);
    hbox->addWidget(green);
    hbox->addWidget(yellow);
    hbox->addWidget(white);

    groupBox->setLayout(hbox);
    return groupBox;
}

// create Transform GroupBox
QGroupBox *Window::createTransformsGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Transforms"));

    QSlider *x = new QSlider(Qt::Horizontal);
    QSlider *y = new QSlider(Qt::Horizontal);
    QSlider *z = new QSlider(Qt::Horizontal);

    QSpinBox *x1 = new QSpinBox;
    QSpinBox *y1 = new QSpinBox;
    QSpinBox *z1 = new QSpinBox;

    QLabel *X = new QLabel("X Rotation");
    QLabel *Y = new QLabel("Y Rotation");
    QLabel *Z = new QLabel("Z Rotation");

    x->setRange(0, 360);
    y->setRange(0, 360);
    z->setRange(0, 360);

    x1->setRange(0, 360);
    y1->setRange(0, 360);
    z1->setRange(0, 360);

    QObject::connect(x1, SIGNAL(valueChanged(int)),
                     x, SLOT(setValue(int)));
    QObject::connect(x, SIGNAL(valueChanged(int)),
                     x1, SLOT(setValue(int)));

    QObject::connect(y1, SIGNAL(valueChanged(int)),
                     y, SLOT(setValue(int)));
    QObject::connect(y, SIGNAL(valueChanged(int)),
                     y1, SLOT(setValue(int)));

    QObject::connect(z1, SIGNAL(valueChanged(int)),
                     z, SLOT(setValue(int)));
    QObject::connect(z, SIGNAL(valueChanged(int)),
                     z1, SLOT(setValue(int)));

    QHBoxLayout *hbox1 = new QHBoxLayout;
    hbox1->addWidget(X);
    hbox1->addWidget(x);
    hbox1->addWidget(x1);

    QHBoxLayout *hbox2 = new QHBoxLayout;
    hbox2->addWidget(Y);
    hbox2->addWidget(y);
    hbox2->addWidget(y1);

    QHBoxLayout *hbox3 = new QHBoxLayout;
    hbox3->addWidget(Z);
    hbox3->addWidget(z);
    hbox3->addWidget(z1);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox3);

    groupBox->setLayout(vbox);

    return groupBox;
}

