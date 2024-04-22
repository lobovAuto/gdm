#include "main.hpp"


int main(int argc, char* argv[]){
    //print_help();
    if (not std::filesystem::exists("./.gdm")){
        std::filesystem::create_directory("./.gdm");
    }
    std::ofstream log("./.gdm/log.txt");
    // std::clog.rdbuf(log.rdbuf());
    GdmFile project(log);
    ComponentsStruct comp_struct(log);

    string root_rm, root_folder, repo_address, address_call_file, branch, commit;
    bool is_full_path, is_force;
    for (;;){
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
        comp_struct.add_component(temp);
    }
    // comp_struct.check_struct_comp_to_reference();
    comp_struct.print_struct();
    std::cout<<"check res: "<<comp_struct.check_struct()<<std::endl;
    comp_struct.print_err_res();
    // Rri * temp_repo = new GitRri("ssh://git@git.redpioneer.ru:2224/tools/dbc_agent.git","./temp/tools/dbc_agent");
    // temp_repo->check_repo_to_gdm_files();
    // temp->clone();
    
}