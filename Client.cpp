//
// Created by Igor on 16.10.2018.
//

#include "Client.h"
Client::Client()
{

}



Client::Client(IpAddress ip, size_t port, bool blocked)
{
    client.setBlocking(blocked);
    client.connect(ip, port);
}

Socket::Status Client::ConnectTo(IpAddress ip, size_t port)
{
    return client.connect(ip, port);
}

void Client::Disconnect()
{
    client.disconnect();
}

bool Client::Send(int number)
{
    Packet packet;
    packet << number;

    Socket::Status status = status = client.send(packet);


        if (status == Socket::Status::Done)
        {
            return true;
        }
        else
        {
            check_status(status);
            return false;
        }
}

bool Client::Send(string data) {
    Packet packet;
    packet << data;


    Socket::Status status = client.send(packet);
    if (status == Socket::Status::Done)
    {
        return true;
    }
    else
    {
        check_status(status);
        return false;
    }
}

bool Client::Send(double number) {
    Packet packet;
    packet << number;

    Socket::Status status = client.send(packet);
    if (status == Socket::Status::Done)
    {
        return true;
    }
    else
    {
        check_status(status);
        return false;
    }
}

bool Client::Send(bool logic) {
    Packet packet;
    packet << logic;

    Socket::Status status = client.send(packet);
    if (status == Socket::Status::Done)
    {
        return true;
    }
    else
    {
        check_status(status);
        return false;
    }
}

bool Client::Send(Packet packet) {
    Socket::Status status = client.send(packet);
    if (status == Socket::Status::Done)
    {
        return true;
    }
    else
    {
        check_status(status);
        return false;
    }
}

bool Client::Send(Transfer transfer) {
    Packet packet;
    packet << transfer.integer
           << transfer.data
           << transfer.f
           << transfer.d
           << transfer.logic;

    Socket::Status status = client.send(packet);
    if (status == Socket::Status::Done)
    {
        return true;
    }
    else
    {
        check_status(status);
    }
    return false;
}

int Client::GetIntMessage(bool &check) {
    Packet packet;
    int integer = 0;

    Socket::Status status = client.receive(packet);
    if (status == Socket::Status::Done)
    {
       if  (packet >> integer)
       {
           check = true;
           return integer;
       }
       else
       {
            check = false;
            cout << "Error to read" << endl;
            return 0;
       }
    }
    else
    {
        check = false;
        check_status(status);
        return 0;
    }
}

string Client::GetStringMessage(bool &check) {
    Packet packet;
    string data;

    Socket::Status status = client.receive(packet);
    if (status == Socket::Status::Done)
    {
        if  (packet >> data)
        {
            check = true;
            return data;
        }
        else
        {
            check = false;
            cout << "Error to read" << endl;
            return data;
        }
    }
    else
    {
        check = false;
        check_status(status);
        return data;
    }
}

double Client::GetDoubleMessage(bool &check) {
    Packet packet;
    double d;

    Socket::Status status = client.receive(packet);
    if (status == Socket::Status::Done)
    {
        if  (packet >> d)
        {
            check = true;
            return d;
        }
        else
        {
            check = false;
            cout << "Error to read" << endl;
            return 0;
        }
    }
    else
    {
        check = false;
        check_status(status);
        return 0;
    }
}

bool Client::GetBoolMessage(bool &check) {
    Packet packet;
    bool logic;

    Socket::Status status = client.receive(packet);
    if (status == Socket::Status::Done)
    {
        if  (packet >> logic)
        {
            check = true;
            return logic;
        }
        else
        {
            check = false;
            cout << "Error to read" << endl;
            return 0;
        }
    }
    else
    {
        check = false;
        check_status(status);
        return 0;
    }
}

Packet Client::GetPacketMessage(bool &check) {
    Packet packet;

    Socket::Status status = client.receive(packet);
    if (status == Socket::Status::Done)
    {
        if  (packet)
        {
            check = true;
            return packet;
        }
        else
        {
            check = false;
            cout << "Error to read" << endl;
            return packet;
        }
    }
    else
    {
        check = false;
        check_status(status);
        return packet;
    }
}

Transfer Client::GetTransferMessage(bool &check) {
    Packet packet;
    Transfer transfer;

    Socket::Status status = client.receive(packet);
    if (status == Socket::Status::Done)
    {
        if  (packet >> transfer.integer
                    >> transfer.data
                    >> transfer.f
                    >> transfer.d
                    >> transfer.logic)
        {
            check = true;
            return transfer;
        }
        else
        {
            check = false;
            cout << "Error to read" << endl;
            return transfer;
        }
    }
    else
    {
        check = false;
        check_status(status);
        return transfer;
    }
}


IpAddress Client::getIp() {
    return client.getRemoteAddress();
}

size_t Client::getPort() {
    return client.getRemotePort();
}

void Client::SetBlock(bool block) {
    client.setBlocking(block);
}

bool Client::IsBlocking() {
    return client.isBlocking();
}

TcpSocket &Client::getClient() {
    return client;
}

void Client::check_status(Socket::Status status)
{
    switch (status)
    {
        case Socket::Status::Disconnected:
        {
            Disconnect();
            cout << "The TCP socket has been disconnected." << endl;
            break;
        }
        case Socket::Status::Partial:
        {
            cout << "The socket sent a part of the data." << endl;
            break;
        }
        case Socket::Status::NotReady:
        {
            cout << "The socket is not ready to send / receive data yet." << endl;
            break;
        }
        default:
        {
            cout << "An unexpected error happened." << endl;
            break;
        }
    }
}






