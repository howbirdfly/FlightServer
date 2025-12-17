#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "networkclient.h"

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    static NetworkManager* instance();
    NetworkClient* client() { return m_client; }
    
    bool connectToServer(const QString &host = "47.112.202.223", quint16 port = 8080);

private:
    NetworkManager(QObject *parent = nullptr);
    static NetworkManager* m_instance;
    NetworkClient *m_client;
};

#endif // NETWORKMANAGER_H

