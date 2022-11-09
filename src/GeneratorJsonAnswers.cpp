//
// Created by Malip on 29.10.2022.
//

#include "GeneratorJsonAnswers.h"
#include <string>

GeneratorJsonAnswers::GeneratorJsonAnswers(int in_responses_limit) : responses_limit(in_responses_limit){}

json GeneratorJsonAnswers::Generate(vector<vector<pair<size_t, float>>> *answers) {
    json file_answers, requests;
    for(auto numb_request = 0; numb_request < answers->size(); ++numb_request){
        requests["request" + GenerateId(numb_request)] = ConvertRelevance(
                ConvertArrayRelevance(&answers->at(numb_request)));
    }
    file_answers["answers"] = requests;
    return file_answers;
}

json GeneratorJsonAnswers::ConvertRelevance(const json& answer) {
    json relevance;
    relevance["result"] = !answer.empty();
    if(!answer.empty()){
        relevance["relevance"] = answer;
    }
    return relevance;
}

json GeneratorJsonAnswers::ConvertArrayRelevance(vector<pair<size_t, float>>* answer) const {
    json answer_json = json::array();
    for(auto numb_response = 0; numb_response < answer->size() && numb_response < responses_limit; ++numb_response){
        auto response = answer->at(numb_response);
        answer_json.emplace_back(json({make_pair("docid", response.first),
                                       make_pair("rank", response.second)}));
    }
    return answer_json;
}

string GeneratorJsonAnswers::GenerateId(int sequence_numb) {
    return (sequence_numb < 10 ? "00" + to_string(sequence_numb) : (sequence_numb < 100 ? "0" +
                to_string(sequence_numb) : to_string(sequence_numb)));
}





