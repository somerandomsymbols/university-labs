#include <WS2tcpip.h>
#include <WinSock2.h>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdio.h>

using namespace std;

vector<string> clientFile;

//CLIENT

void changeFile(int row, string s)
{
    ifstream fi;
    fi.open("clientFile.txt");
    clientFile.clear();

    while (!fi.eof())
    {
        string s;
        getline(fi, s);
        clientFile.push_back(s);
    }

    fi.close();

    clientFile[row] = s;

    ofstream fo;
    fo.open("clientFile.txt");

    for (int i = 0; i < clientFile.size(); ++i)
        fo << clientFile[i] << endl;

    fo.close();
}

int commandProcess(const string& recvbuf, string& sendbuf)
{
    string command = recvbuf;
    vector<string> args;
    int i = 0, offset = 0;

    while (i < recvbuf.length())
    {
        if (recvbuf[i] == '?')
        {
            command = recvbuf.substr(0, i);
            offset = i + 1;
            ++i;
            break;
        }

        ++i;
    }

    while (i < recvbuf.length())
    {
        if (recvbuf[i] == '&')
        {
            args.push_back(recvbuf.substr(offset, i - offset));
            offset = i + 1;
        }

        ++i;
    }

    if (offset < recvbuf.length())
        args.push_back(recvbuf.substr(offset, recvbuf.length() - offset));

    if (command == "")
        return -2;

    if (sendbuf.length() > 1)
        sendbuf += ";";

    if (command == "Message")
    {
        for (int j = 0; j < args.size(); ++j)
        {
            if (j > 0)
                sendbuf += "\n";

            sendbuf += args[j];
        }
    }
    if (command == "ShutDown")
    {
        sendbuf += "ShutDown";
        return -1;
    }
    else if (command == "Change")
    {
        if (args.size() != 2)
        {
            sendbuf += "Error";
            return -2;
        }
        else
        {
            changeFile(stoi(args[0]), args[1]);
            sendbuf += "Changed row #" + args[0] + " to " + args[1];
        }
    }

    return 0;
}

int bufferProcess(const string& recvbuf, string& sendbuf)
{
    if (recvbuf.length() == 0)
        return -2;

    int offset = 1;
    sendbuf = "";
    int i = 1;

    while (i < recvbuf.length())
    {
        if (recvbuf[i] == ';')
        {
            int res = commandProcess(recvbuf.substr(offset, i - offset), sendbuf);
            
            if (res != 0)
                return res;

            offset = i + 1;
        }

        ++i;
    }

    return commandProcess(recvbuf.substr(offset, recvbuf.length() - offset), sendbuf);
}

int main()
{
    //----------------------
    // Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (iResult != NO_ERROR)
        printf("Error at WSAStartup()\n");

    //----------------------
    // Create a SOCKET for connecting to server
    SOCKET ConnectSocket;
    ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    //----------------------
    // The sockaddr_in structure specifies the address family,
    // IP address, and port of the server to be connected to.

    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &(clientService.sin_addr));
    clientService.sin_port = htons(1039);

    //----------------------
    // Connect to server.
    if (connect(ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
    {
        printf("Failed to connect.\n");
        WSACleanup();
        return -1;
    }

    //----------------------
    // Declare and initialize variables.
    int responseCode = 0;
    string strbuf = "";
    char buf[256];


    while (responseCode != -1)
    {
        int bytes = SOCKET_ERROR;

        while (bytes == SOCKET_ERROR)
            bytes = recv(ConnectSocket, buf, 256, 0);

        strbuf = "";

        try
        {
            cout << "Recieved:" << buf << endl;
            responseCode = bufferProcess(buf, strbuf);
        }
        catch (...)
        {
            responseCode = -2;
        }

        cout << strbuf << endl;
        if (responseCode == -1)
            return 0;

        getline(cin, strbuf);
        bytes = SOCKET_ERROR;
        strcpy_s(buf, strbuf.c_str());

        while (bytes == SOCKET_ERROR)
            bytes = send(ConnectSocket, buf, strbuf.length()+1, 0);

        cout << "Sent:" << buf << endl;
    }

    WSACleanup();
    return 0;
}
