#include "Application.h"
#include <memory>

extern Application* createApplication();

int main()
{
	std::unique_ptr<Application> app( createApplication() );
	app->run();
}