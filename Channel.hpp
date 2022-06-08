#pragma once
#include "Server.hpp"

class Server;

#define BUFFER_SIZE 1024
static int numberClients;
class Channel
{
private:
	std::string Channels;
	std::string Password;
	int clients[BUFFER_SIZE];
	std::string Topic;
	std::string nameClients[BUFFER_SIZE];
	int numClient;
	int adminChannel;
	std::string message[BUFFER_SIZE];

public:
	Channel();
	void setChannel(std::string nameChannel);
	void setPassword(std::string passwordChannel);
	void setClients(int _socketClient);
	void setAdminChannel(int _socketAdmin);
	~Channel();
	std::string getChannel();
	bool checkChannel(std::string nickChannel);
	int getNumClient();
	int socketClientForChannel(int i);
	int getAdminChannel();
	void setKickClient(int i);
	std::string getPassword();
};