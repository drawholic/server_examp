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

	printf("Closing server\n");
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

		if(fds[0].revents & POLLIN)
		{
			client = accept(fd, 0, 0);
			if(client == -1)
			{
				perror("Failure accepting");
				continue;
			};
			add_pollfd(client); 
		};
		loop_fds();
	};
};

void Server::add_pollfd(int client)
{
	 if (fds_num >= FDS_CAPACITY) {
        printf("Max capacity reached\n");
        return;
    }
    fcntl(client, F_SETFL, O_NONBLOCK);
    fds[fds_num].fd = client;
    fds[fds_num].events = POLLIN | POLLOUT;
    fds_num++;

    printf("New client connected\n");
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


void Server::stop()
{
	running = false;
};

void Server::loop_fds()
{
	for(unsigned i = 1; i < fds_num; i++)
	{
		if(!running)
			return;
		if(fds[i].revents & POLLHUP)
		{
			close_fd(i);
			i--;
		};
		if(fds[i].revents & POLLIN)
		{
			read_fd(i);
		};
		if(fds[i].revents & POLLOUT)
		{
			write_fd(i);
		};
	};
};

void Server::write_fd(unsigned client_index)
{
	unsigned bytes_sent = 0;
	const char* message = "Hello from server";
	bytes_sent = send(fds[client_index].fd, message, strlen(message), 0);
	if(bytes_sent == -1)
	{
		perror("Failure sending message");
		return;
	};

};

void Server::close_fd(unsigned fd_index)
{
	close(fds[fd_index].fd);
	fds[fd_index] = fds[fd_index - 1];
	fds_num--;


};

void Server::read_fd(unsigned client_index)
{
	unsigned total_read = 0;
	unsigned bytes_read;
	printf("Receiving: ");
	while((bytes_read = recv(fds[client_index].fd, buffer, BUFFER_SIZE-1, 0)) > 0)
	{
		total_read += bytes_read;
		if(!running)
			return;
		buffer[bytes_read+1] = 0;
		printf("%s", buffer);
	};
	printf("\nEnd of receive, received %u bytes\n", total_read);
}