#include "Server.hpp"

Server::Server(const char* ip, int port)
{
	create_socket();
	
	set_options();

	fill_address(ip, port);

	addr_len = sizeof(addr);

	bind_addr();

	socket_listen();

	buffer = new char[BUFFER_SIZE];

	init_fds();

	
};
void Server::init_fds()
{
	fds_num = 1;
	fds = new pollfd[FDS_CAPACITY]();

	pollfd serv;
	serv.fd = fd;
	serv.events = POLLIN;

	fds[0] = serv;
};

void Server::set_options()
{
	int option = 1;
	status = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

	if(status == -1)
	{
		perror("Failure setting reuseaddr option");
		close(fd);
		exit(EXIT_FAILURE);
	};

	status = fcntl(fd, F_SETFL, O_NONBLOCK);

	if(status == -1)
	{
		perror("Failure setting nonblock");
		close(fd);
		exit(EXIT_FAILURE);
	};
};

Server::~Server()
{
	delete[] buffer;
	for(unsigned i = 0; i < fds_num; i++)
	{
		close(fds[i].fd);
	};
	delete[] fds;
	close(fd);
};

void Server::create_socket()
{
	fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(fd == -1)
	{
		perror("Failure creating socket");
		exit(EXIT_FAILURE);
	};
};

void Server::fill_address(const char* ip, int port)
{
	if(ip)
		inet_aton(ip, &addr.sin_addr);
	else
		addr.sin_addr.s_addr = INADDR_ANY;
	if(port)
		addr.sin_port = htons(port);
	else
		addr.sin_port = htons(DEFAULT_PORT);

	addr.sin_family = AF_INET;

};

void Server::bind_addr()
{
	status = bind(fd, (sockaddr*)&addr, addr_len);

	if(status == -1)
	{
		perror("Failure binding");
		close(fd);
		exit(EXIT_FAILURE);
	};
};

void Server::run()
{
	running = true;
	printf("Accepting connections...\n");

	while(running)
	{
		status = poll(fds, fds_num, 1000);

		if(status == -1)
		{
			perror("Error on polling");
			continue;
		};

		if(fds[1].revents & POLLIN)
		{
			client = accept(fd, 0, 0);
			if(client == -1)
			{
				perror("Failure accepting");
				continue;
			};
			pollfd client_pollfd;
			client_pollfd.fd = client;
			client_pollfd.events = POLLIN;

		};
	};
};

void Server::add_pollfd(pollfd* client)
{
	 if (fds_num >= FDS_CAPACITY) {
        close(client);
        return;
    }

    fds[fds_num].fd = client;
    fds[fds_num].events = POLLIN;
    fds_num++;
};

void Server::socket_listen()
{
	status = listen(fd, 10);

	if(status == -1)
	{
		perror("Failure setting listen");
		close(fd);
		exit(EXIT_FAILURE);
	};
};