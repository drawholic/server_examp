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
	fds_num = 0;
	fds = new pollfd[FDS_CAPACITY];
	fds = {0};
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
	while(running)
	{

	};
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