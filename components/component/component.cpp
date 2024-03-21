#include "component.hpp"

void Component::add_call_source(std::string address_call_file, BranchType branch_type, std::string branch){
    ComponentBroadcastUnit temp(address_call_file, branch_type, branch);
    comp_list.push_back(temp);    
}