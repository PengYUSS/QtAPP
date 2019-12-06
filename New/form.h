#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QtMqtt/qmqttmessage.h>
#include <QtMqtt/qmqttsubscription.h>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QMqttSubscription *sub,QWidget *parent = nullptr);
    ~Form();

public slots:
    void updateMessage(const QMqttMessage &msg);
    void updateStatus(QMqttSubscription::SubscriptionState state);

private:
    Ui::Form *ui;
    QMqttSubscription *m_sub;
};

#endif // FORM_H
