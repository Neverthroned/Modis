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
    if (!success)
        return 1;

    // Run 
    app.Run();

    return 0;
}
