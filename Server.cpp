#include "Server.hpp"

Server::Server(){};

Server::~Server(){};

bool Server::checkPassword(std::string pass)
{
	if (pass == passwordServer)
		return (true);
	return (false);
}

void Server::initial(char **av)
{
	int portmin;
	portmin = atoi(av[1]);
	this->passwordServer = static_cast<std::string>(av[2]);
	this->portServer = portmin;
	numberClient = 0;
	FD_ZERO(&fd_read);
	FD_ZERO(&fd_write);
	idClient = 0;
	str[0] = 0;
	i = -1;
	allClients = -1;
	strcpy(buffer, "Hello peer");
	flagfile = false;
	numberChannelPasswordChannel = 0;
}

bool Server::bilding()
{
	int i = 1;
	socket1 = socket(AF_INET, SOCK_STREAM, 0);
	if (socket1 < 0)
	{
		std::cout << ERROR_S << "establishing socket error.\n";
		return false;
	}
	if (setsockopt(socket1, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int)) == -1)
		std::cout << ERROR_S << std::endl;
	bzero((char *)&server_adress, sizeof(server_adress));
	server_adress.sin_family = AF_INET;
	server_adress.sin_addr.s_addr = htons(INADDR_ANY);
	server_adress.sin_port = htons(portServer);
	if (bind(socket1, (struct sockaddr *)(&server_adress), sizeof(server_adress)) < 0)
	{
		std::cout << ERROR_S << "binding connection. Socket has already been establishing.\n";
		return false;
	}
	std::cout << "SERVER: Socket for server was succesfully created\n";
	fcntl(socket1, F_SETFL, O_NONBLOCK);
	max_fd = socket1;
	return true;
}

int Server::startServer(int ac, char **av)
{
	initial(av);
	if (!bilding())
		return (-1);
	size = sizeof(server_adress);
	std::cout << "Port: " << portServer << std::endl;
	std::cout << "SERVER: listening clients...\n";
	listen(socket1, 5);
	while (true)
	{
		if (allClients == 99)
		{
			std::cout << "Error: maximum number of clients connected" << std::endl;
			while (allClients == 99)
				checkTerminal();
		}
		if (new_socket[allClients] != -1)
			allClients++;
		FD_ZERO(&fd_read);
		FD_SET(socket1, &fd_read);
		FD_SET(socket2, &fd_write);
		if (max_fd < socket1)
			max_fd = socket1;
		if (select(max_fd + 1, &fd_read, &fd_write, NULL, NULL) > 0)
		{
			std::pair<int, std::string> pair = connect();
			new_socket[allClients] = pair.first;
			if (new_socket[allClients] != -1)
			{
				fcntl(new_socket[allClients], F_SETFL, O_NONBLOCK);
				cl = mapa.find(new_socket[i]);
				if (cl == mapa.end())
					mapa.insert(std::make_pair(new_socket[allClients], new Client(new_socket[allClients])));
				mapa[new_socket[allClients]]->setIP(pair.second);
			}
		}
		if (!mapa.empty())
			checkTerminal();
	}
	return (1);
}

std::pair<int, std::string> Server::connect()
{
	struct sockaddr_in ClientAddr;
	std::string qwe = "lsdkjflsdkfjsdf";
	client_length = sizeof(ClientAddr);
	new_socket[i] = accept(socket1, (struct sockaddr *)&ClientAddr, &client_length);
	if (new_socket[i] < 0)
		return std::make_pair(-1, qwe);
	std::cout << "New Client Connected, ip: " << inet_ntoa(ClientAddr.sin_addr)
			  << ", port: " << ntohs(ClientAddr.sin_port) << std::endl;
	return std::make_pair(new_socket[i], inet_ntoa(ClientAddr.sin_addr));
}

void Server::checkTerminal()
{
	int res;
	idClient = 0;
	while (new_socket[idClient] > 0)
	{
		res = recv(new_socket[idClient], str, BUFFER_SIZE, 0);
		//printf("%d\n", new_socket[idClient]);
		if (res == 0)
			break;
		if (res > 0)
		{
			if (str[res - 1] == '\n')
				checkCommand(str, new_socket[idClient], idClient);
		}
		if (res == -1)
		{
			mapa[new_socket[idClient]]->setCheckPing();
		}
		if (mapa[new_socket[idClient]]->getnickCheck() == 1 && mapa[new_socket[idClient]]->getpassCheck() == 1 && mapa[new_socket[idClient]]->getuserCheck() == 1 && mapa[new_socket[idClient]]->getOffineOnline() == 0)
		{
			if (mapa[new_socket[idClient]]->getOffineOnline() == 0 && mapa[new_socket[idClient]]->getRegisted() != 0)
				mapa[new_socket[idClient]]->setOfflineOnlinePlus();
			else
			{
				mapa[new_socket[idClient]]->setRegisted();
				mapa[new_socket[idClient]]->setOfflineOnlinePlus();
			}
			motdText(mapa[new_socket[idClient]]->getNickName(), new_socket[idClient]);
		}
		else if (mapa[new_socket[idClient]]->getpassCheck() == 0 && mapa[new_socket[idClient]]->getnickCheck() == 1 && mapa[new_socket[idClient]]->getuserCheck() == 1)
		{
			close(new_socket[idClient]);
			allClients--;
			std::cout << mapa[new_socket[idClient]]->getNickName() << " has disconnected" << std::endl;
			mapa.erase(new_socket[idClient]);
			new_socket[idClient] = -1;
			idClient++;
			continue;
		}
		if (mapa[new_socket[idClient]]->getCheckPing() == 10000000 && mapa[new_socket[idClient]]->getOffineOnline() == 1)
			pingServer(new_socket[idClient]);
		idClient++;
		res = 0;
		while (str[res])
			str[res++] = 0;
	}
}

void Server::motdText(std::string nick, int _socket)
{
	std::string Motd;

	Motd += ":IRC 375 " + nick + ":-" + SERVER_IP + " Message of the day - \n";
	Motd += ":IRC 372 " + nick + ":-" + buffer + "\n";
	Motd += ":IRC 376 " + nick + " :End of /MOTD command\n";
	send(new_socket[idClient], Motd.c_str(), Motd.size(), 0);
	Motd.clear();
	return;
}

bool Server::checkNickClients(int q, int _socket)
{
	int i = 0;
	while (new_socket[i] != -1)
	{
		if (new_socket[i] == 0)
			return (true);
		cl = mapa.find(_socket);
		if (cl == mapa.end())
			return (false);
		else
			return (true);
	}
	return (false);
}