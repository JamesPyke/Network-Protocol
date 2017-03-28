#pragma once
#include <string>
#include <WinSock2.h>

class User
{

public:

	User();
	User(int id, SOCKET socket);

	int getID() const;
	SOCKET getSocket() const;
	void setSocket(SOCKET socket);

private:

	std::string username;
	
	int id;
	SOCKET socket;

};