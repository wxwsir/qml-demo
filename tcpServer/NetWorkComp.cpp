#include "NetWorkComp.h"

NetWorks::NetWorks(QObject *parent): QObject(parent){
    m_state = "socket is null!";
    index = 0;
    QString localIP = getLocalIP();
    tcpServer = new QTcpServer(this);
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(do_newConnection()));
}

void NetWorks::do_newConnection()
{
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(do_clientConnected()));
    do_clientConnected();
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(do_clientDisconnected()));
    connect(tcpSocket,&QTcpSocket::stateChanged,this,&NetWorks::do_socketStateChange);
    do_socketStateChange(tcpSocket->state());
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(do_socketReadyRead()));
}

void NetWorks::do_socketStateChange(QAbstractSocket::SocketState state)
{
    switch (state) {
    case QAbstractSocket::ConnectedState:
        m_state = "ConnectedState";
        break;
    case QAbstractSocket::ConnectingState:
        m_state = "ConnectingState";
        break;
    case QAbstractSocket::UnconnectedState:
        m_state = "UnconnectedState";
        break;
    case QAbstractSocket::HostLookupState:
        m_state = "HostLookupState";
        break;
    case QAbstractSocket::BoundState:
        m_state = "BoundState";
        break;
    case QAbstractSocket::ListeningState:
        m_state = "ListeningState";
        break;
    case QAbstractSocket::ClosingState:
        m_state = "ClosingState";
        break;
    default:
        m_state = "";
        break;
    }
    emit staChanged(m_state);
    //qDebug()<<"do_socketStateChange: " << m_state;
}

void NetWorks::do_clientConnected()
{
    connectedInfo += "--client socket connected~";
    connectedInfo += "\n";
    connectedInfo += "--peer address: " + tcpSocket->peerAddress().toString();
    connectedInfo += "\n";
    connectedInfo += "--peer port: " + QString::number(tcpSocket->peerPort());
    connectedInfo += "\n";
    //qDebug() << "do_clientConnected";
}

void NetWorks::do_clientDisconnected()
{
    tcpSocket->deleteLater();
    disconnectedInfo = "client socket disconnected";
    //qDebug() << "do_clientDisconnected";
}

void NetWorks::do_socketReadyRead()
{
    while (tcpSocket->canReadLine()) {
        index++;
        socketReadyReadMsg = "[in]: " + tcpSocket->readLine();
    }
    emit getMsgChanged(socketReadyReadMsg, index);
    //qDebug()<<"do_socketReadyRead: " << socketReadyReadMsg;
}

//析构时断tcpSocket连接和tcpServer的监听
NetWorks::~NetWorks(){
    if(tcpSocket != nullptr){
        if(tcpSocket->state() == QTcpSocket::ConnectedState){
            tcpSocket->disconnectFromHost();
        }
    }
    if(tcpServer->isListening()){
        tcpServer->close();
    }
}

QString NetWorks::startListens(QString IP, quint16 port)
{
    QHostAddress addr(IP);
    //开始监听
    tcpServer->listen(addr,port);
    listenInfo += "--开始监听...";
    listenInfo += "\n";
    listenInfo += "--服务器地址: "+ tcpServer->serverAddress().toString();
    listenInfo += "\n";
    listenInfo += "--服务器端口: "+ QString::number(tcpServer->serverPort());
    listenInfo += "\n";
    //qDebug() << "startListens";
    return listenInfo;

}

QString NetWorks::getLocalIP()
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
