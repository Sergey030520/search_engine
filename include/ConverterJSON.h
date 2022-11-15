//
// Created by Malip on 15.04.2022.
//

#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H

#include <iostream>
#include <nlohmann/json.hpp>
#include <utility>

using namespace std;
namespace fs = filesystem;

typedef nlohmann::json json;

enum status_read_document{
    CONTINUE_READ = 0,
    STOP_READ = 1
};
enum limitations{
    MAX_WORDS_FILE = 1000,
    MAX_CHARS_WORD = 100,
    MAX_REQUESTS = 1000,
    MAX_WORDS_REQUEST = 10,
    MIN_WORDS_REQUEST = 1,
    MAX_RESPONSES = 5
};

/**
* Класс для работы с JSON-файлами
*/

struct SearchEngine{
    string name;
    float version;
    SearchEngine(string new_name, float new_version) : name(std::move(new_name)), version(new_version){}
};

class ConverterJSON {
private:
    SearchEngine searchEngine = SearchEngine("Search engine", 0.1f);

#if defined(_WIN32) || defined(_WIN64)
    const fs::path path_to_conf_files = GetPathToRootDirProject()
            .concat(R"(\configuration_files\)"); //путь до папки, где хранятся конфигурационные файлы
#elif defined(__linux__)
    const fs::path path_to_conf_files = GetPathToRootDirProject()
            .concat(R"(/configuration_files/)"); //путь до папки, где хранятся конфигурационные файлы
#endif
    json config_file; //json объект конфигурационного файла сервера

    /**
* Метод возвращает текст документа
* @param path_to_doc путь до файла
* @return текст из файла
*/
    string GetTextDocument(const string& path_to_doc);
    /**
* Метод считывает текст из потока вывода текста из файла
* @param stream_doc поток вывода текста из файла
* @return текст документа
*/
    string ReadStreamDataDoc(ifstream* stream_doc);
    /**
* Метод безопасно считывает строку с учётом ограничений на количество слов
     * запроса и количества символов в слове
* @param count_read_words количество считанных слов
  @param count_read_chars_word количество считанных символов
  @param line ссылка на строку
  @param text адрес на память, где храниться считанный текст
* @return возвращает boolean значение на основе которого принимается решение
* о продолжении считывания слов из запроса
*/
    static bool SafeReadString(int& count_read_words, int& count_read_chars_word,
                        const string& line, string& text) ;
    /**
* Метод проверяет количества слов в запросе
* @param request текст запроса
* @return возвращает boolean значение на основе которого принимается решение
*   о продолжении считывания слов из запроса
*/
    bool CheckCountWordsInRequest(const string& request);
    /**
* Метод загрузки json файла
* @param path_to_file путь до файла
* @return возвращает json объект с загруженными данными из файла
*/
    json LoadJsonFile(const fs::path& path_to_file);
    /**
* Метод выводит информацию о поисковом движке
*/
    void ShowEngine() const;
    /**
* Метод создает и возвращает путь до корневой папки проекта
* @return возвращает путь до корневой папки проекта
*/
    static fs::path GetPathToRootDirProject();

public:
    ConverterJSON();

/**
* Метод получения содержимого файлов
* @return Возвращает список с содержимым файлов перечисленных
* в config.json
*/
    std::vector<std::string> GetTextDocuments();
/**
* Метод считывает поле max_responses для определения предельного
* количества ответов на один запрос
* @return
*/
    int GetResponsesLimit();
/**
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json
*/
    std::vector<std::string> GetRequests();
/**
* Положить в файл answers.json результаты поисковых запросов
*/
    void PutAnswers(std::vector<std::vector<std::pair<size_t, float>>> answers);
    /**
* Метод получения версии из файла config.json
* @param config объект с конфигурационными данными поискового сервера
* @return возвращает версию из файла config.json
*/
    float ReadVersionEngine(json config);

    ~ConverterJSON();

};

#endif //SEARCH_ENGINE_CONVERTERJSON_H
