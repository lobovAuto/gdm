#include "component.hpp"

bool ComponentBroadcastUnit::operator==(const ComponentBroadcastUnit & input) const {
    if ((address_in_project==input.address_in_project)&&(branch==input.branch))
        return true;
    else 
        return false;
}

void Component::print_to_screen (){
    std::cout<<"component: ";
    std::cout<<repo_address<<std::endl;
    std::cout<<"call counter: "<<get_comp_list().size()<<std::endl;
    auto iterator  = get_comp_list().begin();
    for (std::size_t i=0; i<get_comp_list().size(); i++){
        std::cout<<"call "<<i+1<<":"<<std::endl;
        std::cout<<"   "<<"project address: "<< comp_list[i].address_in_project <<std::endl;
        std::cout<<"   "<<"file call addr : "<< comp_list[i].address_call_file <<std::endl;
        std::cout<<"   "<<"branch:          "<< comp_list[i].branch <<std::endl;
        std::cout<<"   "<<"is force:        "<< comp_list[i].is_force <<std::endl;
        /*
        if (iterator->branch_type==BranchType::branch){
            std::cout<<"   "<<"branch type"<<std::endl;
        }
        else {std::cout<<"   "<<"tag type"<<std::endl;}
        */
        iterator=iterator++;
    }
}

[[deprecated]] void Component::add_call_source(std::string address_in_project, std::string address_call_file, 
                                std::string branch, bool is_force){
    ComponentBroadcastUnit temp(address_in_project, address_call_file, branch, is_force);
    comp_list.push_back(temp);    
}

// void Component::add_call_source(const ComponentBroadcastUnit & input){
    // comp_list.push_back(input);
// }

void Component::add_call_source(const ComponentBroadcastUnit input){
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
        if (get_comp_list()[j].is_force) ++force_count;
    }
    if (force_count == 1) return 0;
    else if (force_count>1) return 2;
    else if (res) return 1;
    else return 0;
}