#include "gdm_file.hpp"

void delete_first_spaces(std::string & input){
    if ((input.find_first_not_of(" ")==0)||input.find_first_not_of(" ")>1000) return;
    std::string temp(input, input.find_first_not_of(" "), input.size());
    input = temp;
}

void delete_key_word(std::string & input){
    if (input.find("LINK")<1000){
        input.erase(input.find("LINK"), 5);
    }
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
        bool flag_3 = buffer.find("LINK")<gssnsdl;                  // Если строка начинается с LINK
        if (flag_1 && flag_2 && flag_3) {
            file.seekp(position);
            break;
        }
        if (safety_counter>100) break;
    }
    return true;
}

// Component GdmFile::get_comp(){
    // if (file.eof()){
        // return Component();
    // }
    // garbage_string_skip(); // пропускаем ненужные строки
    // std::string read_line;
    // getline(file, read_line);
        // std::cout<<"read string: "<<read_line<<std::endl;
    // delete_first_spaces(read_line); //вероятно, эту строку можно удалять
    // delete_key_word(read_line);
        // std::cout<<"updt string: "<<read_line<<std::endl;
    // repo_::RepoAddrInternet repo_addr_intenet(std::string(read_line, 0, read_line.find_first_of(" ")));
        // if (repo_addr_intenet.check_addr()==false){
            // return Component();
        // }
    // read_line.erase(0,read_line.find_first_of(" ")+1);
        // std::cout<<"cut string: "<<read_line<<std::endl;
    // repo_::RepoAddrProject repo_addr_project(std::string(read_line, 0, read_line.find_first_of(" ")));
    // read_line.erase(0,read_line.find_first_of(" ")+1);
        // std::cout<<"cut string: "<<read_line<<std::endl;
    // repo_::RepoBranch repo_branch(std::string(read_line, 0, read_line.find_first_of(" ")));
        // std::cout<<"cut string: "<<read_line<<std::endl;
    // repo_::RepoHints repo_hints(read_line);
    // bool isforce = repo_hints.isforce();
    // if (is_project_file == false) isforce = 0;
    // return Component(repo_addr_intenet.return_addr(),
                        // path,
                        // repo_branch.return_branch(),
                        // repo_commit.return_branch(),
                        // isforce);
// }

std::string GdmFile::take_link(std::string & in){

}

void GdmFile::take_branch_and_commit(std::string & in, std::string & branch, std::string & commit){
    std::size_t slash_pos = in.find_first_of("/");
    std::size_t space_pos = in.find_first_of(" ");
    if(slash_pos<space_pos){                        // Если стоит slash, то у нас точно есть комит
        branch = in.substr(0, slash_pos);
        std::size_t commit_length;
        if (space_pos==std::string::npos){          // Если нет пробелов в строке
            commit_length = in.size()-slash_pos;    // То тогда длина комита размер строки минус позиция слэша
        }
        else commit_length = space_pos-slash_pos;   // Иначе - разница между позицией пробела и слэша
        commit = in.substr(slash_pos+1,commit_length);
        in.erase(0,branch.size()+commit.size()+1); // стерли из считанной строки ветку и комит
        return;
    }
    if(slash_pos==space_pos==std::string::npos){    // Если после ветки совсем ничего нет
        branch = in;
        commit = "HEAD";
        in.erase(0, in.size());
        return;
    }
    if(space_pos<slash_pos){                        // Если после ветки есть пробел
        branch = in.substr(0, space_pos);
        in.erase(0, space_pos);                     // Удаляем из строки ветку
        in.erase(0, in.find_first_not_of(" "));     // Удаляем все пробелы
        if(in.size()==0){                           // Если после удаления пробела строка осталась пустой, то комит - HEAD
            commit = "HEAD";
            return;
        }
        std::string temp;                           // Делаем переменную темп, записываем в нее следующее слово
        if (in.find_first_of(" ")){
            temp = in.substr( 0, in.find_first_of(" "));
        } else temp = in;
        commit = temp;
        std::transform(temp.begin(), temp.end(), temp.begin(), toupper);
        if (temp == "FORCE") commit = "HEAD";       // Если следующее слово FORCE, то коммит становиться HEAD
    }
}

Component GdmFile::get_comp(){
    if (file.eof()){
        return Component();
    }
    garbage_string_skip(); // пропускаем ненужные строки
    std::string read_line;
    getline(file, read_line);
        // std::cout<<"read string: "<<read_line<<std::endl;
    // delete_first_spaces(read_line); //вероятно, эту строку можно удалять
    delete_key_word(read_line);
        // std::cout<<"updt string: "<<read_line<<std::endl;
    std::string root_folder = "NONE";
    std::string root_rms = "NONE";
    std::string link = take_link(read_line);
    std::string branch;
    std::string commit;
    take_branch_and_commit(read_line, branch, commit);
    
}
GdmFile::~GdmFile(){

}