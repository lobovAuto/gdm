#include "component.hpp"

std::ostream& operator<<(std::ostream& stream, const Component& component){
    stream<<"component: ";
    stream<<component.get_repo_address()<<std::endl;
    stream<<"call counter: "<<component.get_comp_list().size()<<std::endl;
    auto iterator  = component.get_comp_list().begin();
    for (std::size_t i=0; i<component.get_comp_list().size(); i++){
        stream<<"call "<<i+1<<":"<<std::endl;
        stream<<"   "<<"project address: "<< iterator->address_in_project <<std::endl;
        stream<<"   "<<"file call addr : "<< iterator->address_call_file <<std::endl;
        stream<<"   "<<"branch:          "<< iterator->branch <<std::endl;
        if (iterator->branch_type==BranchType::branch){
            stream<<"   "<<"branch type"<<std::endl;
        }
        else {stream<<"   "<<"tag type"<<std::endl;}
        iterator=iterator++;
    }
    return stream;
}

void Component::add_call_source(std::string address_in_project, std::string address_call_file, 
                                BranchType branch_type, std::string branch){
    ComponentBroadcastUnit temp(address_in_project, address_call_file, branch_type, branch);
    comp_list.push_back(temp);    
}