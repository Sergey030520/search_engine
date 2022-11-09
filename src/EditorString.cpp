//
// Created by Malip on 29.10.2022.
//

#include "EditorString.h"
#include <regex>
#include <sstream>

vector<string> EditorString::SplitText(string &text) {
    stringstream streamText(text);
    vector<string> words;
    string word;
    for (streamText >> word; !streamText.eof(); streamText >> word) {
        words.emplace_back(word);
    }
    words.emplace_back(word);
    return words;
}

string EditorString::RemoveCharacters(string &text) {
    std::regex const filter("[^0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_-]");
    return regex_replace(text, filter, " ");
}
