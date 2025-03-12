#include "Client.hpp"


Client::Client(const char* ip, int port)
{
	create_socket();

	fill_address(ip, port);

	buffer = new char[BUFFER_SIZE];
	addr_len = sizeof(addr);

	connect_to_server();
};

Client::~Client()
{
	delete[] buffer;
	close(fd);
};

void Client::create_socket()
{
	fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(fd == -1)
	{
		perror("Failure creating socket");
		exit(EXIT_FAILURE);
	};
};

void Client::fill_address(const char* ip, int port)
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

void Client::connect_to_server()
{
	status = connect(fd, (sockaddr*)&addr, addr_len);
	
	if(status == -1)
	{
		perror("Failure connecting to server");
		close(fd);
	}else{
		printf("Success connecting to server\n");
	};

};

void Client::get_message()
{
	const char* msg = "Hello world from client!";
	message = msg;
};

void Client::run()
{
	get_message();
	send_message();
	receive_message();
};


void Client::receive_message()
{
	unsigned total_read = 0;
	unsigned bytes_read;
	
	printf("Receiving: ");

	while((bytes_read = recv(fd, buffer, BUFFER_SIZE-1, 0)) > 0)
	{
		total_read += bytes_read; 
	
		buffer[bytes_read + 1] = 0;
	
		printf("%s", buffer);
	};
	
	printf("\nEnd of receive, received %u bytes\n", total_read);
};

void Client::send_message()
{
	unsigned total_sent = 0;
	unsigned bytes_sent = 0;

	bytes_sent = send(fd, message, strlen(message), 0);
	if(bytes_sent == -1)
	{
		perror("Failure sending message");
		return;
	}
	
	total_sent += bytes_sent;
	printf("sent: %u bytes\n", bytes_sent);
	
	printf("Total sent bytes %u\n", bytes_sent);
};