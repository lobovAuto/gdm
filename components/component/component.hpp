#pragma once

#include <string>
#include <list>
#include <iostream>
#include <iterator>

enum class BranchType{
    branch,
    tag,
};

struct ComponentBroadcastUnit
{
    ComponentBroadcastUnit(std::string address_in_project, std::string address_call_file, 
                            BranchType branch_type, std::string branch):address_in_project(address_in_project), 
                            address_call_file(address_call_file), 
                            branch_type(branch_type), branch(branch){};
    std::string address_in_project;// адрес компонента в проекте
    std::string address_call_file; // адрес файла, который ссылается на данный компонент
    BranchType branch_type;        // тип ветки: хэш, имя, тэг
    std::string branch;            // имя тэга, хэш комита
};

typedef std::list<ComponentBroadcastUnit> CompList;

class Component{
public:
    Component(std::string repo_address, std::string address_in_project, 
            std::string address_call_file, BranchType branch_type, std::string branch) : 
            repo_address(repo_address){   
        ComponentBroadcastUnit temp(address_in_project, address_call_file, branch_type, branch);
        comp_list.push_back(temp);
    };
    Component():wrong(true){}; // Конструктор для возврата неверного компонента (метод поиска не нашел больше компонентов в файле и т.п.)
    void add_call_source(std::string address_in_project, std::string address_call_file, 
                        BranchType branch_type, std::string branch); // добавить еще один источник ссылки на репозиторий
    
    std::string get_repo_address () const {return repo_address;}
    CompList get_comp_list () const {return comp_list;}
private:
    bool wrong = false;
    std::string repo_address;    // адресс компонента для скачивания
    CompList comp_list;  // контейнер с данными о том, какие компоненты ссылаются на этот репозиторий
};

std::ostream& operator<<(std::ostream& stream, const Component& component);