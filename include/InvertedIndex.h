//
// Created by Malip on 20.04.2022.
//

#ifndef SEARCH_ENGINE_INVERTEDINDEX_H
#define SEARCH_ENGINE_INVERTEDINDEX_H

#include <iostream>
#include <vector>
#include <map>
#include <mutex>
#include <shared_mutex>

using namespace std;

struct Entry {
    size_t doc_id, count;
    Entry(size_t in_doc_id, size_t in_count = 1) : doc_id(in_doc_id), count(in_count){}
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};
class InvertedIndex {
public:
    InvertedIndex() = default;
/**
* Обновить или заполнить базу документов, по которой будем совершать
* поиск
* @param texts_input содержимое документов
*/
    void UpdateDocumentBase(const std::vector<std::string>& input_docs);
/**
 * Метод определяет количество вхождений слова word в загруженной базе
документов
* @param word слово, частоту вхождений которого необходимо определить
* @return возвращает подготовленный список с частотой слов
*/
    std::vector<Entry> GetWordCount(const std::string& word);
/**
* Метод рассчитывает для каждого слова общее количество упоминаний во всех файлах
* @return возвращает динамический массив слов с общим числом повторений
*/
    vector<pair<string, size_t>> CalculateNumberOccurrenceWords();

private:
    std::vector<std::string> docs; // список содержимого документов
    std::map<std::string, std::vector<Entry>> freq_dictionary; // частотный словарь
    mutex mtx_words, //мьютекс на добавление слов в частотный словарь
        mtx_docs; //мьютекс на добавление или увеличение упоминания в файле слов
        /**
* Метод индексирует слова документа
* @param doc_id id документа
* @param text тест файла
*/
    void indexingDocument(size_t doc_id, string& text);
/**
* Метод добавляет или увеличивает количество упоминаний слова в для заданного документа
* @param doc_id id документа, для добавления или увеличения количества упоминаний слова для данного файла;
* @param entries ссылка на массив упоминаний в документах искомого слова
*/
    void FindEntryAndIncreaseVal(const size_t & doc_id, vector<Entry>* entries);


};

#endif //SEARCH_ENGINE_INVERTEDINDEX_H
