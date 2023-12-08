#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDebug>
#include "qsignalstation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class A;
class B;
class C;
class D;

class D : public QObject
{
    Q_OBJECT
public:
    explicit D(QObject* parent = 0):QObject() {
        QSignalStation::instance()->joinRecver(this, SLOT(onReciverD(const QString)), CONN_SIGB_SLOTD);
        QSignalStation::instance()->joinSender(this, SIGNAL(signalsD(const QString)), CONN_SIGD_SLOTB);
    }

public slots:
    void onReciverD(const QString className) {
        qDebug() << "class D reciver: " << className;
    }

signals:
    void signalsD(const QString& data);
};

class C : public QObject
{
    Q_OBJECT
public:
    explicit C(QObject* parent = 0):QObject() {
    }

    void sendData(const QString& data ) {
        emit d.signalsD(data);
    };

private:
    D d;

};

class B : public QObject
{
    Q_OBJECT
public:
    explicit B(QObject* parent = 0):QObject() {
        QSignalStation::instance()->joinRecver(this, SLOT(onReciverB(const QString)), CONN_SIGD_SLOTB);
        QSignalStation::instance()->joinSender(this, SIGNAL(signalsB(const QString)), CONN_SIGB_SLOTD);
    }

signals:
    void signalsB(const QString& data);

public slots:
    void onReciverB(const QString& data) {
        qDebug() << "class B reciver: " << data;
    }
};

class A : public QObject
{
    Q_OBJECT
public:
    explicit A(QObject* parent = 0):QObject(parent) {
    }

    void sendData(const QString& data ) {
        emit b.signalsB(data);
    };
private:
    B b;
};



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    A m_a;
    C m_c;
};
#endif // MAINWINDOW_H
