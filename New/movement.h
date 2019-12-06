#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <opencv2/highgui.hpp>
#include <QWidget>
#include <mainwindow.h>
#include "ui_mainwindow.h"

using namespace cv;

class movement : public QObject
{
        Q_OBJECT
public:
    movement();
    void detect(Mat mask,Mat img);

    MainWindow *ma = new MainWindow;

signals:
    void sendText(const QString & data);
};

#endif // MOVEMENT_H
