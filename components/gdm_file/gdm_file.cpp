#include "gdm_file.hpp"

void delete_first_spaces(std::string & input){
    if ((input.find_first_not_of(" ")==0)||input.find_first_not_of(" ")>1000) return;
    std::string temp(input, input.find_first_not_of(" "), input.size());
    input = temp;
}

GdmFile::GdmFile(){
    file.open("project.gdm");
    if(not file.is_open()){
        std::cerr<<"There is no main project file."<<std::endl;
        exit(1);
    }
    is_file = true;
    path = std::filesystem::absolute(std::filesystem::path("project.gdm"));
}

GdmFile::GdmFile(std::string in_path){
    std::string curr_path = in_path + "component.gdm";
    file.open(curr_path);
    if(not file.is_open()){
        is_file = false;
    } else is_file = true;
    path = std::filesystem::absolute(std::filesystem::path(curr_path));
}

bool GdmFile::garbage_string_skip(){
    std::string buffer;           // буффер для считывания
    std::streampos position;        // переменная с текущей позицей в файле
    unsigned int safety_counter=0;
    while (true){
        position = file.tellp(); // запоминаем текущую позицию в файле
        safety_counter++;
        getline(file, buffer);
        bool flag_1 = buffer.find_first_not_of(" ")<gssnsdl;        // если первый символ не очень далеко
        bool flag_2 = buffer[buffer.find_first_not_of(" ")]!='#';   // если первый символ - не символ комментария
        if (flag_1 && flag_2) {
            file.seekp(position);
            break;
        }
        if (safety_counter>100) break;
    }
    return true;
}

Component GdmFile::get_comp(){
    if (file.eof()){
        return Component();
    }
    garbage_string_skip(); // пропускаем ненужные строки
    std::string read_line;
    getline(file, read_line);
        // std::cout<<"read string: "<<read_line<<std::endl;
    delete_first_spaces(read_line);
        // std::cout<<"updt string: "<<read_line<<std::endl;
    repo_::RepoAddrInternet repo_addr_intenet(std::string(read_line, 0, read_line.find_first_of(" ")));
        if (repo_addr_intenet.check_addr()==false){
            return Component();
        }
    read_line.erase(0,read_line.find_first_of(" ")+1);
        // std::cout<<"cut string: "<<read_line<<std::endl;
    repo_::RepoAddrProject repo_addr_project(std::string(read_line, 0, read_line.find_first_of(" ")));
    read_line.erase(0,read_line.find_first_of(" ")+1);
        // std::cout<<"cut string: "<<read_line<<std::endl;
    repo_::RepoBranch repo_branch(std::string(read_line, 0, read_line.find_first_of(" ")));
        // std::cout<<"cut string: "<<read_line<<std::endl;
    repo_::RepoHints repo_hints(read_line);
    bool isforce = repo_hints.isforce();
    if (is_project_file == false) isforce = 0;
    return Component(repo_addr_intenet.return_addr(),
                        repo_addr_project.return_addr(),
                        path,
                        repo_branch.return_branch(),
                        isforce);
}

GdmFile::~GdmFile(){

}