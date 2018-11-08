#include "Client.h"

int main()
{

    Client client;
    Socket::Status status = client.ConnectTo(IpAddress::LocalHost, 1261);
    if (status == Socket::Status::Done)
    {

        cout << "DONE!!!" << endl;

        string str = " ";
        int integer;
        double doble;
        bool bol;
        Packet pack;
        Transfer trans;
        bool ok = false;


        cout << str << endl;

        trans.d = 5.6745;
        trans.data = "ulala";
        trans.f = 5.34;
        trans.integer = 54;
        trans.logic = true;

        pack << 5 << "hilo" << true << 34.56;

        cout << client.Send(6) << endl;
        cout << client.Send(string("huhu")) << endl;
        cout << client.Send(5.2351) << endl;
        cout << client.Send(true) << endl;
        cout << client.Send(pack) << endl;
        cout << client.Send(trans) << endl << endl;

        cout << client.GetIntMessage(ok) << endl;
        cout << client.GetStringMessage(ok) << endl;
        cout << client.GetDoubleMessage(ok) << endl;
        cout << client.GetBoolMessage(ok) << endl;
        pack.clear();
        pack = client.GetPacketMessage(ok);
        pack >> integer >> str >> bol >> doble;
        cout << integer << " " << str << " " << bol << " " << doble << endl;
        trans = client.GetTransferMessage(ok);
        cout << trans.integer << " " << trans.logic << " " << trans.f << " " << trans.data << " " << trans.d << endl;
    }
    else
    {
        switch (status)
        {
            case Socket::Status::Disconnected:
            {
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
    while (true)
    {}
    //bool chk = false;
   // int mes = client.GetIntMessage(chk);

    return 0;
}