#pragma once

#ifndef __cplusplus
#define __cplusplus
#endif

#include "boost/process.hpp"
#include "rri.hpp"
#include "iostream"
#include <vector>
#include "filesystem"

class GitRri : public Rri
{
private:
    int boost_command(const char *, std::vector<std::string> &);
    int last_result;
    std::string url;
    std::string location;
    std::string branch;
    std::string folder_name; // имя папки для проверочного выкачивания
    const std::string get_folder_name();
public:
    GitRri(/* args */);
    GitRri(std::string url, std::string location, std::string branch);
    int push();
    int pull();
    int check_repo_to_gdm_files();
    int checkout();
    int status();
    int clone();
    ~GitRri();
};


