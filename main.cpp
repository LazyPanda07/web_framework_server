#include <iostream>

#include <WebFramework.hpp>

int main(int argc, char** argv)
{
	framework::utility::initializeWebFramework(); // Load WebFramework shared library

	framework::WebFramework server(argv[1]);

	server.start(true, []() { std::cout << "Server is running" << std::endl; });

	return 0;
}
