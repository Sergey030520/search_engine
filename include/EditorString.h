//
// Created by Malip on 29.10.2022.
//

#ifndef SEARCH_ENGINE_EDITORSTRING_H
#define SEARCH_ENGINE_EDITORSTRING_H

#include <iostream>
#include <vector>

using namespace std;

class EditorString {
public:
    EditorString() = default;
    /**
* Метод делит строку на слова
* @param text текст
* @return возвращает массив слов
*/
    static vector<string> SplitText(string& text);
    /**
* Статический метод удаляющий символы не относящиеся к словам
* @param text текст
* @return возвращает текст без символов не относящихся к словам
*/
    static string RemoveCharacters(string& text);
};


#endif //SEARCH_ENGINE_EDITORSTRING_H
