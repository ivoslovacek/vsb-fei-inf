#pragma once
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#define UDP_PORT 9020
#define TCP_PORT 8000

class Networking
{
  protected:
    struct sockaddr_in server_addr;
    int socket_fd;

  public:
    ~Networking();

    virtual void sendMsg(const char *buf, size_t len) = 0;
    virtual void receiveMsg(void *buf, size_t len) = 0;
};

class TCPClient : Networking
{
  private:
  public:
    TCPClient(std::string address, uint16_t port);

    void sendMsg(const char *buf, size_t len);
    void receiveMsg(void *buf, size_t len);
};

class UDPClient : Networking
{
  private:
    sockaddr_in client_addr;

  public:
    UDPClient(std::string address, uint16_t port);

    void sendMsg(const char *buf, size_t len);
    void receiveMsg(void *buf, size_t len);
};
