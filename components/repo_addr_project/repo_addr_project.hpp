#pragma once

#include "string"

namespace repo_{

class RepoAddrProject
{
private:
   std::string addr;
public:
    RepoAddrProject(const std::string);
    std::string return_addr(){return addr;};
    ~RepoAddrProject();
};

}

