#pragma once
#include "Server.hpp"
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#define BUFFER_SIZE 1024

class Client
{
private:
	int id;
	int socket_fd;
	std::string nickname;
	int passCheck;
	int nickCheck;
	int userCheck;
	int Registed;
	int offlineOnline;
	std::string myChannels[BUFFER_SIZE];
	int numberMyChannel;
	int checkPing;
	int flagCheckPingPong;

	std::string Realname;
	std::string UserName;
	std::string HostName;
	std::string zvezda;
	std::string ip;

public:
	Client(int _socket_fd);
	Client();
	~Client();
	void setNickName(std::string nick);
	void setuserCheckPlus();
	void setnickCheckPlus();
	void setpassCheckPlus();
	void setzvezda(std::string str);
	void setRealname(std::string str);
	void setRealNamePlus(std::string str);
	void setUserName(std::string str);
	void setHostName(std::string str);
	void setMyChannel(std::string nameChannel);
	int getuserCheck();
	int getnickCheck();
	int getpassCheck();
	void setRegisted();
	int getRegisted();
	std::string getNickName();
	void setOfflineOnlinePlus();
	void setOfflineOnlineMinus();
	int getId();
	int getOffineOnline();
	void setIP(std::string _ip);
	std::string getIP();
	std::string getUserName();
	void setuserCheckMinus();
	void setnickCheckMinus();
	void setpassCheckMinus();
	void setCheckPing();
	int getCheckPing();
	void nullCheckPing();
	void plusFlagCheckPingPong();
	void minusFlagCheckPingPong();
	int getflagCheckPingPong();
	int getSocket();
};
