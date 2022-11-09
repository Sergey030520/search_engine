//
// Created by Malip on 21.04.2022.
//

#include "SearchServer.h"
#include<algorithm>

SearchServer::SearchServer(InvertedIndex &idx):  _index(idx) {}

std::vector<std::vector<RelativeIndex>*> SearchServer::Search(const vector<std::string> &queries_input) {
    vector<vector<RelativeIndex>*> answers;
    vector<thread> thrd_search_request;
    for (const auto& request: queries_input) {
        thrd_search_request.emplace_back(&SearchServer::SearchRequest, this, request,
                                         answers.emplace_back(new vector<RelativeIndex>()));
    }
    for(auto & thr : thrd_search_request) thr.join();
    return answers;
}

void SearchServer::SearchRequest(string &request, vector<RelativeIndex>* answer) {
    InvertedIndex invertedIndex;
    invertedIndex.UpdateDocumentBase(vector<string>({request}));

    auto freq_dict_request = invertedIndex.CalculateNumberOccurrenceWords();

    SortWordsRequest(&freq_dict_request);

    auto matched_files = FindAllMatchFiles(freq_dict_request);

    if(!matched_files.empty()) {
        answer->operator=(
                CalculateRelativeRelevance(CalculateTotalRelevanceFiles(freq_dict_request, matched_files)));
        SortArrayRelativeIndex(answer);
    }
}

void SearchServer::SortWordsRequest(vector<pair<string, size_t>>* words_request) {
    std::sort(words_request->begin(), words_request->end(),
              [](const pair<string, size_t>& left_val,const pair<string, size_t>& right_val){
        return left_val.second < right_val.second;
    });
}

set<size_t> SearchServer::FindAllMatchFiles(vector<pair<string, size_t>>& freq_dict_request){
    auto files_for_word = _index.GetWordCount(freq_dict_request.at(0).first);
    set<size_t> files;

    for_each(begin(files_for_word), end(files_for_word), [&files](Entry& entry){
        files.emplace(entry.doc_id);
    });

    for(int indWord = 1; indWord < freq_dict_request.size() && !files.empty(); ++indWord){
        files = FindMatchFilesForWord(freq_dict_request.at(indWord).first, files);
    }
    return files;
}

set<size_t> SearchServer::FindMatchFilesForWord(string &word, set<size_t> &current_files) {
    auto files_for_word =  _index.GetWordCount(word);
    set<size_t> matched_files;
    for(auto doc_id : current_files){
        for (auto fileDB : files_for_word) {
            if(fileDB.doc_id == doc_id){
                matched_files.emplace(doc_id);
                break;
            }
        }
    }
    return matched_files;
}

vector<RelativeIndex> SearchServer::CalculateTotalRelevanceFiles(vector<pair<string, size_t>> &request,
                                                                 set<size_t>& files) {
    vector<RelativeIndex> absolute_relevance;
    for(auto doc_id : files){
        auto relevance = CalculateTotalRelevanceFile(request, doc_id);
        absolute_relevance.emplace_back(RelativeIndex(doc_id, relevance));
    }
    return absolute_relevance;
}

float SearchServer::CalculateTotalRelevanceFile(vector<pair<string, size_t>> &request, size_t &doc_id) {
    float counter = 0;
    for (const auto& word : request) {
        auto entries = _index.GetWordCount(word.first);
        for (auto entry: entries) {
            if (doc_id == entry.doc_id) counter += (float) entry.count;
        }
    }
    return counter;
}

vector<RelativeIndex> SearchServer::CalculateRelativeRelevance(vector<RelativeIndex> relevance_docs) {
    auto max_relevance = max_element(begin(relevance_docs), end(relevance_docs),
                                     [](RelativeIndex& left_val, RelativeIndex& right_val){
        return left_val.rank < right_val.rank;
    })->rank;
    for(auto &file : relevance_docs){
        file.rank = file.rank / max_relevance;
    }
    return relevance_docs;
}

void SearchServer::SortArrayRelativeIndex(vector<RelativeIndex> *unsorted_array) {
    sort(unsorted_array->begin(), unsorted_array->end(),
         [](RelativeIndex& left_val, RelativeIndex& right_val){
        return left_val.rank > right_val.rank;
    });
}
