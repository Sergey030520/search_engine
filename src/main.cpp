#include <iostream>
#include "SearchServer.h"
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "gtest/gtest.h"


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    /*try {
        ConverterJSON converterJson;
        InvertedIndex invertedIndex;
        invertedIndex.UpdateDocumentBase(converterJson.GetTextDocuments());
        SearchServer server(invertedIndex);
        auto res = server.Search(converterJson.GetRequests());
        vector<vector<pair<size_t , float>>> reqRes;
        int id = 0;
        for(auto vec : res){
            reqRes.emplace_back(vector<pair<size_t, float>>());
            for(auto ind : *vec){
                reqRes.at(id).emplace_back(make_pair(ind.doc_id, ind.rank));
            }
            ++id;
        }
        converterJson.PutAnswers(reqRes);
        for(auto vec : res){
            delete vec;
        }
    }catch (EngineException* except){
        ConsoleOutput().PrintLn(except->what());
    }*/
}
