#pragma once

#ifndef __cplusplus
#define __cplusplus
#endif

#include "boost/process.hpp"
#include "rri.hpp"
#include "iostream"
#include <vector>
#include "filesystem"
#include "component.hpp"

class GitRri : public Rri
{
private:
    int boost_command(const char *, std::vector<std::string> &);
    std::ostream & log_stream; // поток для вывода лога
    int last_result;
    std::string url;
    std::string location;
    std::string branch;
    std::string commit;
    std::string folder_name; // имя папки для проверочного выкачивания
    const std::string get_folder_name();
public:
    GitRri(std::ostream & log_stream);
    GitRri(std::ostream & log_stream, std::string url, std::string location, std::string branch, std::string commit);
    GitRri(std::ostream & log_stream, const Component &);
    int push();
    int pull();
    int check_repo_to_gdm_file();
    int checkout();
    int status();
    int clone();

    const std::string get_folder_name() const {return folder_name;};

    ~GitRri();
};


