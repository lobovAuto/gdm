#include "gdm_file.hpp"

void delete_first_spaces(std::string & input){
    if (input.find_first_not_of(" ")==0) return;
    std::string temp(input, input.find_first_not_of(" "), input.size());
    input = temp;
}

GdmFile::GdmFile(){
    file.open("project.gdm");
    if(not file.is_open()){
        std::cerr<<"There is no main project file."<<std::endl;
        exit(1);
    }
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
    RepoAddrInternet repo_addr_intenet(std::string(read_line, 0, read_line.find_first_of(" ")));
    
    return Component();
}

GdmFile::~GdmFile(){

}