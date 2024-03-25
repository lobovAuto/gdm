#pragma once

#include "string"

namespace repo_{

enum class BranchType{ //to del?
    head,
    tag,
    hash,
};

class RepoBranch
{
private:
    BranchType branch_type;
    const std::string branch;
public:
    std::string return_branch(){return branch;};
    RepoBranch(const std::string);
    ~RepoBranch();
};

}
