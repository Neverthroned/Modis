#include <iostream>
#include <fstream>
#include <sstream>

#include "application.h"

int main()
{
    // Construct
    Application app;

    // Application init
    bool success = app.Init();
    if (success == false)
    {
        return 1;
    }

    // Run (and pass parameter to render screen from application)
    app.Run();

    return 0;
}
