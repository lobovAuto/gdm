#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <iterator>

enum class BranchType{
    branch,
    tag,
};

struct ComponentBroadcastUnit
{
    ComponentBroadcastUnit(std::string address_in_project, std::string address_call_file, 
                            std::string branch):address_in_project(address_in_project), 
                            address_call_file(address_call_file),branch(branch){};
    std::string address_in_project;// адрес компонента в проекте
    std::string address_call_file; // адрес файла, который ссылается на данный компонент
    std::string branch;            // имя тэга, хэш комита
};

typedef std::vector<ComponentBroadcastUnit> CompList;

class Component{
public:
    Component(std::string repo_address, std::string address_in_project, 
            std::string address_call_file, std::string branch) : 
            repo_address(repo_address){   
        ComponentBroadcastUnit temp(address_in_project, address_call_file, branch);
        comp_list.push_back(temp);
    };
    Component():wrong(true){}; // Конструктор для возврата неверного компонента (метод поиска не нашел больше компонентов в файле и т.п.)
    void add_call_source(std::string address_in_project, std::string address_call_file, 
                         std::string branch); // добавить еще один источник ссылки на репозиторий
    // void add_call_source(const ComponentBroadcastUnit &);
    void add_call_source(const ComponentBroadcastUnit);
    std::string get_repo_address () const {return repo_address;}
    CompList get_comp_list () const {return comp_list;}
    ComponentBroadcastUnit get_brdunit() const ; 
    void print_to_screen();
    // перенести в приват 
    CompList comp_list;  // контейнер с данными о том, какие компоненты ссылаются на этот репозиторий
    bool get_health() const {return !wrong;}
private:
    bool wrong = false;
    std::string repo_address;    // адресс компонента для скачивания
    
};

std::ostream& operator<<(std::ostream& stream, const Component& component);