import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import NetWork

ApplicationWindow {
    id: window
    visible: true
    width: 400
    height: 300
    title: "TCP Client"
    property string outMsg: ""
    property string inMsg: ""
    property string iP: addrText.text
    property string port: portText.text
    //客户端组件
    NetWork {
        id: network
    }
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        // 顶部按钮栏
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Button {
                text: "连接服务器"
                onClicked: {
                    network.actConnect(iP,parseInt(port))
                }
            }
            Button {
                text: "断开连接"
                onClicked: {
                    network.actDisConnect()
                }
            }
            Button {
                text: "清空文本框"
                onClicked: {
                    sendTextfield.text = ""
                }
            }
            Button {
                text: "退出"
                onClicked: {
                    window.close()
                }
            }
        }

        // 监听地址和端口
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Label {
                text: "服务器地址:"
            }
            TextField {
                id: addrText
                text: ""
                Layout.fillWidth: true
                Keys.onReturnPressed: {
                    console.log(addrText.text)
                }
            }
            Label {
                text: "端口:"
            }
            TextField {
                id: portText
                text: ""
                Layout.preferredWidth: 60
                Keys.onReturnPressed: {
                    console.log(portText.text)
                }
            }
        }
        RowLayout {
            Layout.fillWidth: true
            spacing: 10
            // 发送消息框
            TextField {
                id: sendTextfield
                placeholderText: "输入要发送的消息"
                text: ""
            }
            Button {
                text: "发送消息"
                onClicked: {
                    outMsg += network.sendMsg(sendTextfield.text)
                    outMsg += "\n"
                }
            }
        }
        // 日志显示区域
        TextArea {
            Layout.fillWidth: true
            Layout.fillHeight: true
            readOnly: true
            text: network.getConnectedInfo() +
                  network.getDisConnectedInfo()
        }
        TextArea {
            Layout.fillWidth: true
            Layout.fillHeight: true
            readOnly: true
            text: outMsg
        }
        TextArea {
            id: taa
            Layout.fillWidth: true
            Layout.fillHeight: true
            readOnly: true
            text: inMsg
            Connections {
                target: network
                function onGetMsgChanged(newMsg){
                    inMsg = newMsg
                }
            }
        }
        // 底部状态栏
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Label {
                text: "socket状态: "
            }
            Label {
                id: lla
                text: network.getSocketState()
                color: "green"
                Connections {
                    target: network
                    function onStaChanged(newState){
                        lla.text += newState
                    }
                }
            }
        }
    }
}

