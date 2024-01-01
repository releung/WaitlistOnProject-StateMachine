
#include "widget.h"
#include "myPlayer.h"
#include <QString>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    Player* player = new Player();
    qDebug()<< __PRETTY_FUNCTION__ << __LINE__  << "OpenClose"; player->OpenClose();
    qDebug()<< __PRETTY_FUNCTION__ << __LINE__  << "OpenClose"; player->OpenClose();
    qDebug()<< __PRETTY_FUNCTION__ << __LINE__  << "Play"; player->Play(QString("file").toStdString());
    qDebug()<< __PRETTY_FUNCTION__ << __LINE__  << "Pause"; player->Pause();
//    qDebug()<< __PRETTY_FUNCTION__ << __LINE__  << "EndPause"; player->EndPause();
    qDebug()<< __PRETTY_FUNCTION__ << __LINE__  << "Stop"; player->Stop();
    qDebug()<< __PRETTY_FUNCTION__ << __LINE__  << "Play"; player->Play(QString("file").toStdString());
    qDebug()<< __PRETTY_FUNCTION__ << __LINE__  << "Play"; player->Play(QString("file").toStdString());
    qDebug()<< __PRETTY_FUNCTION__ << __LINE__  << "OpenClose"; player->OpenClose();
}

Widget::~Widget()
{
}


