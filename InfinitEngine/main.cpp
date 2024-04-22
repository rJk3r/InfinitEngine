#include <iostream>
#include "App.h"

int main()
{
	App app;
	if (app.init())
	{
		while (app.isRun())
		{
			app.broadcast();
		}
	}
	return 0;
}