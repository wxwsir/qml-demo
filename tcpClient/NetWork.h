#pragma once

#include <QHostInfo>
#include <QObject>
#include <QTcpSocket>
#include <QDebug>
class NetWork: public QObject{
    Q_OBJECT
public:
    NetWork(QObject *parent = nullptr);
    ~NetWork();
private slots:
    void do_socketStateChange(QAbstractSocket::SocketState socketState);
    void do_connected();
    void do_disconnected();
    void do_socketReadyRead();
signals:
    void staChanged(const QString &newState);
    void getMsgChanged(const QString &newMsg,int index);
public:
    //连接到服务器
    Q_INVOKABLE void actConnect(QString IP, quint16 port);
    //断开连接
    Q_INVOKABLE void actDisConnect();
    //获取IP
    Q_INVOKABLE QString getLoIP(){
        return getLocalIP();
    }
    //获取连接到服务器信息
    Q_INVOKABLE QString getConnectedInfo(){
        return connectedInfo;
    }
    //获取SocketState
    Q_INVOKABLE QString getSocketState(){
        return socketState;
    }
    //获取断开连接信息
    Q_INVOKABLE QString getDisConnectedInfo(){
        return disconnectedInfo;
    }
    //发送信息
    Q_INVOKABLE QString sendMsg(QString msg){
        QByteArray str = msg.toUtf8();
        str.append("\n");
        tcpClient->write(str);
        return "[out]: " + msg;
    }
    //获取信息
    Q_INVOKABLE QString getMsg(){
        return socketReadyReadMsg;
    }

private:
    QTcpSocket *tcpClient;
    QString socketState;
    QString connectedInfo;
    QString disconnectedInfo;
    QString socketReadyReadMsg;
    int index;
    QString getLocalIP();
};
