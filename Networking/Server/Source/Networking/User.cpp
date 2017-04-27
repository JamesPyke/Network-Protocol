#include "User.h"

User::User()
{
	id = -1;
	socket = INVALID_SOCKET;
}

User::User(int id, SOCKET socket)
{
	this->id = id;
	this->socket = socket;
	this->username = "User " + std::to_string(id);

}

int User::getID() const
{
	return id;
}

SOCKET User::getSocket() const
{
	return socket;
}

void User::setSocket(SOCKET socket) 
{
	this->socket = socket;
}

std::string User::getUsername() const
{
	return username;
}

void User::setUsername(const std::string& username)
{
	this->username = username;
}
