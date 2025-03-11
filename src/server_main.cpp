#include <cstdio>
#include "Server.hpp"

int main(int argc, char const *argv[])
{
	const char* ip = "0.0.0.0";
	int port = 8000;
	Server s(ip, port);

	printf("Hello world!\n");
	return 0;
}