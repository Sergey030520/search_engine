//

//// Created by Malip on 15.04.2022.

#include "ConverterJSON.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include "EngineException.h"
#include "ConsoleOutput.h"
#include "GeneratorJsonAnswers.h"


ConverterJSON::ConverterJSON(){
    try {
        config_file = LoadJsonFile(fs::path(path_to_conf_files.string() + "config.json"));
    }catch (EngineException* except){
        ConsoleOutput().PrintLn(except->what());
    }
    if(!config_file.contains("config")){
        throw new EngineException("Exception: config file is empty!");
    }
    float version = ReadVersionEngine(config_file.at("config"));
    if(searchEngine.version != version){
        throw new EngineException("Exception: has incorrect file version!");
    }
    if(config_file.contains("name")){
       searchEngine.name = config_file.at("name");
    }
    ShowEngine();
}

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    if(!config_file.contains("files")) return {};

    vector<string> files;
    for(const auto& path_to_file : config_file.at("files")){
        try {
            files.emplace_back(GetTextDocument(path_to_file));
        }catch (EngineException* except){
            ConsoleOutput().PrintLn(except->what());
        }
    }
    return files;
}

string ConverterJSON::GetTextDocument(const string& path_to_doc) {
    ifstream file;
    file.open(path_to_doc);
    if (file.is_open()) {
        auto text = ReadStreamDataDoc(&file);
        file.close();
        return text;
    }else{
        throw new EngineException("Exception: File " +
                                  fs::path(path_to_doc).filename().string() + " is not find!");
    }
}

string ConverterJSON::ReadStreamDataDoc(ifstream* stream_doc) {
    string text, line;
    int count_words = 0, count_chars_in_word = 0;
    while (getline(*stream_doc, line)) {
        if(SafeReadString(count_words, count_chars_in_word, line, text) == STOP_READ){
            return text;
        }
    }
    return text;
}

bool ConverterJSON::SafeReadString(int &count_read_words, int &count_read_chars_word,
                                   const string &line, string &text) {
    for(char symbol : line) {
        if (symbol != ' ') {
            if (count_read_chars_word < MAX_CHARS_WORD) {
                text += symbol;
                ++count_read_chars_word;
            } else {
                ConsoleOutput().PrintLn("Exception: Exceeding the number of letters in a word!");
            }
        } else if (count_read_chars_word != 0) {
            count_read_chars_word = 0;
            count_read_words++;
            text += symbol;
            if (count_read_words >= MAX_WORDS_FILE) {
                ConsoleOutput().PrintLn("Exception: Exceeding the allowed number of words in the text!");
                return STOP_READ;
            }
        }

    }
    return CONTINUE_READ;
}

int ConverterJSON::GetResponsesLimit() {
    if (config_file.at("config").contains("max_responses")) {
        return config_file.at("config").at("max_responses");
    }
    return MAX_RESPONSES;
}

std::vector<std::string> ConverterJSON::GetRequests() {
    json data_json;
    vector<string> text_requests;
    try {
        data_json = LoadJsonFile(fs::path(path_to_conf_files.string() + "requests.json"));
    }catch (EngineException* except){
        ConsoleOutput().PrintLn(except->what());
    }
    if(data_json.contains("requests")){
        for(const auto& request : data_json.at("requests")){
            if(CheckCountWordsInRequest(request)){
               text_requests.emplace_back(request);
            }
            if(text_requests.size() == MAX_REQUESTS){
                break;
            }
        }
    }
    return text_requests;
}

void ConverterJSON::PutAnswers(std::vector<std::vector<std::pair<size_t, float>>> answers) {
    ofstream file_answers;
    file_answers.open(path_to_conf_files.string() + "answers.json");
    file_answers << GeneratorJsonAnswers(GetResponsesLimit()).Generate(&answers);
    file_answers.flush();
    file_answers.close();
}

bool ConverterJSON::CheckCountWordsInRequest(const string &request) {
    std::stringstream stream(request);
    int count_words =
            std::distance(std::istream_iterator<std::string>(stream),
                    std::istream_iterator<std::string>());
    if(count_words != MAX_WORDS_REQUEST && count_words >= MIN_WORDS_REQUEST) {
        return true;
    }else{
        ConsoleOutput().PrintLn("Exception: Bad request! Max number words in request 10 and minimum 1!");
        return false;
    }
}

json ConverterJSON::LoadJsonFile(const fs::path& path_to_file) {
    ifstream file(path_to_file.string());
    if(!file.is_open()){
        throw new EngineException(("Exception: config " + path_to_file.filename().string() + " file is missing!"));
    }
    json data_file = json::parse(file);
    file.close();
    return data_file;
}

void ConverterJSON::ShowEngine() const{
    ConsoleOutput().PrintLn("Start Engine!")
            ->PrintLn("Engine name: " + searchEngine.name)
            ->PrintLn("Engine version: " + to_string(searchEngine.version));
}

float ConverterJSON::ReadVersionEngine(json config) {
    if(!config.contains("version")) return -1;
    return std::stof(config["version"].get<string>());
}

ConverterJSON::~ConverterJSON() {
    ConsoleOutput().PrintLn("Stop Engine!");
}
