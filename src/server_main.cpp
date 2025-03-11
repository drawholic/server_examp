#include <cstdio>
#include "Server.hpp"
#include <csignal>


Server* s;

void handle_interrupt(int);
void handle_terminate(int);
int main(int argc, char const *argv[])
{
	signal(SIGINT, handle_interrupt);
	signal(SIGTERM, handle_interrupt);

	const char* ip = "0.0.0.0";
	int port = 8000;

	s = new Server(ip, port);

	s->run();
	printf("Hello world!\n");
	delete s;
	return 0;
}


void handle_interrupt(int sig)
{
	printf("Interrupting...\n");
	s->stop();
};

void handle_terminate(int sig)
{
	printf("Terminating...\n");
	s->stop();
};