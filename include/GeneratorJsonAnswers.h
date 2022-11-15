//
// Created by Malip on 29.10.2022.
//

#ifndef SEARCH_ENGINE_GENERATORJSONANSWERS_H
#define SEARCH_ENGINE_GENERATORJSONANSWERS_H

#include <iostream>
#include <nlohmann/json.hpp>
#include "SearchServer.h"

using namespace std;

typedef nlohmann::json json;

class GeneratorJsonAnswers {
    int responses_limit;
public:
    explicit GeneratorJsonAnswers(int in_responses_limit = 5);

    /**
* Метод создающий json документ на основе полученных ответов на запросы
* @param answers массив ответов на запросы
* @return возвращает json документ созданный на основе ответов на запросы
*/
    json Generate(vector<vector<RelativeIndex>*>& answers);
    /**
* Метод создающий json документ массива релевантности файлов запроса
* @param answer массив документов с их относительной релевантностью
* @return возвращает json документ
*/
    json ConvertArrayRelevance(vector<RelativeIndex>* answer) const;
    /**
* Метод создающий json документ релевантности
* @param answer json документ хранящий массив релевантности документов запроса
* @return возвращает json документ
*/
    json ConvertRelevance(const json& answer);
    /**
* Метод генерирующий id
* @param sequence_numb порядковый номер документа
* @return возвращает созданный строковый id
*/
    static string GenerateId(int sequence_numb);


};


#endif //SEARCH_ENGINE_GENERATORJSONANSWERS_H
