#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <qxmpp/QXmppClient.h>
#include <qmlapplicationviewer.h>

#include "model.h"

/// ChatClient class derived from QXmppClient class in order to use the
/// QXmpp functionality.
class ChatClient: public QXmppClient
{
    Q_OBJECT

public:
    ChatClient(QObject *parent = 0);
    ~ChatClient();

    /// static pointer object to class QmlApplictionViewer.
    static QmlApplicationViewer *viewer;
    Q_INVOKABLE QString presenceToStatusText(const QXmppPresence& presence);
    Q_INVOKABLE QString getPresence(const QString&);
    Q_INVOKABLE QString getClientPresence ();

signals:
    void rosterReceivedfromServer();
    void chatMessageReceived(QString from,QString msg);
    void errorSignal(QString errmsg);
    void userPresenceChanged();

public slots:
    void messageReceived(const QXmppMessage&);
    void presenceChanged(const QString&,
                         const QString&);
    void clientConnected();
    void clientDisconnected();
    void rosterReceived();
    void errorReceived(QXmppClient::Error);


private:   
    Model* rosterModel;
};

#endif // CHATCLIENT_H
