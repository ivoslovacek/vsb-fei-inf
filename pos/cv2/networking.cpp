#include "networking.hpp"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>

Networking::~Networking()
{
    close(this->socket_fd);
}

TCPClient::TCPClient(std::string address, uint16_t port)
{
    this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&this->server_addr, 0, sizeof(this->server_addr));
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_port = htons(port);
    inet_pton(AF_INET, address.c_str(), &this->server_addr.sin_addr);

    if (connect(this->socket_fd, (struct sockaddr *)&this->server_addr, sizeof(this->server_addr)) != 0)
    {
        std::cerr << "Couldn't establish connection to " << address << ":" << port;
        exit(1);
    }
}

void TCPClient::receiveMsg(void *buf, size_t len)
{
    recv(this->socket_fd, buf, len, 0);
}

void TCPClient::sendMsg(const char *buf, size_t len)
{
    send(this->socket_fd, buf, len, 0);
}

UDPClient::UDPClient(std::string address, uint16_t port)
{
    this->socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    int broadcast_enable = 1;
    setsockopt(this->socket_fd, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable));

    memset(&this->client_addr, 0, sizeof(this->client_addr));
    memset(&this->server_addr, 0, sizeof(this->server_addr));

    this->client_addr.sin_family = AF_INET;
    this->client_addr.sin_port = htons(port);
    this->client_addr.sin_addr.s_addr = INADDR_ANY;

    bind(this->socket_fd, (sockaddr *)&this->client_addr, sizeof(this->client_addr));
}

void UDPClient::sendMsg(const char *buf, size_t len)
{
    socklen_t server_len = sizeof(this->server_addr);

    sendto(this->socket_fd, buf, len, 0, (struct sockaddr *)&this->server_addr, server_len);
}

void UDPClient::receiveMsg(void *buf, size_t len)
{
    socklen_t server_len = sizeof(this->server_addr);

    recvfrom(this->socket_fd, buf, len, 0, (struct sockaddr *)&this->server_addr, &server_len);
}
