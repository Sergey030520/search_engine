//
// Created by Malip on 25.10.2022.
//

#ifndef SEARCH_ENGINE_CONSOLEOUTPUT_H
#define SEARCH_ENGINE_CONSOLEOUTPUT_H

#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
namespace win {
#include <Windows.h>
    static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
}
#endif

#define PRINT_SYSTEM_WIN(text, color_base, color_system) \
    win::SetConsoleTextAttribute(win::handle, color_system); std::cout << (text) << std::endl; \
    win::SetConsoleTextAttribute(win::handle, color_base);
#define PRINT_SYSTEM_LINUX(text, color) cout << ("\x1B[" + (colors) +"m" + (text) + "\033[0m") << std::endl;


enum colors{
    WHITE = 15,
    RED = 12,
    GREEN = 10,
    BLUE = 11,
    WHITE_FG = 37,
    RED_FG = 31,
    GREEN_FG = 32,
    BLUE_FG = 34
};


class ConsoleOutput {
private:
    colors color_base;
    colors color_system;
public:
    ConsoleOutput();
    ConsoleOutput* PrintLn(const std::string& text);
    void PrintLn(const std::string& text, colors new_color);
    void SetColorBase(colors new_color);
    int GetColorBase();
};


#endif //SEARCH_ENGINE_CONSOLEOUTPUT_H
