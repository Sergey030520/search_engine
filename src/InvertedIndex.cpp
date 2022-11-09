//
// Created by Malip on 26.10.2022.
//
#include "InvertedIndex.h"
#include <thread>
#include <numeric>
#include "EditorString.h"

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& input_docs) {
    vector<thread> thrd_indexing_docs;
    for (const auto& text : input_docs) {
        docs.emplace_back(text);
        thrd_indexing_docs.emplace_back(&InvertedIndex::indexingDocument, this, docs.size()-1, text);
    }
    for (auto & thrd : thrd_indexing_docs) {
        thrd.join();
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const string &word) {
    return (freq_dictionary.find(word) != freq_dictionary.end() ? freq_dictionary.at(word) : vector<Entry>());
}

void InvertedIndex::indexingDocument(size_t doc_id, string& text) {
    auto cleanText = EditorString::RemoveCharacters(text);
    vector<string> words = EditorString::SplitText(cleanText);

    for(const auto& word : words){
        unique_lock uniqueLock(mtx_words);
        auto foundWord = std::find_if(begin(freq_dictionary),end(freq_dictionary),
                                      [word](const pair<string, vector<Entry>>& value){
            return value.first == word;
        });
        if(foundWord == freq_dictionary.end()){
            freq_dictionary.emplace(make_pair(word, vector<Entry>({Entry(doc_id)})));
            uniqueLock.unlock();
        }
        else{
            uniqueLock.unlock();
            FindEntryAndIncreaseVal(doc_id, &freq_dictionary.at(word));
        }
    }
}

void InvertedIndex::FindEntryAndIncreaseVal(const size_t & doc_id, vector<Entry> *entries) {
    unique_lock uniqueLock(mtx_docs);
    auto foundEntry = std::find_if(entries->begin(), entries->end(), [&doc_id](Entry entry){
        return doc_id == entry.doc_id;
    });
    if(foundEntry != entries->end()){
        foundEntry->count++;
    }else{
        entries->emplace_back(Entry(doc_id));
    }
}

vector<pair<string, size_t>> InvertedIndex::CalculateNumberOccurrenceWords() {
    vector<pair<string, size_t>> words;
    for(const auto& word : freq_dictionary){
        size_t total_occurrence = accumulate(begin(word.second), end(word.second), 0, [](int current_val,
                                                                                      const Entry& entry){
            return current_val + entry.count;
        });
        words.emplace_back(make_pair(word.first, total_occurrence));
    }
    return words;
}