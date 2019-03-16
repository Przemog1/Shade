#include "Application.h"

extern Application* createApplication();

int main()
{
	std::unique_ptr<Application> app( createApplication() );
	app->run();
}