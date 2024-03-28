#pragma once

#include "libgit2/common.h"
#include "libgit2/libgit2.h"
#include "libgit2/repository.h"
#include "git2.h"
#include "git2/types.h"
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


