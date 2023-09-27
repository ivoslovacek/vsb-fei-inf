#include <iostream>
#include <thread>
#include <cstring>
#include <ctime>
#include "networking.hpp"

void udpstuff()
{
    UDPClient client("158.196.135.85", 8010);

    const size_t len = 2048;
    uint8_t *buf = new uint8_t[len];
    char address_str[INET_ADDRSTRLEN];

    while(true)
    {
        memset(buf, 0, len);
        client.receiveMsg(buf, len);

        sockaddr_in address;
        memcpy(&address, buf, sizeof(sockaddr_in));
        inet_ntop(AF_INET, &address, address_str, INET_ADDRSTRLEN);

        time_t msg_time;
        memcpy(&msg_time, buf + 4, sizeof(time_t));
        time(&msg_time);

        size_t msg_len = buf[8];

        uint8_t crc = buf[9 + msg_len];
        uint8_t calculated_crc = buf[0];
        for(int i = 1; i < 9 + msg_len; i++)
        {
            calculated_crc ^= buf[i];
        }

        char *msg = new char[msg_len + 1];
        memcpy(msg, buf + 9, msg_len);
        msg[msg_len] = 0; 

        std::cout << "Message from " << address_str << " at " << ctime(&msg_time);
        std::cout << msg << std::endl;
        std::cout << "Calculated CRC: " << (int)calculated_crc << " Received CRC: " << (int)crc << std::endl;
   
        delete msg;
    }

    delete buf;
}

void tcpstuff()
{
    TCPClient client("158.196.135.85", 8000);

    std::string buf;

    while(true)
    {
        std::cin >> buf;

        buf += '\n';
        
        client.sendMsg(buf.c_str(), buf.size());
    }
}

int main()
{
    std::thread udp_thread(udpstuff);
    std::thread tcp_thread(tcpstuff);

    udp_thread.join();
    tcp_thread.join();

    return 0;
}