#include <cstdio>
#include "Server.hpp"
#include <csignal>


Server* s;

void handle_interrupt(int);

int main(int argc, char const *argv[])
{
	const char* ip = "0.0.0.0";
	int port = 8000;

	s = new Server(ip, port);

	s->run();
	printf("Hello world!\n");
	return 0;
}


void handle_interrupt(int sig)
{
	printf("Interrupting...\n");
	s->stop();
};

