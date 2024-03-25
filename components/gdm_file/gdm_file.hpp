#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>

#include "component.hpp"
#include "repo_addr_internet.hpp"
#include "repo_addr_project.hpp"
#include "repo_branch.hpp"
#include "repo_hints.hpp"

/*
enum class GdmFileType{
    project,
    comopnent,
};
*/

class GdmFile
{
private:
    std::fstream file;
    bool is_file;
    std::string path;
    bool garbage_string_skip(); // пропускает неинтересующие нас строки

    unsigned int gssnsdl = 1000; // garbage_string_skip_no_space_dist_lim
public:
    GdmFile();
    GdmFile(std::string path);
    Component get_comp();
    ~GdmFile();
};

