#include <iostream>
#include <fstream>
#include "utilities.h"

Utilities::Utilities()
{
}

Utilities::~Utilities()
{
}

std::string Utilities::openFile(std::string path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cout << path << "isn't open" << std::endl;
        return "";
    }

    // Write complete string to buffer
    std::stringstream buffer;
    buffer << file.rdbuf();

    // Write buffer to contents string
    std::string contents = buffer.str();

    // File cleanup and return
    file.close();
    return contents;
}
