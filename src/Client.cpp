#include "Client.hpp"


Client::Client(const char* ip, int port)
{
	create_socket();

	fill_address(ip, port);

	buffer = new char[BUFFER_SIZE];
	addr_len = sizeof(addr);
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

