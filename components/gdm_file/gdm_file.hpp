#pragma once

#include <fstream>
#include <iostream>

#include "component.hpp"

class GdmFile
{
private:
    std::fstream file;
public:
    GdmFile(/* args */);
    Component get_comp();
    ~GdmFile();
};

