// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

//  QML component to display received messages from other users.
Item{
    id:chatitem

    // Property to store the received message body.
    property string recvmsg: client.msgbody

    height: 30
    width: 250

    // Text field to display he received message.
    Rectangle{
        anchors.fill:parent
        color: "gray"
        Text {id:chatbox;color: "white";font.pixelSize: 20;clip: true; wrapMode: Text.WrapAnywhere;text:client.msgbody;width:parent.width;height: parent.height}
    }

    //Text to display the senders information
    Text{
        anchors.bottom: chatitem.top
        anchors.bottomMargin: 15
        visible: (client.msgfrom == "")?false:true
        color: "white"
        text: "From: " + client.msgfrom
        font.pixelSize: 15
    }
}
