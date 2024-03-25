#include "repo_hints.hpp"

repo_::RepoHintType repo_::RepoHints::check_to_hint(const std::string input){
    std::size_t pos = std::min(input.size(), 
                        input.find_first_of(" ")); // нашли конец строки\длину хинта
    std::string hint(input, 0, pos);
    std::transform(hint.begin(), hint.end(), hint.begin(), toupper);
    if (hint=="FORCE"){
        return repo_::RepoHintType::force; 
    }
    return repo_::RepoHintType::none;
}

repo_::RepoHints::RepoHints(std::string input){
    if (input.find_first_of(" ")>1000){ // если пробелов нет, то хинты отсутствуют
        is_force = false;
        return;
    }
    input.erase(0,input.find_first_of(" ")+1); // убрали branch
    while (check_to_hint(input)!=repo_::RepoHintType::none)
    {
        switch (check_to_hint(input))
        {
        case repo_::RepoHintType::force:
            is_force = true;
            input.erase(0, 5);
            break;
        
        default:
            break;
        }
    }
    
}

repo_::RepoHints::~RepoHints()
{
}
