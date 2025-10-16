#include "Core/Application.hpp"

int main()
{
	Application app;

	WindowConfig winConfig(1920, 1080, 3, 3);
	if (!app.Initialize(winConfig)) return -1;
	app.Run();

	return 0;
}