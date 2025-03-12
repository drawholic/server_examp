#ifndef SERVER_HPP
#define SERVER_HPP

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <cstring>

const unsigned BUFFER_SIZE = 1024;
const unsigned DEFAULT_PORT = 8000;
const unsigned FDS_CAPACITY = 10;

class Server
{

	pollfd* fds;
	nfds_t fds_num;

	int status;
	bool running;
	int fd, client;
	
	sockaddr_in addr;

	socklen_t addr_len;

	char* buffer;

	void set_options();
	void create_socket();
	void fill_address(const char*, int);
	void socket_listen();
	void bind_addr();
	void server_accept();

	void get_message();
	void send_message();

	void init_fds();
	void add_pollfd(int);

	void loop_fds();
	void read_fd(unsigned);
	void write_fd(unsigned);

	void close_fd(unsigned);

public:
	Server(const char* ip = 0, int port = 0);
	~Server();

	void run();
	void stop();

};

#endif
