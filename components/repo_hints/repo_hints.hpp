#pragma once

#include <string>
#include <iostream>
#include <algorithm>
namespace repo_{

enum class RepoHintType{
    none,
    force,
};

class RepoHints
{
private:
    bool is_force = false;
    repo_::RepoHintType check_to_hint(const std::string);
public:
    RepoHints(std::string);
    ~RepoHints();
};

};