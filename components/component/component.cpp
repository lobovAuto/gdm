#include "component.hpp"

bool ComponentBroadcastUnit::operator==(const ComponentBroadcastUnit & input) const {
    if ((commit==input.commit)&&(branch==input.branch))
        return true;
    else 
        return false;
}

void Component::print_to_screen (std::ostream & out){
    out<<"component: ";
    out<<repo_address<<std::endl;
    out<<"call counter: "<<get_comp_list().size()<<std::endl;
    auto iterator  = get_comp_list().begin();
    for (std::size_t i=0; i<get_comp_list().size(); i++){
        int a = 20;
        out<<"call "<<i+1<<":"<<std::endl;
        out.fill('*');
        // out << std::setw(a);
        out << std::setw(a);
        out<<"file call addr: "<< comp_list[i].address_call_file <<std::endl;
        out << std::setw(a);
        out<<"branch: "<< comp_list[i].branch <<std::endl;
        out << std::setw(a);
        out<<"commit: "<< comp_list[i].commit <<std::endl;
        out << std::setw(a);
        out<<"is force: ";
        out<<std::boolalpha;
        out<< comp_list[i].is_force <<std::endl;
        iterator=iterator++;
    }
}
void Component::print_for_log(std::ostream & out){
    int a = 20;
    out << std::setw(a);
    out<<"component: ";
    out<<repo_address<<std::endl;
    out << std::setw(a);
    out<<"root_rms: "<<_root_rms<<std::endl;
    out << std::setw(a);
    out<<"root_folder: "<<_root_folder<<std::endl;
    out << std::setw(a);
    out<<"is full path: "<<_is_full_path<<std::endl;
    out << std::setw(a);
    out<<"file call addr : "<< comp_list[0].address_call_file <<std::endl;
    out << std::setw(a);
    out<<"branch: "<< comp_list[0].branch <<std::endl;
    out << std::setw(a);
    out<<"commit: "<< comp_list[0].commit <<std::endl;
    out << std::setw(a);
    out<<"is force: "<<std::boolalpha<< comp_list[0].is_force <<std::endl;
}

[[deprecated]] void Component::add_call_source(std::string address_in_project, std::string address_call_file, 
                                std::string branch, bool is_force){
    ComponentBroadcastUnit temp(address_in_project, address_call_file, branch, is_force);
    comp_list.push_back(temp);    
}

void Component::add_call_source(const ComponentBroadcastUnit & input){
    comp_list.push_back(input);
}

ComponentBroadcastUnit Component::get_brdunit() const {
    if (!comp_list.size())
        throw "there are not broadcast unit";
    return comp_list[0];
} 

bool Component::addr_is_eq(const Component & input) const {
    std::string input_addr = input.get_repo_address();
    if ((repo_address == input_addr)){
        return true;
    }
    return false;
}

bool Component::operator==(const Component & input) const {
    if ((repo_address == input.get_repo_address())){
        if (get_comp_list()==input.get_comp_list())
            return true;
    }
    return false;
}

/**
 * @result 0 - Если ошибок нет,
 * @result 1 - Если разняться хэши\указатели\ветки
 * @result 2 - Если force больше 1
*/
int Component::check_component() const {
    if (get_comp_list().size()==1) {
            return 0;
    }
    bool res=false; // временная переменная
    for (size_t j=0; j<get_comp_list().size(); j++){ // идем по всем значениям вектора ComponentBroadcastUnit
        for (size_t k=j+1; k<get_comp_list().size(); k++){ // сравниваем "взятое" ранее значение со следующим
            if (not(get_comp_list()[j]==                   // если они не равны, то поднимаем флаг ошибки
                    get_comp_list()[k])){
                res = true;
                break;
            }
        }
        if (res) break;
    }
    unsigned force_count=0;
    for (size_t j=0; j<get_comp_list().size(); j++){      // Подсчет хинтов force
        if (get_comp_list()[j].is_force) {
            ++force_count;
            force_pos = j; // запоминаем позицию форс ComponentBroadcastUnit
        }
    }
    if (force_count == 1) {
        is_valid_force = 1; // отмечаем в компоненте, что есть валидный force
        return 0;
    }
    else if (force_count>1) return 2;
    else if (res) return 1;
    else return 0;
}

std::string Component::get_commit() const {
    if (is_valid_force){
        return comp_list[force_pos].commit;
    }
    else {
        return comp_list[0].commit;
    }
}
std::string Component::get_addr_call_file() const {
    if (is_valid_force){
        return comp_list[force_pos].address_call_file;
    }
    else {
        return comp_list[0].address_call_file;
    }
}
std::string Component::get_branch() const {
    if (is_valid_force){
        return comp_list[force_pos].branch;
    }
    else {
        return comp_list[0].branch;
    }
}

void Component::set_repo_address () {
    std::string temp = _root_rms;
    if (_is_full_path){
        temp+="/"+local_address;
    }
    else {
        temp+="/"+_root_folder+"/"+local_address;
    } 
    repo_address = temp;
}