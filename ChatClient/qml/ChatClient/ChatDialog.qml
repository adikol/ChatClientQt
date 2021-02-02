// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

// QML component to initiate chat converstaions.
Item{
    id:chatitem
    property variant object;
    height: 30
    width: 250

    // Text to display the receipient of the message
    Text{
        id:totext
        anchors.bottom: chatitem.top
        anchors.bottomMargin: 15
        visible: (client.msgto == "")?false:true
        color: "white"
        text: "To: " + client.msgto
        font.pixelSize: 15
    }

    // Text Input field used to input message to be sent.
    Rectangle{
        id:textinput
        anchors.fill:parent
        color: "gray"       
        TextInput {id:chatbox;anchors.fill: parent ;width: 250; color: "black"; cursorVisible: true;font.pixelSize: 20 }
    }

    // Button when clicked sends the message to receipient
    Rectangle{
        id:sendbutton
        anchors.top: chatitem.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        height: 30
        width: 50

        //! Mouse area covering send button
        MouseArea {
            anchors.fill: parent
            onClicked: {
                chatitem.sendmessage()
            }
        }

        // Text to be displayed on the send button
        Text {
            text: qsTr("Send")
            anchors.centerIn: parent
            color: "black"
        }
    }

    // Helper function to initiate message send, calls the qxmmp library function.
    // Clears the text input field
    function sendmessage()
    {
        console.log("message sent to :" + client.msgto);
        client.sendMessage(client.msgto,chatbox.text);
        chatbox.text = ""
    }
}



