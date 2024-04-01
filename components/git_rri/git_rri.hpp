#pragma once

#ifndef __cplusplus
#define __cplusplus
#endif

#include "boost/process.hpp"
#include "rri.hpp"
#include "iostream"
#include <vector>

class GitRri : public Rri
{
private:
    int boost_command(const char *, std::vector<std::string> &);
    int last_result;
    std::string url;
    std::string location;
public:
    GitRri(/* args */);
    GitRri(std::string, std::string);
    int push();
    int pull();
    int check_repo_to_gdm_files();
    int checkout();
    int status();
    int clone();
    ~GitRri();
};


