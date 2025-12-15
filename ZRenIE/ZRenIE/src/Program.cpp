#include "Core/Application.hpp"

#include <memory>

int main()
{
	std::unique_ptr<Application> app = std::make_unique<Application>();

	WindowConfig winConfig(1920, 1080, 3, 3);
	if (!app->Initialize(winConfig)) return -1;
	app->Run();

	return 0;
}