// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.mine.chat 1.0


//QML main component to display the login dialogs and the
// List view of contacts after succesful authentication


Rectangle {
    id:mainwindow
    property string userid : ""
    width: 360
    height: 480
    color: "darkgray"

    // Heading showing
    Text {
        id:heading
        font.bold: true
        text: (userid == "")? qsTr("XMPP Chat Client"): qsTr(userid + " (" + getClientPresence() + ")")
        anchors {top: parent.top; topMargin: 5; horizontalCenter: parent.horizontalCenter}
    }

    // Text message shown while connecting to the server.
    Text {
        id: waitmsg
        visible:false
        anchors.bottom: parent.bottom
        anchors.bottomMargin:175
        anchors.horizontalCenter: parent.horizontalCenter
        color: "white"
        font.pixelSize: 25
        text: qsTr("Connecting...")
    }


    // Login button when clicked the application connects to the server with Username and password.
    Rectangle {
        id:loginbutton
        //  visible: (pageLoader.source=="")? true:false
        width: 60
        height: 20
        radius: 5
        color: "gray"
        anchors {top: parent.top; margins: 5; centerIn: parent}

        //Text shown the login button
        Text {
            text: qsTr("Login")
            color: "white"
            font.pixelSize: 12
            anchors.centerIn: parent
        }

        // Mouse area covers the login button, when clicked collects
        // the username and password from the respective fields and
        // sends request for authentication to the server.
        MouseArea {
            anchors.fill: parent
            onClicked: {
                loginpanel.visible = false;
                loginbutton.visible = false;
                waitmsg.visible = true;
                waitmsg.text = qsTr("Connecting...");
                console.log("calling connect");
                console.log(username.text + password.text);
                userid = username.text;
                client.connectToServer(userid,password.text);
            }
        }
    }


    // Login Username and Password fields.
    Rectangle{
        id:loginpanel
        color: "gray"
        height: 75
        width: 200
        radius: 10
        anchors{bottom: loginbutton.top; bottomMargin: 20;horizontalCenter: parent.horizontalCenter}

        Grid {
            anchors{left:parent.left;top:parent.top;topMargin: 18;leftMargin: 10}
            columns: 2
            spacing: 5
            Text {font.bold: true; color: "white"; text: "Username:";width: 60; height: 20 }
            TextInput {id:username; maximumLength:25;cursorVisible: true; color: "white"; width: 100; height: 20 ;}
            Text {font.bold: true; color: "white"; text: "Password:" ;width: 55; height: 20 }
            TextInput {id:password;maximumLength:25;echoMode: TextInput.Password; color: "white"; width: 100; height: 20 }
        }
    }


    // Instantiation of the ChatClient class from the C++ code.
    ChatClient{
        id:client
        property string msgfrom
        property string msgbody
        property string msgto

        // Handler called when Roster is received from server.
        onRosterReceivedfromServer:{
            console.log("roster received")
            waitmsg.visible = false
            listviewloader.sourceComponent = listviewcomponent
        }

        // Handler called when chat message is received from server.
        onChatMessageReceived:{
            msgfrom = from
            if(msg!= "")
                msgbody = msg
            loader.source = "MsgReceived.qml"
        }

        onErrorSignal:{
            waitmsg.text = errmsg;
            loginpanel.visible = true;
            loginbutton.visible = true;
        }

        onUserPresenceChanged:{
            listviewloader.sourceComponent = null
            listviewloader.sourceComponent = listviewcomponent
        }
    }

    Component{
        id:listviewcomponent

        //List view to display the list of the contacts.
        ListView {
            id: folderlistview
            anchors.fill: parent

            clip: true

            // Model containing the list of contacts ( Roster data)
            model: rosterModel

            // Delegate to display the list of contacts.
            delegate: Item{
                height: 40
                width: parent.width
                Rectangle {
                    id: listItem
                    anchors.centerIn: parent
                    color: (mouseArea.pressed)? "lightblue": "gray"
                    height: 35
                    width: parent.width

                    Text{
                        id:delegatetext
                        anchors{centerIn: parent}
                        //text: model.user
                        text: rosterModel.returnSubmodelForData(index) + "  (" +getUserPresence(rosterModel.returnSubmodelForData(index)) + ")"
                        //text:rosterModel.returnSubmodelForData();
                        font.pixelSize: 20
                        color: "white"
                    }

                    //! Mouse area covering every single selected listview item
                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent

                        onDoubleClicked: {
                            folderlistview.currentIndex = index;
                            client.msgto = rosterModel.returnSubmodelForData(index)
                            loader.source = "ChatDialog.qml"
                        }
                    }
                }
            }
        }
    }

    //used to load new components.
    Loader{
        id:listviewloader
        anchors.fill: parent
        anchors.topMargin: 30
    }


    //used to load new components.
    Loader{
        id:loader
        anchors.bottom:parent.bottom
        anchors.bottomMargin: 60
        anchors.horizontalCenter: parent.horizontalCenter
    }

    // Helper function to get user presence information
    function getUserPresence(contactname)
    {
        console.log("getting presence for " + contactname );
        return client.getPresence(contactname);
    }

    // Helper function to get client presence information
    function getClientPresence()
    {
        console.log("getting presence for me");
        return client.getClientPresence();
    }
}
