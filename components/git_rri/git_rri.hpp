#pragma once

#ifndef __cplusplus
#define __cplusplus
#endif


#include "rri.hpp"
#include "iostream"

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


