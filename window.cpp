#include "window.h"
#include "myglwidget.h"

Window::Window(QWidget *parent) : QWidget(parent)
{
    glWidget = new MyGLWidget;                                      //Create out GLWidget

    QGridLayout *grid = new QGridLayout;                            //Create a new GridLayout
    grid->addWidget(glWidget, 0, 0);                                //Add out GLWidget to the grid
    grid->addWidget(Configurations(), 1, 0);                        //Add the Groupbox returned by the Configurations function to the grid
    grid->addWidget(Transforms(), 2, 0);                            //Add the Groupbox returned by the Transforms function to the grid
    grid->addWidget(Resolution(), 3, 0);                            //Add the Groupbox returned by the Resolution function to the grid
    grid->addWidget(LEDColor(), 4, 0);                              //Add the Groupbox returned by the LEDColor function to the grid
    setLayout(grid);
    setWindowTitle(tr("LED Cube"));
    setStyleSheet("background-color:dimgray;");                     //Make the background color dim-gray
    resize(600, 1000);                                              //Set the size of the window

}
/* Function that returns the groupbox for the Configurations to add to the layout
 */
QGroupBox *Window::Configurations()
{
    QGroupBox *groupBox = new QGroupBox(tr("Configurations"));
    QComboBox *animations = new QComboBox();
    QLabel    *labelAnimate = new QLabel("Animations:");
    animations->addItem("Off");
    animations->addItem("Sine Wave");
    animations->addItem("Face");

    QComboBox *mode = new QComboBox();
    QLabel    *labelMode = new QLabel("Cube Mode:");
    mode->addItem("Cubes");
    mode->addItem("Points");

    QCheckBox *checkBox = new QCheckBox("Fit to screen");

    //Setting up the SIGNALS AND SLOTS

    QObject::connect(checkBox, SIGNAL(stateChanged(int)),
    glWidget, SLOT(fitToWindow(int)));

    QObject::connect(animations, SIGNAL(currentIndexChanged(int)),
    glWidget, SLOT(animate(int)));

    QObject::connect(mode, SIGNAL(currentIndexChanged(int)),
    glWidget, SLOT(modeChanged(int)));

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(labelAnimate, 0, 0);
    grid->addWidget(animations, 0, 1, Qt::AlignLeft);
    grid->addWidget(labelMode, 0, 2, Qt::AlignRight);
    grid->addWidget(mode, 0, 3);
    grid->addWidget(checkBox, 0, 4);
    groupBox->setLayout(grid);

    //Styling the Widget

    labelAnimate->setStyleSheet("color:white;");
    labelMode->setStyleSheet("color:white;");

    groupBox->setMaximumHeight(75);
    return groupBox;

}
/* Function that returns the groupbox for the Resolution to add to the layout
 */
QGroupBox *Window::Resolution()
{
    QGroupBox *groupBox = new QGroupBox(tr("LED Count"));

    QLabel *label_x = new QLabel("X:");
    QLabel *label_y = new QLabel("Y:");
    QLabel *label_z = new QLabel("Z:");
    QLabel *label_s = new QLabel("LED Spacing:");
    QLabel *label_i = new QLabel("inches");
    QLabel *label_l = new QLabel("LED Size:");

    QSpinBox *spinBox_x = new QSpinBox();
    spinBox_x->setRange(2,128);
    spinBox_x->setValue(9);
    QSpinBox *spinBox_y = new QSpinBox();
    spinBox_y->setRange(2,128);
    spinBox_y->setValue(9);
    QSpinBox *spinBox_z = new QSpinBox();
    spinBox_z->setRange(2,128);
    spinBox_z->setValue(9);
    QDoubleSpinBox *spinBox_s = new QDoubleSpinBox();
    spinBox_s->setMaximum(1);
    spinBox_s->setMinimum(0.1);
    spinBox_s->setValue(0.1);
    spinBox_s->setSingleStep(0.1);
    QSpinBox *spinBox_lsize = new QSpinBox();
    spinBox_lsize->setRange(0,50000);
    spinBox_lsize->setValue(15);

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(label_x, 0, 0, Qt::AlignRight);
    grid->addWidget(spinBox_x, 0, 1);
    grid->addWidget(label_y, 0, 2, Qt::AlignRight);
    grid->addWidget(spinBox_y, 0, 3);
    grid->addWidget(label_z, 0, 4, Qt::AlignRight);
    grid->addWidget(spinBox_z, 0, 5);
    grid->addWidget(label_s, 1, 0);
    grid->addWidget(spinBox_s, 1, 1);
    grid->addWidget(label_i, 1, 2);
    grid->addWidget(label_l, 1, 3);
    grid->addWidget(spinBox_lsize, 1, 4);

    groupBox->setLayout(grid);

    //Setting up the SIGNALS AND SLOTS

    QObject::connect(spinBox_lsize, SIGNAL(valueChanged(int)),
    glWidget, SLOT(setLedSize(int)));

    QObject::connect(spinBox_x, SIGNAL(valueChanged(int)),
                     glWidget, SLOT(setxDimensions(int)));
    QObject::connect(spinBox_y, SIGNAL(valueChanged(int)),
                     glWidget, SLOT(setyDimensions(int)));
    QObject::connect(spinBox_z, SIGNAL(valueChanged(int)),
                     glWidget, SLOT(setzDimensions(int)));
    QObject::connect(spinBox_s, SIGNAL(valueChanged(double)),
                     glWidget, SLOT(setSpacing(double)));

    //Styling the Widget

    spinBox_x->setStyleSheet("background-color:white;");
    spinBox_y->setStyleSheet("background-color:white;");
    spinBox_z->setStyleSheet("background-color:white;");
    spinBox_s->setStyleSheet("background-color:white;");
    spinBox_lsize->setStyleSheet("background-color:white;");

    label_x->setStyleSheet("color:white;");
    label_y->setStyleSheet("color:white;");
    label_z->setStyleSheet("color:white;");
    label_s->setStyleSheet("color:white;");
    label_i->setStyleSheet("color:white;");
    label_l->setStyleSheet("color:white;");

    groupBox->setMaximumHeight(150);
    return groupBox;
}
/* Function that returns the groupbox for the LEDColor to add to the layout
 */
QGroupBox *Window::LEDColor()
{
    QGroupBox *groupBox = new QGroupBox(tr("LED Color"));

    QRadioButton *radio_w = new QRadioButton("White");
    QRadioButton *radio_r = new QRadioButton("Red");
    QRadioButton *radio_g = new QRadioButton("Green");
    QRadioButton *radio_b = new QRadioButton("Blue");
    QRadioButton *radio_y = new QRadioButton("Yellow");

    radio_w->setChecked(true);

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(radio_w, 0, 2);
    grid->addWidget(radio_r, 0, 4);
    grid->addWidget(radio_g, 1, 1);
    grid->addWidget(radio_b, 1, 3);
    grid->addWidget(radio_y, 1, 5);
    groupBox->setLayout(grid);

    //Setting up the SIGNALS AND SLOTS

    connect(radio_r, SIGNAL(clicked(bool)), glWidget, SLOT(setColorRed(bool)));
    connect(radio_w, SIGNAL(clicked(bool)), glWidget, SLOT(setColorWhite(bool)));
    connect(radio_g, SIGNAL(clicked(bool)), glWidget, SLOT(setColorGreen(bool)));
    connect(radio_y, SIGNAL(clicked(bool)), glWidget, SLOT(setColorYellow(bool)));
    connect(radio_b, SIGNAL(clicked(bool)), glWidget, SLOT(setColorBlue(bool)));

    //Styling the Widget

    radio_w->setStyleSheet("color:white;");
    radio_r->setStyleSheet("color:white;");
    radio_g->setStyleSheet("color:white;");
    radio_b->setStyleSheet("color:white;");
    radio_y->setStyleSheet("color:white;");


    groupBox->setMaximumHeight(150);
    return groupBox;
}
/* Function that returns the groupbox for the Transforms to add to the layout
 */
QGroupBox *Window::Transforms()
{
    QGroupBox *groupBox = new QGroupBox(tr("Transforms"));

    QLabel *label_x = new QLabel("X-Rot:");
    QLabel *label_y = new QLabel("Y-Rot:");
    QLabel *label_z = new QLabel("Z-Rot:");
    QLabel *label_zoom = new QLabel("Zoom:");
    QLabel *label_transparency = new QLabel("Transparency:");

    QSlider* slider_x = new QSlider(Qt::Horizontal);
    slider_x->setRange(0, 360);

    QSlider* slider_y = new QSlider(Qt::Horizontal);
    slider_y->setRange(0, 360);

    QSlider* slider_z = new QSlider(Qt::Horizontal);
    slider_z->setRange(0, 360);

    QSlider* slider_zoom = new QSlider(Qt::Horizontal);
    slider_zoom->setRange(0,500);
    slider_zoom->setValue(50);

    QSlider* slider_transparency = new QSlider(Qt::Horizontal);
    slider_transparency->setRange(0,100);
    slider_transparency->setValue(50);

    QSpinBox *spinBox_x = new QSpinBox();
    spinBox_x->setRange(0,360);
    QSpinBox *spinBox_y = new QSpinBox();
    spinBox_y->setRange(0,360);
    QSpinBox *spinBox_z = new QSpinBox();
    spinBox_z->setRange(0,360);
    QSpinBox *spinBox_zoom = new QSpinBox();
    spinBox_zoom->setRange(0,500);
    QSpinBox *spinBox_transparency = new QSpinBox();
    spinBox_transparency->setRange(0,100);
    spinBox_transparency->setValue(50);

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(label_x, 0, 0);
    grid->addWidget(label_y, 1, 0);
    grid->addWidget(label_z, 2, 0);
    grid->addWidget(label_zoom, 3, 0);
    grid->addWidget(label_transparency, 4, 0);
    grid->addWidget(slider_x, 0, 1);
    grid->addWidget(slider_y, 1, 1);
    grid->addWidget(slider_z, 2, 1);
    grid->addWidget(slider_zoom, 3, 1);
    grid->addWidget(slider_transparency, 4, 1);
    grid->addWidget(spinBox_x, 0, 2);
    grid->addWidget(spinBox_y, 1, 2);
    grid->addWidget(spinBox_z, 2, 2);
    grid->addWidget(spinBox_zoom, 3, 2);
    grid->addWidget(spinBox_transparency, 4, 2);

    groupBox->setLayout(grid);

    //Setting up the SIGNALS AND SLOTS

    QObject::connect(spinBox_x, SIGNAL(valueChanged(int)),
    slider_x, SLOT(setValue(int)));
    QObject::connect(slider_x, SIGNAL(valueChanged(int)),
    spinBox_x, SLOT(setValue(int)));

    QObject::connect(spinBox_y, SIGNAL(valueChanged(int)),
    slider_y, SLOT(setValue(int)));
    QObject::connect(slider_y, SIGNAL(valueChanged(int)),
    spinBox_y, SLOT(setValue(int)));

    QObject::connect(spinBox_z, SIGNAL(valueChanged(int)),
    slider_z, SLOT(setValue(int)));
    QObject::connect(slider_z, SIGNAL(valueChanged(int)),
    spinBox_z, SLOT(setValue(int)));

    QObject::connect(spinBox_zoom, SIGNAL(valueChanged(int)),
    slider_zoom, SLOT(setValue(int)));
    QObject::connect(slider_zoom, SIGNAL(valueChanged(int)),
    spinBox_zoom, SLOT(setValue(int)));

    QObject::connect(spinBox_transparency, SIGNAL(valueChanged(int)),
    slider_transparency, SLOT(setValue(int)));
    QObject::connect(slider_transparency, SIGNAL(valueChanged(int)),
    spinBox_transparency, SLOT(setValue(int)));

    connect(slider_x, SIGNAL(valueChanged(int)), glWidget, SLOT(setXRotation(int)));
    connect(glWidget, SIGNAL(xRotationChanged(int)), slider_x, SLOT(setValue(int)));
    connect(slider_y, SIGNAL(valueChanged(int)), glWidget, SLOT(setYRotation(int)));
    connect(glWidget, SIGNAL(yRotationChanged(int)), slider_y, SLOT(setValue(int)));
    connect(slider_z, SIGNAL(valueChanged(int)), glWidget, SLOT(setZRotation(int)));
    connect(glWidget, SIGNAL(zRotationChanged(int)), slider_z, SLOT(setValue(int)));
    connect(slider_zoom, SIGNAL(valueChanged(int)), glWidget, SLOT(setScale(int)));
    connect(glWidget, SIGNAL(transparencyChanged(int)), slider_zoom, SLOT(setValue(int)));
    connect(slider_transparency, SIGNAL(valueChanged(int)), glWidget, SLOT(setTransparency(int)));
    connect(glWidget, SIGNAL(transparencyChanged(int)), slider_transparency, SLOT(setValue(int)));

    //Styling the Widget

    label_x->setStyleSheet("color:white;");
    label_y->setStyleSheet("color:white;");
    label_z->setStyleSheet("color:white;");
    label_zoom->setStyleSheet("color:white;");
    label_transparency->setStyleSheet("color:white;");

    spinBox_x->setStyleSheet("background-color:white;");
    spinBox_y->setStyleSheet("background-color:white;");
    spinBox_z->setStyleSheet("background-color:white;");
    spinBox_zoom->setStyleSheet("background-color:white;");
    spinBox_transparency->setStyleSheet("background-color:white;");

    groupBox->setMaximumHeight(150);

    return groupBox;
}



