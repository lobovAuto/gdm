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
    bool is_project_file;
    std::string path;
    std::string _root_folder;
    std::string _root_rms;
    bool garbage_string_skip(); // пропускает неинтересующие нас строки

    unsigned int gssnsdl = 1000; // garbage_string_skip_no_space_dist_lim
public:
    GdmFile();
    GdmFile(std::string path);
    Component get_comp();
    std::string take_link(std::string &);
    void take_branch_and_commit(std::string &, std::string &, std::string &);
    ~GdmFile();
};

