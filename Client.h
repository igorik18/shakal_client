//
// Created by Igor on 16.10.2018.
//

#ifndef ZHAKAL2_CLIENT_H
#define ZHAKAL2_CLIENT_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <cstring>

using namespace std;
using namespace sf;

struct Transfer
{
    int integer;
    string data;
    float f;
    double d;
    bool logic;
};

class Client {
private:
    TcpSocket client;
public:
    Client();
    Client(IpAddress ip, size_t port, bool blocked = true);

    Socket::Status ConnectTo(IpAddress ip, size_t port);

    void Disconnect();

    bool Send(int number);
    bool Send(string data);
    bool Send(double number);
    bool Send(bool logic);
    bool Send(Packet packet);
    bool Send(Transfer transfer);

    int GetIntMessage(bool &check);
    string GetStringMessage(bool &check);
    double GetDoubleMessage(bool &check);
    bool GetBoolMessage(bool &check);
    Packet GetPacketMessage(bool &check);
    Transfer GetTransferMessage(bool &check);

    IpAddress getIp();
    size_t getPort();

    TcpSocket &getClient();

    void SetBlock(bool block);
    bool IsBlocking();

    void check_status(Socket::Status status);
};




#endif //ZHAKAL2_CLIENT_H
