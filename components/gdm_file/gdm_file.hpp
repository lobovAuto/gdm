#pragma once

#include <fstream>
#include <iostream>

#include "component.hpp"
#include "repo_addr_internet.hpp"

class GdmFile
{
private:
    std::fstream file;
    bool garbage_string_skip(); // пропускает неинтересующие нас строки

    unsigned int gssnsdl = 1000; // garbage_string_skip_no_space_dist_lim
public:
    GdmFile(/* args */);
    Component get_comp();
    ~GdmFile();
};

