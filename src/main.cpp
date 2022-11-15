#include <iostream>
#include "SearchServer.h"
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "gtest/gtest.h"
#include "EngineException.h"
#include "ConsoleOutput.h"


int main(int argc, char* argv[]) {
    /*::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();*/
    try {
        ConverterJSON converterJson;
        InvertedIndex invertedIndex;
        invertedIndex.UpdateDocumentBase(converterJson.GetTextDocuments());
        SearchServer server(invertedIndex);
        auto res_requests = server.Search(converterJson.GetRequests());
        converterJson.PutAnswers(res_requests);

    }catch (EngineException* except){
        ConsoleOutput().PrintLn(except->what());
    }
}
