/***********************************************************
! @File        : qsignalstation.h
 *  @Brief       : 这个是个单实例类,多层级的信号通信,直接发到这里进行转发
 *  @Details     : 详细说明
 *  @Author      : soda
 *  @Date        : 2023-12-08 10:33:57
 *  @Version     : v1.0
 *  @Copyright   : Copyright By soda, All Rights Reserved
 ***********************************************************/
#pragma once
#include <QObject>
#include <QMetaMethod>
#include <singleton.h>

#define CONN_SIGB_SLOTD     "CONN_SIGB_SLOTD"
#define CONN_SIGD_SLOTB     "CONN_SIGD_SLOTB"

using Sender = struct Sender { \
    const QObject *sendObj;
    const char *signal;
    QString specialName;
    Qt::ConnectionType type;
    QString& name() {
        return specialName;
    }
};

using Receiver = struct Receiver { \
    const QObject* recvObj;
    const char *method;
    QString specialName;
    QString& name() {
        return specialName;
    }
};

class QSignalStation : public QObject
{
    Q_OBJECT
public:
    explicit QSignalStation(QObject* parent = 0);
    ~QSignalStation();

    SINGLETON_DEFINE(QSignalStation)
    bool joinSender(const QObject *sender, const char *signal, \
                    const QString specialName, Qt::ConnectionType = Qt::AutoConnection);

    bool joinRecver(const QObject *recvObj, const char *method, \
                    const QString specialName);

private:
    template<class T>
    bool exisitName(std::list<T> list, const QString name, std::function<QString&(T&)> func);

    std::list<Sender> m_senders;
    std::list<Receiver> m_receivers;
    QStringList m_matchs;
};


