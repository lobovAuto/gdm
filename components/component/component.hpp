#pragma once

#include <string>
#include <list>

enum class BranchType{
    branch,
    tag,
};

struct ComponentBroadcastUnit
{
    std::string address_call_file; // адрес файла, который ссылается на данный компонент
    BranchType branch_type;        // тип ветки: хэш, имя, тэг
    std::string branch;            // имя тэга, хэш комита
};

typedef std::list<ComponentBroadcastUnit> CompList;

class Component{
public:
    Component(std::string name, std::string address){};
private:
    std::string name;    // имя компонента
    std::string address; // адрес компонента в репозитории
    CompList comp_list;  // контейнер с данными о том, какие компоненты ссылаются на этот компонент
};