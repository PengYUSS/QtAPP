#include "form.h"
#include "ui_form.h"

Form::Form(QMqttSubscription *sub,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form),
    m_sub(sub)
{
    ui->setupUi(this);

    ui->labelSub->setText(m_sub->topic().filter());
    ui->labelQoS->setText(QString::number(m_sub->qos()));
    updateStatus(m_sub->state());
    connect(m_sub, &QMqttSubscription::messageReceived, this, &Form::updateMessage);
    connect(m_sub, &QMqttSubscription::stateChanged, this, &Form::updateStatus);
    connect(m_sub, &QMqttSubscription::qosChanged, [this](quint8 qos){
        ui->labelQoS->setText(QString::number(qos));
    });
    connect(ui->pushButton, &QAbstractButton::clicked, m_sub, &QMqttSubscription::unsubscribe);
}

Form::~Form()
{
    delete ui;
}

void Form::updateStatus(QMqttSubscription::SubscriptionState state)
{
    switch(state){
    case QMqttSubscription::Unsubscribed:
        ui->labelStatus->setText(QLatin1String("Unsubscribed"));
        break;

    case QMqttSubscription::SubscriptionPending:
        ui->labelStatus->setText(QLatin1String("Pending"));
        break;

    case QMqttSubscription::Subscribed:
        ui->labelStatus->setText(QLatin1String("Subscribed"));
        break;

    case QMqttSubscription::Error:
        ui->labelStatus->setText(QLatin1String("Error"));
        break;

    default:
        ui->labelStatus->setText(QLatin1String("--Unknown--"));
        break;
    }
}

void Form::updateMessage(const QMqttMessage &msg)
{
    ui->listWidget->addItem(msg.payload());
}

