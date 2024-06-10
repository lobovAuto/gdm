#include "main.hpp"


int main(int argc, char* argv[]){
    // print_help();
    // return 0;
    if (not std::filesystem::exists("./.gdm")){
        std::filesystem::create_directory("./.gdm");    
    }
    std::ofstream log("./.gdm/log.txt");
    // std::clog.rdbuf(log.rdbuf());
    GdmFile project(log);
    ComponentsStruct comp_struct(log);

    string root_rm, root_folder, repo_address, address_call_file, branch, commit;
    bool is_full_path, is_force;
    for (;;){   // Цикл, считывающий главный gdm файл
        if (!project.get_comp(root_rm, root_folder, repo_address, 
                                address_call_file, is_full_path, 
                                branch, commit, is_force))
        {
            break;
        }
        Component temp(root_rm, root_folder, repo_address, 
                        address_call_file, is_full_path, 
                        branch, commit, is_force);
        temp.print_for_log(log);
        log<<"________________"<<std::endl;
        comp_struct.add_component(temp);
    }
    log<<"Parsing dependency files was completed!"<<std::endl;

    if(!comp_struct.check_struct()){
        return 1;
    }

    log<<"Download applicants:"<<std::endl;
    comp_struct.print_all_paths();
    log<<"Try to download ..."<<std::endl;
    comp_struct.clone_all_components();
    
}