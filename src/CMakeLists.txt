cmake_minimum_required(VERSION 3.20)


add_executable(${PROJECT_NAME} main.cpp ${MY_INCLUDE_DIR}/ConverterJSON.h ConverterJSON.cpp
        InvertedIndex.cpp ${MY_INCLUDE_DIR}/InvertedIndex.h
        SearchServer.cpp ${MY_INCLUDE_DIR}/SearchServer.h
        ${MY_INCLUDE_DIR}/EngineException.h ConsoleOutput.cpp ${MY_INCLUDE_DIR}/ConsoleOutput.h
        GeneratorJsonAnswers.cpp ${MY_INCLUDE_DIR}/GeneratorJsonAnswers.h
        EditorString.cpp ${MY_INCLUDE_DIR}/EditorString.h
        TestInvertedIndexClass.cpp TestSearchServerClass.cpp)


target_include_directories(${PROJECT_NAME} PUBLIC ${MY_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
