#include "gdm_file.hpp"

void delete_first_spaces(std::string & input){
    if ((input.find_first_not_of(" ")==0)||input.find_first_not_of(" ")>1000) return;
    std::string temp(input, input.find_first_not_of(" "), input.size());
    input = temp;
}

void delete_end_line_spaces(std::string & input){
    if (input.find_first_of(" ")!=std::string::npos){
    input.erase(input.find_first_of(" "), input.length());
    }
}

void delete_key_word(std::string & input){
    if (input.find("LINK")<1000){
        input.erase(input.find("LINK"), 5);
    }
}

void delete_key_word(std::string & input, const char * key){
    if (input.find(key)<1000){
        delete_first_spaces(input);
        input.erase(input.find(key), input.find_first_of(" ")+1);
    }
}

keyword GdmFile::define_keyword(std::string & buffer){
    if (buffer.find("LINK")<1000) return keyword::LINK;
    else if (buffer.find("ROOT_RMS")<1000) return keyword::ROOT_RMS;
    else if (buffer.find("ROOT_FOLDER")<1000) return keyword::ROOT_FOLDER;
    else return keyword::ERR;
}

/**
 * @brief Конструктор главного файла проекта
*/
GdmFile::GdmFile(std::ostream & log_stream):log_stream(log_stream){
    log_stream<<"Opening main project file..."<<std::endl;
    file.open("project.gdm");
    if(not file.is_open()){
        log_stream<<"There is no main project file."<<std::endl;
        std::cerr<<"There is no main project file."<<std::endl;
        exit(1);
    }
    log_stream<<"Main project file has been sucsessfully opened."<<std::endl;
    is_file = true;
    path = std::filesystem::absolute(std::filesystem::path("project.gdm"));
    keyword _return=garbage_string_skip();
    while ((_return==keyword::ROOT_FOLDER)||(_return==keyword::ROOT_RMS)){
        std::string buffer;
        getline(file, buffer);
        switch (_return)
        {
        case keyword::ROOT_FOLDER:
            delete_key_word(buffer, "ROOT_FOLDER");
            delete_end_line_spaces(buffer);
            buffer.erase(0, buffer.find_first_not_of("/"));
            _root_folder=buffer;
            log_stream<<"root folder was set as: "<<_root_folder<<std::endl;
            break;
        case keyword::ROOT_RMS:
            delete_key_word(buffer, "ROOT_RMS");
            delete_end_line_spaces(buffer);
            _root_rms=buffer;
            log_stream<<"root rms was set as: "<<_root_rms<<std::endl;
            break;
        default:
            break;
        }
        _return=garbage_string_skip();

    }
}

/**
 * @brief Конструктор файла компонента проекта
*/
GdmFile::GdmFile(std::string in_path, std::ostream & log_stream):log_stream(log_stream){
    std::string curr_path = in_path + "component.gdm";
    file.open(curr_path);
    if(not file.is_open()){
        is_file = false;
    } else is_file = true;
    path = std::filesystem::absolute(std::filesystem::path(curr_path));
}

/**
 * @brief  Метод пропускает в обрабатываемом файле пустые строки, комментарии и т.п.
*/
keyword GdmFile::garbage_string_skip(){
    std::string buffer;           // буффер для считывания
    std::streampos position;        // переменная с текущей позицей в файле
    unsigned int safety_counter=0;
    while (true){
        position = file.tellp(); // запоминаем текущую позицию в файле
        safety_counter++;
        getline(file, buffer);
        log_stream<<"Read line: "<<buffer<<std::endl;
        bool flag_1 = buffer.find_first_not_of(" ")<gssnsdl;        // если первый символ не очень далеко
        bool flag_2 = buffer[buffer.find_first_not_of(" ")]!='#';   // если первый символ - не символ комментария
        bool flag_3 = buffer.find("LINK")<gssnsdl;                  // Если строка начинается с LINK
        bool flag_4 = buffer.find("ROOT_FOLDER")<gssnsdl;           // Если в строке есть ROOT_FOLDER
        bool flag_5 = buffer.find("ROOT_RMS")<gssnsdl;              // Если в строке есть ROOT_RMS
        if (flag_1 && flag_2 && (flag_3 || flag_4 || flag_5)) {
            keyword temp;
            log_stream<<"Line was recognized as correct"<<std::endl;
            if (flag_3) temp = keyword::LINK;
            else if (flag_4) temp = keyword::ROOT_FOLDER;
            else if (flag_5) temp = keyword::ROOT_RMS;
            file.seekp(position);
            return temp;
            break;
        }
        if (position==-1) {
            return keyword::ERR;
        }
    }
}


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
        if (commit=="head") commit = "HEAD";
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
    if (garbage_string_skip()==keyword::ERR) return Component(); // пропускаем ненужные строки
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

bool GdmFile::get_comp(string & root_rms, string & root_folder,
            string & repo_address, string & address_call_file, 
            bool & is_full_path, string & branch, 
            string & commit, bool & is_force){
    if (file.eof()){
        log_stream<<"The end of the file has been reached"<<std::endl;
        return false;
    }
    if (garbage_string_skip()==keyword::ERR) return false; // пропускаем ненужные строки
    std::string read_line;
    getline(file, read_line);
        // log_stream<<"________________"<<std::endl;
        // log_stream<<"read string: "<<read_line<<std::endl;
        log_stream<<"was parsing as: "<<std::endl;
        
    delete_key_word(read_line);
    is_full_path =  take_link(read_line, repo_address);
    take_branch_and_commit(read_line, branch, commit);
    is_force = check_force(read_line);
    root_rms = _root_rms;
    root_folder = _root_folder;
    address_call_file = path;
    return true;
}

GdmFile::~GdmFile(){

}