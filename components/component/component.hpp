#pragma once

#include <string>
#include <list>

enum class BranchType{
    branch,
    tag,
};

struct ComponentBroadcastUnit
{
    ComponentBroadcastUnit(std::string addr, BranchType branch_type, std::string branch):address_call_file(addr), branch_type(branch_type), branch(branch){};
    std::string address_call_file; // адрес файла, который ссылается на данный компонент
    BranchType branch_type;        // тип ветки: хэш, имя, тэг
    std::string branch;            // имя тэга, хэш комита
};

typedef std::list<ComponentBroadcastUnit> CompList;

class Component{
public:
    Component(std::string name, std::string repo_address, std::string address_call_file, BranchType branch_type, std::string branch) : name(name), repo_address(repo_address)
    {   
        ComponentBroadcastUnit temp(address_call_file, branch_type, branch);
        comp_list.push_back(temp);
    };
    void add_call_source(std::string address_call_file, BranchType branch_type, std::string branch); // добавить еще один источник ссылки на репозиторий
private:
    std::string name;    // имя компонента
    std::string repo_address; // адрес компонента в репозитории
    CompList comp_list;  // контейнер с данными о том, какие компоненты ссылаются на этот компонент
};