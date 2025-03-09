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
	delete buffer[];
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
		addr.sin_port = htons(DEFAULT_PORT)
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
	const char* msg = "Hello world!";
	message = msg;
};