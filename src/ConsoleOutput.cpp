//
// Created by Malip on 25.10.2022.
//

#include "ConsoleOutput.h"

ConsoleOutput::ConsoleOutput() {
#if defined(_WIN32) || defined(_WIN64)
    color_base = WHITE;
    color_system = RED;
#elif defined(__linux__)
    color_base = WHITE_FG;
    color_system = RED_FG;
#endif
}

ConsoleOutput* ConsoleOutput::PrintLn(const std::string& text) {
#if defined(__linux__)
    PRINT_SYSTEM_LINUX(text, color_system);
#elif defined(_WIN32) || defined(_WIN64)
    PRINT_SYSTEM_WIN(text, color_base, color_system);
#endif
    return this;
}

void ConsoleOutput::PrintLn(const std::string& text, colors new_color) {
#if defined(__linux__)
    PRINT_SYSTEM_LINUX(text, new_color);
#elif defined(_WIN32) || defined(_WIN64)
    PRINT_SYSTEM_WIN(text, color_base, new_color);
#endif
}

void ConsoleOutput::SetColorBase(colors new_color) {
    color_base = new_color;
}

int ConsoleOutput::GetColorBase() {
    return color_base;
}