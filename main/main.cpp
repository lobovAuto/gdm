#include "main.hpp"


int main(int argc, char* argv[]){

    if (not std::filesystem::exists("./.gdm")){
        std::filesystem::create_directory("./.gdm");
    }

    GdmFile project;
    ComponentsStruct comp_struct;
    Component temp = project.get_comp();

    while (temp.get_health()){
        comp_struct.add_component(temp);
        temp = project.get_comp();
    }
    // comp_struct.check_struct_comp_to_reference();
    comp_struct.print_struct();
    std::cout<<"check res: "<<comp_struct.check_struct()<<std::endl;
    comp_struct.print_err_res();
    // Rri * temp_repo = new GitRri("ssh://git@git.redpioneer.ru:2224/tools/dbc_agent.git","./temp/tools/dbc_agent");
    // temp_repo->check_repo_to_gdm_files();
    // temp->clone();
    
}