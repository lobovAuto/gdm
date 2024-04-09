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
                            std::string branch, bool is_force):address_in_project(address_in_project), 
                            address_call_file(address_call_file),branch(branch),is_force(is_force){};
    std::string address_in_project;// адрес компонента в проекте
    std::string address_call_file; // адрес файла, который ссылается на данный компонент
    std::string branch;            // имя тэга, хэш комита
    bool is_force;
    bool operator==(const ComponentBroadcastUnit &) const;
};

typedef std::vector<ComponentBroadcastUnit> CompList;

class Component{
public:
    Component(std::string repo_address, std::string address_in_project, 
            std::string address_call_file, std::string branch, bool is_force) : 
            repo_address(repo_address){   
        ComponentBroadcastUnit temp(address_in_project, address_call_file, branch, is_force);
        comp_list.push_back(temp);
    };
    Component():wrong(true){}; // Конструктор для возврата неверного компонента (метод поиска не нашел больше компонентов в файле и т.п.)
    void add_call_source(std::string address_in_project, std::string address_call_file, 
                         std::string branch, bool is_force); // добавить еще один источник ссылки на репозиторий
    // void add_call_source(const ComponentBroadcastUnit &);
    void add_call_source(const ComponentBroadcastUnit);
    std::string get_repo_address () const {return repo_address;}
    const CompList & get_comp_list () const {return comp_list;}
    ComponentBroadcastUnit get_brdunit() const ; 
    void print_to_screen();
    // перенести в приват 
    CompList comp_list;  // контейнер с данными о том, какие компоненты ссылаются на этот репозиторий
    bool get_health() const {return !wrong;}
    bool operator==(const Component&) const;
    bool addr_is_eq(const Component&) const;
    int check_component() const;
private:
    bool wrong = false;
    std::string repo_address;    // адрес компонента для скачивания
    mutable bool is_valid_force; // флаг наличия хинта force
    mutable unsigned force_pos; // номер форс элемента
};

std::ostream& operator<<(std::ostream& stream, const Component& component);