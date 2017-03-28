#include <iostream>
#include <WinSock2.h>
#include <thread>
#include <vector>
#include <string>
#include <algorithm>
#include "User.h"

//inlcude the ws2_32 library using pragma comment
#pragma comment(lib, "Ws2_32.lib")

//Declare max clients
const int MAX_CLIENTS = 5;

//Then bind to the port that the server will be listening on.
const unsigned short PORT = 1234;

//Checks to make use the message is valid by removing extra characters
bool isMessageValid(const char* message)
{
	if (message[0] == '\r')
	{
		return false;
	}
	if (message[0] == '\n')
	{
		return false;
	}
	return true;
}


int processClient(User &user, std::vector<User> &users, std::thread &thread)
{
	const int bufLen = 512;
	char tempmsg[bufLen];
	std::string msg = "";	

	msg = "UNAME";
	send(user.getSocket(), msg.c_str(), strlen(msg.c_str()), 0);

	while (true) 
	{
		memset(tempmsg, 0, bufLen);
		int result = recv(user.getSocket(), tempmsg, bufLen, 0);

		if (result != SOCKET_ERROR)
		{
			if (strcmp("", tempmsg) && isMessageValid(tempmsg))
			{
				msg = "Client #" + std::to_string(user.getID()) + " : " + tempmsg;
				for (int i = 0; i < MAX_CLIENTS; i++)
				{
					if (users[i].getSocket() != INVALID_SOCKET)
					{
						if (user.getID() != i)
						{
							result = send(users[i].getSocket(), msg.c_str(), strlen(msg.c_str()), 0);
						}
					}
				}
			}
		}
		else
		{
			msg = "Client #" + std::to_string(user.getID() + 1) + " disconnected";
			printf("%s\n", msg.c_str());

			for (int i = 0; i < MAX_CLIENTS; i++) 
			{
				if (users[i].getSocket() != INVALID_SOCKET) 
				{
					if (user.getID() != i)
					{
						result = send(users[i].getSocket(), msg.c_str(), strlen(msg.c_str()), 0);
					}
				}
			}
				
			closesocket(user.getSocket());
			closesocket(users[user.getID()].getSocket());
			users[user.getID()].setSocket(INVALID_SOCKET);
			thread.detach();
		}
	}
	return 0;
}

//Start to adding main function 
int main()
{
	//specify the version of winsock

	WORD wVersionRequested = MAKEWORD(2, 2);
	WSADATA wsaData;
	

	printf("Initialising Server...\n");
	int error = WSAStartup(wVersionRequested, &wsaData);

	//Check to make sur ethe socket initialised correctly and check for error
	if (error != 0)
	{
		printf("Failed to initialise winsock. Error code: %d\n", WSAGetLastError());
		return 0;
	}

	//Request the socket if no error
	//Specify using TCP
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//Check for errors again
	if (sock == INVALID_SOCKET) 
	{
		printf("Could not create socket: %d\n", WSAGetLastError());
		return 0;
	}

	//Use the port when creating the socket address structure.
	struct sockaddr_in sa, client;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = ADDR_ANY;
	sa.sin_port = htons(PORT);

	//then use the structure when we call bind
	error = bind(sock, reinterpret_cast<struct sockaddr*>(&sa), sizeof(sa));

	if (error == SOCKET_ERROR) 
	{
		printf("Bind failed with error code: %d", WSAGetLastError());
		return 0;
	}

	//Then set the socket to listen
	if (listen(sock, 256) == SOCKET_ERROR) 
	{
		printf("failed to set socket to listen with error code: %d", WSAGetLastError());
		return 0;
	}

	//Then using vectors to create a list of clients
	std::vector<User> clients(MAX_CLIENTS);
	std::thread threads[MAX_CLIENTS];
	int num_clients = 0;
	int temp_id = -1;

	for (auto i = 0; i < MAX_CLIENTS; i++) 
	{
		clients.push_back(User(-1, INVALID_SOCKET));
	}

	//Then we create an infinite loop the keep checking the listening socket for incoming connections.
	int size = sizeof(client);
	std::string msg;

	while (1)
	{
		auto clientSock = accept(sock, reinterpret_cast<sockaddr *>(&client), &size);
		if (clientSock == INVALID_SOCKET) continue;

		num_clients = -1;
		temp_id = -1;

		for (auto i = 0; i < MAX_CLIENTS; i++) 
		{
			if (clients[i].getSocket() == INVALID_SOCKET && temp_id == -1)
			{
				clients[i] = User(i, clientSock);
				temp_id = i;
			}
			if (clients[i].getSocket() != INVALID_SOCKET)
			{
				num_clients++;
			}
		}

		//At this point, the temp_id variable will let us know if we have space for the client, if we do, we spin
		//up a thread and hand off any further handling of this client to it.Otherwise, we close the clients
		//socket and ignore them.

		if (temp_id != -1) 
		{
			printf("Client # %d accepted\n", clients[temp_id].getID());
			msg = std::to_string(clients[temp_id].getID());
			send(clients[temp_id].getSocket(), msg.c_str(), strlen(msg.c_str()), 0);

			threads[temp_id] = std::thread(processClient,
				std::ref(clients[temp_id]),
				std::ref(clients),
				std::ref(threads[temp_id]));
		}
		else 
		{
			msg = "Server is full";
			send(clientSock, msg.c_str(), strlen(msg.c_str()), 0);
			printf("%s\n", msg.c_str());
		}

	}

	closesocket(sock);

	for (auto i = 0; i < MAX_CLIENTS; i++)
	{
		threads[i].detach();
		closesocket(clients[i].getSocket());
	}

	WSACleanup();

	return 0;



}