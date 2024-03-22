#include "repo_addr_internet.hpp"

void RepoAddrInternet::check_type_repo(){
    std::string https_prefix(addr, 0, 5);
    if (https_prefix=="https"){
        repo_type=RepoConnectionType::https;
        return;
    }
    std::string http_prefix(addr, 0, 4);
    if (http_prefix=="http"){
        repo_type=RepoConnectionType::http;
        return;
    }
    std::string ssh_prefix(addr, 0, 3);
    if (ssh_prefix=="git"){
        repo_type=RepoConnectionType::ssh;
        return;
    }
    std::string ssh_github_prefix(addr, 0, 3);
    if (ssh_github_prefix=="ssh"){
        repo_type=RepoConnectionType::ssh_github;
        return;
    }
    if (addr[0]=='/'){ //уборка ожидаемой ошибки при начале адреса с /
        std::string temp(addr, 1, addr.size());
        addr=temp;
    }
    repo_type=RepoConnectionType::home_repo;
    addr = HOME_REPO + addr;
}

RepoAddrInternet::RepoAddrInternet(std::string & input):addr(input){
}
RepoAddrInternet::RepoAddrInternet(std::string  input):addr(input){
    check_type_repo();
}

bool RepoAddrInternet::check_addr(){
    std::string git_suffix (addr, addr.size()-4);
    if (git_suffix!=".git"){
        return false;
    }
    return true;
}

RepoAddrInternet::~RepoAddrInternet(){
}