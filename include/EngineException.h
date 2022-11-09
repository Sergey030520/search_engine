//
// Created by sergei on 25.10.22.
//

#ifndef SEARCH_ENGINE_ENGINEEXCEPTION_H
#define SEARCH_ENGINE_ENGINEEXCEPTION_H

#include <iostream>
#include <utility>
using namespace std;

class EngineException : public exception{
private:
    string text_error;
public:
    explicit EngineException(string  in_text_error) : text_error(std::move(in_text_error)){}
    virtual const char* what(){
        return text_error.c_str();
    }

};


#endif //SEARCH_ENGINE_ENGINEEXCEPTION_H
