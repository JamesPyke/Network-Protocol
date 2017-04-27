#include <iostream>
#include <WinSock2.h>
#include <thread>
#include <vector>
#include <string>
#include "User.h"

//inlcude the ws2_32 library using pragma comment
#pragma comment(lib, "Ws2_32.lib")

//Declare max clients
const unsigned int MAX_CLIENTS = 5;

//Then bind to the port that the server will be listening on.
const unsigned short PORT = 1234;

// Message Buffer Length
const int BUFFER_SIZE = 512;

const unsigned int USERNAME_MIN_LENGTH = 3;
const unsigned int USERNAME_MAX_LENGTH = 12;

enum Command { INVALID, UNAME, PM };

struct CommandData
{
	CommandData(const Command& command, std::vector<std::string> parameters)
	{
		this->command = command;
		this->parameters = parameters;
	}

	Command command;
	std::vector<std::string> parameters;
};

//Checks to make use the message is valid by removing extra characters
bool isMessageValid(const char* message)
{
	if(!strcmp("", message))
		return false;
	if (message[0] == '\r')
		return false;
	if (message[0] == '\n')
		return false;
	return true;
}

std::string toLower(std::string string)
{
	for(char& character : string)
	{
		character = towlower(character);
	}
	return string;
}

void disconnectUser(User &user, std::vector<User> &users)
{
	// Close the user's socket and flag it as invalid
	closesocket(user.getSocket());
	user.setSocket(INVALID_SOCKET);

	// Build the message to send to other users and log it to the console
	std::string message = "User #" + std::to_string(user.getID()) + " Disconnected.";
	printf("%s\n", message.c_str());

	// For each valid user that is connected, notify them of the user disconnecting
	for (unsigned int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (users[i].getSocket() != INVALID_SOCKET)
		{
			send(users[i].getSocket(), message.c_str(), message.length(), NULL);
		}
	}
}

CommandData getCommand(const std::string& message)
{
	std::vector<std::string> segments;
	std::string current = "";
	for(int i = 0; i < message.length(); ++i)
	{
		if (message[i] == ' ' && !current.empty())
		{
			segments.push_back(current);
			current = "";
			continue;
		}

		current += message[i];

		if(i == message.length() - 1 && !current.empty())
		{
			segments.push_back(current);
		}

	}

	if (segments.empty())
		return CommandData(INVALID, segments);

	std::string command = toLower(segments[0]);
	segments.erase(segments.begin());

	if (command == "pm" && segments.size() >= 2)
		return CommandData(PM, segments);
	if (command == "uname" && segments.size() >= 1)
		return CommandData(UNAME, segments);

	return CommandData(INVALID, segments);
}

void processCommand(User &user, std::vector<User> &users, const CommandData& commandData)
{
	Command commandType = commandData.command;

	if(commandType == UNAME)
	{
		std::string desiredUsername = commandData.parameters[0];
		unsigned int desiredUsernameLength = desiredUsername.length();
		
		if(desiredUsernameLength < USERNAME_MIN_LENGTH || desiredUsernameLength > USERNAME_MAX_LENGTH)
		{
			std::string response = "Username too long or short ";
			send(user.getSocket(), response.c_str(), response.length(), NULL);
			return;
		}

		std::string desiredUsernameLowered = toLower(desiredUsername);

		for(unsigned int i = 0; i < users.size(); ++i)
		{
			std::string usersNameLowered = toLower(users[i].getUsername());
			if(usersNameLowered == desiredUsernameLowered)
			{
				std::string response = "Username already exists ";
				send(user.getSocket(), response.c_str(), response.length(), NULL);
				return;
			}
		}
		user.setUsername(desiredUsername);
		printf("Set User %d's name to %s\n", user.getID(), desiredUsername.c_str());
		std::string response = "Username set successfully ";
		send(user.getSocket(), response.c_str(), response.length(), NULL);
		return;
	}

	if(commandType == PM)
	{
		std::vector<std::string> parameters = commandData.parameters;

		std::string targetUser = toLower(parameters.front());
		parameters.erase(parameters.begin());

		std::string message = "(PM) " + user.getUsername() + ": ";
		for(std::string& item : parameters)
		{
			message += item + " ";
		}

		for(unsigned int i = 0; i < users.size(); ++i)
		{	
			std::string usersNameLowered = toLower(users[i].getUsername());
			if(targetUser == usersNameLowered)
			{
				std::string response = "PM sent succesfully.";
				send(user.getSocket(), response.c_str(), response.length(), NULL);

				send(users[i].getSocket(), message.c_str(), message.length(), NULL);
			}
		}
		return;
	}
}

int processClient(User &user, std::vector<User> &users, std::thread &thread)
{
	while(true)
	{
		// Create a buffer to store the recieved data
		char messageBuffer[BUFFER_SIZE] = { 0 };

		// Wait for a message to be recieved
		int status = recv(user.getSocket(), messageBuffer, BUFFER_SIZE, NULL);

		// If there was an error, disconnect the user and detach the thread
		if(status == SOCKET_ERROR)
		{
			disconnectUser(user, users);
			thread.detach();
			return -1;
		}

		// If the message is invalid, ignore it and continue
		if(!isMessageValid(messageBuffer))
			continue;

		CommandData commandData = getCommand(std::string(messageBuffer));
		if (commandData.command != INVALID)
		{
			processCommand(user, users, commandData);
			continue;
		}

		// Build the message to send to other users and log it to the console
		std::string message = user.getUsername() + ": " + std::string(messageBuffer);
		printf("%s\n", message.c_str());

		int sendersID = user.getID();
		for (unsigned int i = 0; i < MAX_CLIENTS; ++i)
		{
			// Send the message to all valid users (that are not the sending user)
			if (users[i].getSocket() != INVALID_SOCKET)
			{
				send(users[i].getSocket(), message.c_str(), message.length(), NULL);
			}
		}
	}
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

	while (true)
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