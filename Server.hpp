#pragma once

#define BUFSIZ 4096

#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <fcntl.h>
#include <map>
#include "Client.hpp"
#include "Channel.hpp"
#include <vector>
#define ERROR_S "SERVER ERROR: "
#define BUFFER_SIZE 1024
#define CLIENT_CLOSE_CONNECTION_SYMBOL '#'
#define SERVER_CLOSE_CONNECTION_SYMBOL '#'
#define SERVER_IP "127.0.0.1"

class Client;
class Channel;

static int numberClient;

class Server
{
private:
	short portServer;
	std::string passwordServer;
	socklen_t client_length;
	int allClients;
	int numberChannelPasswordChannel;
	bool flagfile;

public:
	std::map<int, Client *> mapa;
	std::map<std::string, Channel *> chan;
	std::map<std::string, Channel *>::iterator chann;
	std::map<int, Client *>::iterator cl;
	/*  переменные который были в main*/
	int i;
	int idClient;
	char client[100];
	socklen_t size;
	Server *serv;
	struct sockaddr_in server_adress;
	char buffer[BUFFER_SIZE]; // отсюда берет текст для клиента
	char str[BUFFER_SIZE + 1];	// сюда записываются от клиента информация
	char *recv_str;
	fd_set fd_read, fd_write;
	int new_socket[100];
	int max_fd;
	int socket1, socket2;

	Server();
	~Server();
	int startServer(int ac, char **av);
	bool is_client_connection_close(const char *msg);
	void init(std::string port, std::string password);
	void initial(char **av);
	std::pair<int, std::string> connect();
	void checkTerminal();
	bool bilding();
	bool checkPassword(std::string pass);
	void checkCommand(char *str, int _socket, int idClient);
	void motdText(std::string nick, int _socket);
	bool checkNickClients(int q, int _socket);

	void splitCommand(char *str);
	std::string commandClient[BUFFER_SIZE];
	void writeCommandClient();
	void deleteCommand();

	// command
	void quit(int _socket);
	void join(int _socket);
	void privmsgChannel(int i, int _socket);
	void error(int error, int _socket, int iterator);
	void privmsgClient(int _socket);
	void kick(int _socket);
	void ison(int _socket);
	int pass(int _socket, int iterator);
	int user(int _socket, int iterator);
	int nick(int _socket, int iterator);
	void allowedCharacterJoin(int _socket);
	void allowedCharacterPrivmsg(int _socket);
	void ping(int _socket);
	void pingServer(int _socket);
	void pong(int _socket);
};
