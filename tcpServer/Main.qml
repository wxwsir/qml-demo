import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import NetWork

//服务器端
ApplicationWindow {
    id: window
    visible: true
    width: 400
    height: 300
    title: "TCP Server"
    //监听信息
    property string lis_text: ""
    property string listens: "未监听"
    property string outMsg: ""
    property string inMsg: ""
    property string iP: addrText.text
    property string port: portText.text
    //网络组件
    NetWorkComp {
        id: netWorkComp
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
                text: "开始监听"
                onClicked: {
                    lis_text = netWorkComp.startListens(iP, parseInt(port))
                    listens = "正在监听"
                }
            }
            Button {
                text: "停止监听"
                onClicked: {
                    listens = "监听已关闭"
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
                text: "监听地址:"
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
                text: "监听端口:"
            }
            TextField {
                id: portText
                text: "1200"
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
                    outMsg += netWorkComp.sendMsg(sendTextfield.text)
                    outMsg += "\n"
                }
            }
        }
        // 日志显示区域
        TextArea {
            Layout.fillWidth: true
            Layout.fillHeight: true
            readOnly: true
            text: netWorkComp.getClientConnectedInfo() +
                  netWorkComp.getClientdisConnectedInfo()
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
                target: netWorkComp
                function onGetMsgChanged(newMsg){
                    inMsg += newMsg;
                }
            }
        }
        // 底部状态栏
        RowLayout {
            Layout.fillWidth: true
            spacing: 10

            Label {
                text: "监听状态："
            }
            Label {
                text: listens
                color: "green"
            }
            Item { Layout.fillWidth: true }
            Label {
                text: "socket状态: "
            }
            Label {
                id: lla
                text: netWorkComp.getSocketState()
                color: "green"
                Connections {
                    target: netWorkComp
                    function onStaChanged(newState){
                        lla.text = newState
                    }
                }
            }
        }
    }
}
