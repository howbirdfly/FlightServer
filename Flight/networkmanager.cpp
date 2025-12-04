#include "networkmanager.h"
#include <QDebug>

NetworkManager* NetworkManager::m_instance = nullptr;

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
    , m_client(nullptr)
{
    m_client = new NetworkClient(this);
}

NetworkManager* NetworkManager::instance()
{
    if (!m_instance) {
        m_instance = new NetworkManager();
    }
    return m_instance;
}

bool NetworkManager::connectToServer(const QString &host, quint16 port)
{
    return m_client->connectToServer(host, port);
}

