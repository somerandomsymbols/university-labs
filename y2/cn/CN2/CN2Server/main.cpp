#include <WS2tcpip.h>
#include <WinSock2.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> serverFile, clientFile;

//SERVER

int getNextChange()
{
    ifstream fi;
    fi.open("serverFile.txt");
    serverFile.clear();

    while (!fi.eof())
    {
        string s;
        getline(fi, s);
        serverFile.push_back(s);
    }

    fi.close();

    for (int i = 0; i < serverFile.size(); ++i)
        if (clientFile[i] != serverFile[i])
        {
            clientFile[i] = serverFile[i];
            return i;
        }

    return -1;
}

int commandProcess(const string& recvbuf, string& sendbuf)
{
    string command = "";
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

    if (i == recvbuf.length())
    {
        command = recvbuf;
    }
    else
    {
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
        {
            args.push_back(recvbuf.substr(offset, recvbuf.length() - offset));
        }
    }

    if (command == "")
        return -2;

    if (sendbuf.length() > 1)
        sendbuf += ";";

    if (command == "Who")
    {
        sendbuf += "Message?Program by Shvets Misha, K-25. Variant 14: Comparison/correction of files";
    }
    else if (command == "ShutDown")
    {
        sendbuf += "ShutDown";
        return -1;
    }
    else if (command == "NextChange")
    {
        int nextChange = getNextChange();

        if (nextChange >= 0)
            sendbuf += "Change?" + to_string(nextChange) + "&" + serverFile[nextChange];
        else
            sendbuf += "Message?NoChanges";
    }

    return 0;
}

int bufferProcess(const string& recvbuf, string& sendbuf)
{
    if (recvbuf.length() == 0)
        return -1;

    int offset = 1;
    sendbuf = ">";
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
    // Initialize Winsock.
    ifstream fi;
    ofstream fo;
    fi.open("serverFile.txt");
    fo.open("D:/c/kubick/labs/CN2/CN2Client/clientFile.txt");
    cout << "File:\n";

    while (!fi.eof())
    {
        string s;
        getline(fi, s);
        fo << s << endl;
        cout << s << endl;
        serverFile.push_back(s);
        clientFile.push_back(s);\
    }

    fo.close();
    fi.close();
    cout << "File End.\n";

    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (iResult != NO_ERROR)
        printf("Error at WSAStartup()\n");

    //----------------------
    // Create a SOCKET for listening for
    // incoming connection requests.
    SOCKET ListenSocket;
    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (ListenSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    sockaddr_in service = { 0 };
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = htonl(INADDR_ANY);
    service.sin_port = htons(1039);
    /*
    //----------------------
    // The sockaddr_in structure specifies the address family,
    // IP address, and port for the socket that is being bound.
    sockaddr_in service;
    service.sin_family = AF_INET;
    //InetPton(AF_INET, (PCWSTR)("127.0.0.1"), &service.sin_addr.s_addr);
    service.sin_addr.s_addr = inet_addr("127.0.0.1");
    service.sin_port = htons(1039);*/

    if (bind(ListenSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR)
    {
        printf("bind() failed.\n");
        closesocket(ListenSocket);
        return -1;
    }

    //----------------------
    // Listen for incoming connection requests.
    // on the created socket
    if (listen(ListenSocket, 1) == SOCKET_ERROR)
        printf("Error listening on socket.\n");

    //----------------------
    // Create a SOCKET for accepting incoming requests.
    SOCKET AcceptSocket;
    printf("Waiting for client to connect...\n");

    //----------------------
    // Accept the connection.
    AcceptSocket = SOCKET_ERROR;
    while (AcceptSocket == SOCKET_ERROR)
    {
        AcceptSocket = accept(ListenSocket, NULL, NULL);
    }

    printf("Client connected.\n");
    ListenSocket = AcceptSocket;

    int responseCode = 0;
    string strbuf = ">Message?OK";
    char buf[256];
    strcpy_s(buf, strbuf.c_str());
    send(AcceptSocket, strbuf.c_str(), strbuf.length()+1, 0);
    cout << "Sent:" << strbuf << endl;

    while (responseCode != -1)
    {
        int bytes = SOCKET_ERROR;

        while (bytes == SOCKET_ERROR)
            bytes = recv(AcceptSocket, buf, 256, 0);

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

        bytes = SOCKET_ERROR;
        strcpy_s(buf, strbuf.c_str());

        while (bytes == SOCKET_ERROR)
            bytes = send(AcceptSocket, buf, strbuf.length()+1, 0);

        cout << "Sent:" << buf << endl;
    }

    WSACleanup();
    return 0;
}
