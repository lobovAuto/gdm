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

GdmFile::GdmFile(std::ostream & log_stream):log_stream(log_stream){
    log_stream<<"Opening main project file..."<<std::endl;
    file.open("project.gdm");
    if(not file.is_open()){
        std::cerr<<"There is no main project file."<<std::endl;
        exit(1);
    }
    is_file = true;
    path = std::filesystem::absolute(std::filesystem::path("project.gdm"));
}

GdmFile::GdmFile(std::string in_path, std::ostream & log_stream):log_stream(log_stream){
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
        if (position==-1) {
            return false;
        }
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

/**
 * Возвращает ДА, если ссылка с полным путем
 * Возвращает НЕТ, если ссылка короткая
*/
bool GdmFile::take_link(std::string & in, std::string & link){
    link = in.substr(0, in.find_first_of(" "));
    in.erase(0, in.find_first_of(" "));
    in.erase(0, in.find_first_not_of(" "));
    if (link.find("//")==0){ // случай, когда указан полный путь
        link.erase(0,2); 
        return true;
    }
    else {
        if (link.find_first_of("/")==0) link.erase(0,1);
        return false;
    }
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
    if((slash_pos==space_pos)&&(space_pos==std::string::npos)){    // Если после ветки совсем ничего нет
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

bool GdmFile::check_force(std::string & in){
    if (path!=std::filesystem::absolute(std::filesystem::path("project.gdm"))){  // force может быть только в корне
        return false;
    }
    if (in.size()<5) return false; 
    in.erase(0, in.find_first_not_of(" "));
    std::transform(in.begin(), in.end(), in.begin(), toupper);
    if (in.find("FORCE")==0){
        return true;
    } else return false;
}

Component GdmFile::get_comp(){
    if (file.eof()){
        return Component();
    }
    if (!garbage_string_skip()) return Component(); // пропускаем ненужные строки
    std::string read_line;
    getline(file, read_line);
        log_stream<<"________________"<<std::endl;
        log_stream<<"read string: "<<read_line<<std::endl;
        log_stream<<"was parsing as: "<<std::endl;
        
    delete_key_word(read_line);
    std::string link;
    bool is_full_path =  take_link(read_line, link);
    std::string branch;
    std::string commit;
    take_branch_and_commit(read_line, branch, commit);
    bool is_force = check_force(read_line);
    Component temp (_root_rms, _root_folder, link, path, is_full_path, branch, commit, is_force);
    temp.print_for_log(log_stream);
    return temp;
}
GdmFile::~GdmFile(){

}