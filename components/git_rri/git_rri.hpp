#pragma once

#include "rri.hpp"

class GitRri : public Rri
{
private:
    /* data */
public:
    GitRri(/* args */);
    int push();
    int pull();
    int check_repo_to_gdm_files();
    int checkout();
    int status();
    int clone();
    ~GitRri();
};


