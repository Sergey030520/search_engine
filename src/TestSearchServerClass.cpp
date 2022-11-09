//
// Created by Malip on 09.11.2022.
//

#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include "SearchServer.h"

vector<vector<RelativeIndex>> Convert(vector<vector<RelativeIndex>*> rel_index_arr){
    vector<vector<RelativeIndex>> result;
    for (auto array : rel_index_arr) {
        result.emplace_back(vector<RelativeIndex>());
        for(auto value : *array){
            result[result.size()-1].emplace_back(value);
        }
    }
    return result;
}


TEST(TestCaseSearchServer, TestSimple) {
    const vector<string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const vector<string> request = {"milk water", "sugar"};
    const std::vector<vector<RelativeIndex>> expected = {
            {
                    {2, 1},
                    {0, 0.7},
                    {1, 0.3}
            },
            {
            }
    };
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    std::vector<vector<RelativeIndex>> result = Convert(srv.Search(request));
    ASSERT_EQ(result, expected);
}
TEST(TestCaseSearchServer, TestTop5) {
    const vector<string> docs = {
            "london is the capital of great britain",/*0*/
            "paris is the capital of france",/*1*/
            "berlin is the capital of germany",/*2*/
            "rome is the capital of italy",
            "madrid is the capital of spain",
            "Moscow is the capital of portugal",
            "bern is the capital of switzerland",
            "moscow is the capital of russia",/*7*/
            "kiev is the capital of ukraine",
            "minsk is the capital of belarus",
            "astana is the capital of kazakhstan",
            "beijing is the capital of china",
            "tokyo is the capital of japan",
            "bangkok is the capital of thailand",
            "welcome to moscow the capital of russia the third rome",/*14*/
            "amsterdam is the capital of netherlands",
            "helsinki is the capital of finland",
            "oslo is the capital of norway",
            "stockholm is the capital of sweden",
            "riga is the capital of latvia",
            "tallinn is the capital of estonia",
            "warsaw is the capital of poland",
    };
    const vector<string> request = {" the capital of is moscow "};
    const std::vector<vector<RelativeIndex>> expected = {
            {
                    {7, 1}
            }
    };
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    SearchServer srv(idx);
    vector<vector<RelativeIndex>> result = Convert(srv.Search(request));
    ASSERT_EQ(result, expected);
}
