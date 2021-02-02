#include "chatclient.h"
#include "qxmpp/QXmppMessage.h"
#include "qxmpp/QXmppRosterManager.h"
#include "qmlapplicationviewer.h"
#include <qdeclarative.h>
#include <QDeclarativeContext>
#include <QStringlistModel>
#include <iostream>
using namespace std;

/// Definition of the QmlApplicationViewer pointer object.
QmlApplicationViewer *ChatClient::viewer;

/// Constructor of the class ChatClient
ChatClient::ChatClient(QObject *parent)
    : QXmppClient(parent)
{
    //Initialize all the signals ans slots
    //Assert if any fails.
    bool check;
    Q_UNUSED(check);


    check = connect(this, SIGNAL(error(QXmppClient::Error)),
                    SLOT(errorReceived(QXmppClient::Error)));

    Q_ASSERT(check);

    check = connect(this, SIGNAL(connected()),
                    SLOT(clientConnected()));
    Q_ASSERT(check);

    check = connect(this, SIGNAL(disconnected()),
                    SLOT(clientDisconnected()));
    Q_ASSERT(check);

    check = connect(&this->rosterManager(), SIGNAL(rosterReceived()),
                    SLOT(rosterReceived()));
    Q_ASSERT(check);

    check = connect(this, SIGNAL(messageReceived(const QXmppMessage&)),
                    SLOT(messageReceived(const QXmppMessage&)));
    Q_ASSERT(check);
}

/// Destructor of the class ChatClient
ChatClient::~ChatClient()
{
    delete rosterModel;
}

/// slot called when an error occurs.
void ChatClient::errorReceived(QXmppClient::Error error)
{
    qDebug("Error in connecting");

    switch(error)
    {
    case NoError:
        qDebug("NoError");
        emit errorSignal("NoError");
        break;
    case SocketError :
        qDebug("SocketError");
        emit errorSignal("SocketError");
        break;
    case KeepAliveError :
        qDebug("KeepAliveError");
        emit errorSignal("KeepAliveError");
        break;
    case XmppStreamError :
        qDebug("XmppStreamError");
        emit errorSignal("XmppStreamError");
        break;

    }
}

/// slot called when client connects to server
void ChatClient::clientConnected()
{
    qDebug("Connected to Server");
}

/// slot called when client disconnects from server
void ChatClient::clientDisconnected()
{
    qDebug("Disconnected from Server");
}


/// slot called when roster is received
/// here roster data is given as input to ListModes so as
/// to display in a list view.
void ChatClient::rosterReceived()
{
    qDebug("roster Received");

    QStringList listModel = rosterManager().getRosterBareJids();

    rosterModel = new Model(listModel,this);

    ChatClient::viewer->rootContext()->setContextProperty("rosterModel",rosterModel );    

    /// Then QXmppRoster::presenceChanged() is emitted whenever presence of someone
    /// in roster changes
    bool check = connect(&this->rosterManager(), SIGNAL(presenceChanged(QString,QString)),
                         SLOT(presenceChanged(QString,QString)));
    Q_ASSERT(check);


    emit rosterReceivedfromServer();
}


/// slot where message sent to this client is received
/// here getFrom() gives the sender and getBody() gives the message
/// using the function sendPacket message is sent to the sender
void ChatClient::messageReceived(const QXmppMessage& message)
{
    qDebug("Message received");
    QString from = message.from();
    QString msg = message.body();

    emit chatMessageReceived(from,msg);
}

/// slot called when presence of any buddies added in the roster changes.
void ChatClient::presenceChanged(const QString& id,
                                 const QString& resource)
{
    cout << "presence changed" << endl;
   // getPresence(id);
    emit userPresenceChanged();
}

QString ChatClient::getPresence(const QString& jid)
{
    cout << "In getPresence function:" << endl;
    QString resource;
    QStringList resources = this->rosterManager().getResources(jid);
    for(int i = 0; i < resources.count(); ++i)
    {
        resource = resources.at(i);
        QXmppPresence presence = rosterManager().getPresence(jid, resource);
        return presenceToStatusText(presence);
    }
    QXmppPresence presence = rosterManager().getPresence(jid, resource);
    return presenceToStatusText(presence);
}

QString ChatClient::presenceToStatusText(const QXmppPresence& presence)
{
    QString statusText = presence.status().statusText();
    if(statusText.isEmpty())
    {
        if(presence.type() == QXmppPresence::Available)
        {
            switch(presence.status().type())
            {
            //case QXmppPresence::Status::Invisible:
            case QXmppPresence::Status::Offline:
                statusText = "Offline";
                break;
            case QXmppPresence::Status::Online:
            case QXmppPresence::Status::Chat:
                statusText = "Available";
                break;
            case QXmppPresence::Status::Away:
            case QXmppPresence::Status::XA:
                statusText = "Idle";
                break;
            case QXmppPresence::Status::DND:
                statusText = "Busy";
                break;
            }
        }
        else
            statusText = "Offline";
    }

    return statusText;
}


QString ChatClient::getClientPresence(){
    QXmppPresence presence = clientPresence();
    return presenceToStatusText(presence);
}
