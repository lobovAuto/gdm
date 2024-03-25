#pragma once

#include "string"
#include "iostream"
#include "config.h"

namespace repo_{

enum class RepoConnectionType{
    https,
    http,
    ssh,
    ssh_github,
    home_repo,
};

class RepoAddrInternet
{
private:
    std::string addr;
    void check_type_repo();
    RepoConnectionType repo_type;
public:
    RepoAddrInternet(std::string &);
    RepoAddrInternet(const std::string);
    bool check_addr();
    std::string return_addr(){return addr;};
    ~RepoAddrInternet();
};
}

