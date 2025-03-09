#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

// const char* message = "Hello server!";
const unsigned BUFFER_SIZE = 1024;

class Client
{
	int status;
	int fd;
	sockaddr_in addr;
	socklen_t addr_len;
	char* buffer;
	const char* message;

	void create_socket();
	void fill_address(const char*, int);
	void connect_to_server();
	void send_message();
	void get_message();
public:
	Client(const char* ip = 0, int port = 0);
	~Client();

	void run();
};


#endif