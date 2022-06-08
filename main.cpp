#include "Server.hpp"

Server servs;


int main(int ac, char **av)
{

	if (ac != 3)
	{
		std::cout << av[0] << " <port> <password>" << std::endl;
		return (1);
	}
	if (servs.startServer(ac, av) == -1)
		return (-1);
	return (0);
}

