#include "NetWork.h"

NetWork::NetWork(QObject *parent): QObject(parent){
    socketState = "socket is null!";
    index = 0;
    QString localIP = getLocalIP();
    tcpClient = new QTcpSocket(this);
    connect(tcpClient,SIGNAL(connected()),this,SLOT(do_connected()));
    connect(tcpClient,SIGNAL(disconnected()),this,SLOT(do_disconnected()));
    connect(tcpClient,&QTcpSocket::stateChanged,this,&NetWork::do_socketStateChange);
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(do_socketReadyRead()));
}

void NetWork::do_socketStateChange(QAbstractSocket::SocketState state)
{
    switch (state) {
    case QAbstractSocket::ConnectedState:
        socketState = "ConnectedState";
        break;
    case QAbstractSocket::ConnectingState:
        socketState = "ConnectingState";
        break;
    case QAbstractSocket::UnconnectedState:
        socketState = "UnconnectedState";
        break;
    case QAbstractSocket::HostLookupState:
        socketState = "HostLookupState";
        break;
    case QAbstractSocket::BoundState:
        socketState = "BoundState";
        break;
    case QAbstractSocket::ListeningState:
        socketState = "ListeningState";
        break;
    case QAbstractSocket::ClosingState:
        socketState = "ClosingState";
        break;
    default:
        socketState = "";
        break;
    }
    emit staChanged(socketState);
    //qDebug()<<"do_socketStateChange: " << state;
}

void NetWork::do_connected()
{
    connectedInfo += "--已连接到服务器~";
    connectedInfo += "\n";
    connectedInfo += "--peer address: " + tcpClient->peerAddress().toString();
    connectedInfo += "\n";
    connectedInfo += "--peer port: " + QString::number(tcpClient->peerPort());
    connectedInfo += "\n";
    //qDebug()<<"do_connected";
}

void NetWork::do_disconnected(){
    disconnectedInfo = "--已断开与服务器的连接~";
    //qDebug()<<"do_disconnected";
}

void NetWork::do_socketReadyRead()
{
    while (tcpClient->canReadLine()) {
        index++;
        socketReadyReadMsg = "[in]: " + tcpClient->readLine();
    }
    emit getMsgChanged(socketReadyReadMsg,index);
    //qDebug()<<"do_socketReadyRead: " << socketReadyReadMsg;
}

void NetWork::actConnect(QString IP, quint16 port)
{
    tcpClient->connectToHost(IP,port);
    //qDebug()<<"actConnect";
}

void NetWork::actDisConnect()
{
    if(tcpClient->state() == QAbstractSocket::ConnectedState){
        tcpClient->disconnectFromHost();
    }
    //qDebug()<<"actDisConnect";
}

NetWork::~NetWork() = default;

QString NetWork::getLocalIP()
{
    QString hostName = QHostInfo::localHostName();
    QHostInfo hostInfo= QHostInfo::fromName(hostName);
    QString localIP = "";
    QList<QHostAddress> addrList = hostInfo.addresses();
    if(addrList.isEmpty()){
        return localIP;
    }
    foreach(QHostAddress aHost,addrList){
        if(QAbstractSocket::IPv4Protocol== aHost.protocol()){
            localIP= aHost.toString();
            break;
        }
    }
    return localIP;
}
