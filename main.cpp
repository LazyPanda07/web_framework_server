#include <iostream>

#include <WebFramework.hpp>

int main(int argc, char** argv)
{
	framework::utility::initializeWebFramework("");

	framework::utility::Config config(argv[1]);

	config.overrideBasePath("executors");

	framework::WebFramework server(config);

	server.start(true, []() { std::cout << "Server is running" << std::endl; });

	return 0;
}
