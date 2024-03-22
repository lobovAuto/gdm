#pragma once

#include "string"
#include "iostream"

class RepoAddrInternet
{
private:
    std::string addr;
public:
    RepoAddrInternet(std::string &);
    RepoAddrInternet(std::string);
    bool check_addr(){return true;}
    ~RepoAddrInternet();
};

