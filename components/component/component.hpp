#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <iomanip>

enum class BranchType{
    branch,
    tag,
};

struct ComponentBroadcastUnit
{
    ComponentBroadcastUnit(std::string const & address_call_file, 
                            std::string const & branch, std::string const & commit, 
                            bool is_force): 
                            address_call_file(address_call_file),branch(branch), commit(commit),is_force(is_force){};
    std::string address_call_file; // адрес файла, который ссылается на данный компонент
    std::string branch;            // имя тэга
    std::string commit;            // хэш комита
    bool is_force;
    bool operator==(const ComponentBroadcastUnit &) const;
};

typedef std::vector<ComponentBroadcastUnit> CompList;

using std::string;
class Component{
public:
    Component(string const & root_rms, string const & root_folder,
            string const & repo_address, string const & address_call_file, 
            bool is_full_path, string const & branch, 
            string const & commit, bool is_force) : 
            _root_rms(root_rms), _root_folder(root_folder),
            local_address(repo_address), _is_full_path(is_full_path){   
        ComponentBroadcastUnit temp(address_call_file, branch, commit, is_force);
        comp_list.push_back(temp);
        set_repo_address();
    };
    Component():wrong(true){}; // Конструктор для возврата неверного компонента (метод поиска не нашел больше компонентов в файле и т.п.)
    void add_call_source(string address_in_project, string address_call_file, 
                         string branch, bool is_force); // добавить еще один источник ссылки на репозиторий

    void add_call_source(const ComponentBroadcastUnit &);

    string get_repo_address () const {return repo_address;}
    string get_local_address() const {return local_address;}
    string get_commit() const;
    string get_addr_call_file() const;
    string get_branch() const;

    ComponentBroadcastUnit get_brdunit() const ; 
    void print_to_screen(std::ostream &);
    void print_for_log(std::ostream &);
    // перенести в приват 
    CompList comp_list;  // контейнер с данными о том, какие компоненты ссылаются на этот репозиторий
    bool get_health() const {return !wrong;}
    bool operator==(const Component&) const;
    bool addr_is_eq(const Component&) const;
    int check_component() const;
private:
    void set_repo_address ();
    const CompList & get_comp_list () const {return comp_list;}

    bool wrong = false;
    string _root_rms;       // ssh приставка для скачивая репозитория
    string _root_folder;    // корневой адрес, который опускается при выкачивании и добавлении в проект
    string repo_address;    // адрес компонента для скачивания
    string local_address;   //путь, который будет у компонента в проекте
    bool _is_full_path;  // флаг полного пути в repo_address
    mutable bool is_valid_force; // флаг наличия хинта force
    mutable unsigned force_pos; // номер форс элемента
};

std::ostream& operator<<(std::ostream& stream, const Component& component);