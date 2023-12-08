#include "qsignalstation.h"

QSignalStation::QSignalStation(QObject* parent):QObject(parent)
{
    m_matchs.clear();
    m_senders.clear();
    m_receivers.clear();
}

QSignalStation::~QSignalStation()
{

}

template<class T>
bool QSignalStation::exisitName(std::list<T> list, const QString name, std::function<QString&(T&)> func)
{
    auto iterObj = std::find_if(list.begin(), list.end(), [&name, &func](T& data){
        return func(data) == name; });

    if(iterObj == list.end())
        return false;

    return true;
}

bool QSignalStation::joinSender(const QObject *sender, const char *signal, \
                const QString specialName, Qt::ConnectionType type)
{
    if(exisitName<Sender>(m_senders, specialName, &Sender::name)) {
        qCritical("special name is used, please give a new specail name!");
        return false;
    }

    Sender obj = { sender, signal, specialName, type };
    m_senders.push_back(obj);

    auto reciverObj = std::find_if(m_receivers.begin(), m_receivers.end(), \
        [&specialName](Receiver& data){
            return data.specialName == specialName; });

    if(reciverObj == m_receivers.end())
        return false;



    connect(obj.sendObj, obj.signal, \
        reciverObj->recvObj, reciverObj->method, obj.type);
    return true;
}

bool QSignalStation::joinRecver(const QObject *recvObj, const char *method, \
                const QString specialName)
{
    if(exisitName<Receiver>(m_receivers, specialName, &Receiver::name)) {
        qCritical("special name is used, please give a new specail name!");
        return false;
    }

    Receiver obj = { recvObj, method, specialName };
    m_receivers.push_back(obj);

    auto sendObj = std::find_if(m_senders.begin(), m_senders.end(), \
        [&specialName](Sender& data){
        return data.specialName == specialName; });

    if(sendObj == m_senders.end())
        return false;


    connect(sendObj->sendObj, sendObj->signal, \
        obj.recvObj, obj.method, (Qt::ConnectionType)sendObj->type);

    return true;
}
