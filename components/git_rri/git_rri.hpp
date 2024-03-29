#pragma once

#ifndef __cplusplus
#define __cplusplus
#endif

#include "git2.h"
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


