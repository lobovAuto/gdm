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
    std::ostream & log_stream; // поток для вывода лога
    std::fstream file;
    bool is_file;
    bool is_project_file;
    std::string path = "NULL";
    bool _is_root_exist;
    std::string _root_folder = "NULL";
    std::string _root_rms = "NULL";
    bool garbage_string_skip(); // пропускает неинтересующие нас строки

    unsigned int gssnsdl = 1000; // garbage_string_skip_no_space_dist_lim
public:
    // GdmFile();
    GdmFile(std::ostream & log_stream);
    GdmFile(std::string path , std::ostream & log_stream);
    Component get_comp();
    bool take_link(std::string & in, std::string & link);
    void take_branch_and_commit(std::string &, std::string &, std::string &);
    bool check_force(std::string & in);
    ~GdmFile();
};

