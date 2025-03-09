#ifndef SERVER_HPP
#define SERVER_HPP



class Server
{
	int status;
	int fd;
	
	sockaddr_in addr;
	socklen_t addr_len;

	char* buffer;

	void create_socket();
	void fill_address();
	void socket_listen();
	void bind_addr();
	void server_accept();
	void get_message();
	void send_message();

public:
	Server(const char* ip = 0, int port);
	~Server();

};

#endif
