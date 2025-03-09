#include "Client.hpp"


Client::Client(const char* ip, int port)
{
	create_socket();

	fill_address(ip, port);

	buffer = new char[BUFFER_SIZE];
	addr_len = sizeof(addr);
};

Client::~Client()
{
	delete buffer;
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
		addr.sin_addr.s_addr = INADDRY_ANY;

	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

};

void Client::connect_to_server()
{
	status = connect(fd, (sockaddr*)&addr, addr_len);
	
	if(status == -1)
	{
		perror("Failure connecting to server");
		close(fd);
		exit(EXIT_FAILURE);
	}else{
		printf("Success connecting to server\n");
	};

};