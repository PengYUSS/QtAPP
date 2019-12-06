#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QtMqtt/qmqttclient.h>
#include <opencv2/highgui.hpp>
#include <QWidget>


using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *ui;
    QMqttClient *m_client;

    QString DA;

public slots:
    void setClientPort(int p);
    void updateText(const QString & data);

private slots:
    void on_buttonConnect_clicked();
    void on_buttonQuit_clicked();
    void updateLogStateChange();

    void brokerDisconnected();

    void on_buttonPublish_clicked();

    void on_buttonSubscrible_clicked();

    void on_buttonPing_clicked();

//private:
  //  Ui::MainWindow *ui;
  // QMqttClient *m_client;
};

#endif // MAINWINDOW_H
