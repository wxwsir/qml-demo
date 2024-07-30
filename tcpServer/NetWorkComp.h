#pragma once

#include <QHostInfo>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class NetWorks: public QObject{
    Q_OBJECT
public:
    NetWorks(QObject *parent = nullptr);
    ~NetWorks();
private slots:
    void do_newConnection();
    void do_socketStateChange(QAbstractSocket::SocketState socketState);
    void do_clientConnected();
    void do_clientDisconnected();
    void do_socketReadyRead();
signals:
    void staChanged(const QString &newState);
    void getMsgChanged(const QString &newMsg,int index);
public:
    //开始侦听，返回服务器地址和端口
    Q_INVOKABLE QString startListens(QString IP, quint16 port);
    //获取IP
    Q_INVOKABLE QString getLoIP(){
        return getLocalIP();
    }
    Q_INVOKABLE QString getClientConnectedInfo(){
        return connectedInfo;
    }
    Q_INVOKABLE QString getSocketState(){
        return m_state;
    }
    Q_INVOKABLE QString getClientdisConnectedInfo(){
        return disconnectedInfo;
    }
    Q_INVOKABLE QString sendMsg(QString msg){
        QByteArray str = msg.toUtf8();
        str.append("\n");
        tcpSocket->write(str);
        return "[out]: " + msg;
    }
    Q_INVOKABLE QString getMsg(){
        return socketReadyReadMsg;
    }

private:
    QTcpSocket *tcpSocket = nullptr;
    QTcpServer *tcpServer;
    QString listenInfo;
    QString m_state;
    QString connectedInfo;
    QString disconnectedInfo;
    QString socketReadyReadMsg;
    int index;
    QString getLocalIP();
};
