//
// Created by Malip on 21.04.2022.
//

#ifndef SEARCH_ENGINE_SEARCHSERVER_H
#define SEARCH_ENGINE_SEARCHSERVER_H

#include <vector>
#include <set>
#include "InvertedIndex.h"

struct RelativeIndex{
    size_t doc_id;
    float rank;
    RelativeIndex(size_t in_doc_id, float in_rank): doc_id(in_doc_id), rank(in_rank){}
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};
class SearchServer {
public:
/**
* @param idx в конструктор класса передаётся ссылка на класс
InvertedIndex,
* чтобы SearchServer мог узнать частоту слов встречаемых в
запросе
*/
    SearchServer(InvertedIndex& idx);
/**
* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла
requests.json
* @return возвращает отсортированный список релевантных ответов для
заданных запросов
*/
    std::vector<std::vector<RelativeIndex>*> Search(const
                                                   std::vector<std::string>& queries_input);

private:
    InvertedIndex& _index;

    /**
* Метод обработки поискового запроса
* @param request поисковой запрос взятые из файла
requests.json
 @param answer ссылка на динамический массив вычисленных относительных релевантности
*/
    void SearchRequest(string& request, vector<RelativeIndex>* answer);
    /**
* Метод сортировки слов поискового запроса
* @param words_request ссылка на массив слов запроса
*/
public: static void SortWordsRequest(vector<pair<string, size_t>>* words_request);

private:
/**
* Метод сортировки документов по убыванию релевантности
* @param unsorted_array ссылка на не отсортированный массив
*/
    void SortArrayRelativeIndex(vector<RelativeIndex>* unsorted_array);
/**
* Метод поиска совпадающих файлов для слова запроса
* @param word слово из поискового запроса
 * @param current_files файлы которые указывают и совпали с предыдущими словами запроса
* @return возвращает список файлов которые совпали с предыдущими словами
*/
    set<size_t> FindMatchFilesForWord(string& word, set<size_t>& current_files);
    /**
* Метод поиска совпадающих файлов для слов запроса
* @param freq_dict_request слова из поискового запроса
* @return возвращает список файлов которые совпали со всеми словами запроса
*/
    set<size_t> FindAllMatchFiles(vector<pair<string, size_t>>& freq_dict_request);
/**
* Метод вычисления абсолютной релевантности для всех файлов
* @param request слова из поискового запроса
 * @param files файлы которые указывают на слова запроса
* @return возвращает массив вычисленной абсолютной релевантности для каждого документа
*/
    vector<RelativeIndex> CalculateTotalRelevanceFiles(vector<pair<string, size_t>>& request,
                                                       set<size_t>& files);
    /**
* Метод вычисления абсолютной релевантности для файла
* @param request слова из поискового запроса
 * @param doc_id id документа для которого необходимо рассчитать абсолютною релевантность
* @return возвращает абсолютную релевантность для заданного файла
*/
    float CalculateTotalRelevanceFile(vector<pair<string, size_t>> &request, size_t& doc_id);
/**
* Метод вычисления относительной релевантности для всех файлов
* @param relevance_docs массив с абсолютной релевантностью для каждого документа
* @return возвращает массив вычисленной относительной релевантности для каждого документа
*/
    vector<RelativeIndex> CalculateRelativeRelevance(vector<RelativeIndex> relevance_docs);
};

#endif //SEARCH_ENGINE_SEARCHSERVER_H
