#include "Core/Application.hpp"

#include <memory>

int main()
{
	std::unique_ptr<Application> app = std::make_unique<Application>();
	app->Start("Assets/Configs/config.json");

	return 0;
}