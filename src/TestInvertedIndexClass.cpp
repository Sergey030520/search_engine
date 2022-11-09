//
// Created by Malip on 09.11.2022.
//

#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include "InvertedIndex.h"
#include <algorithm>

using namespace std;

void TestInvertedIndexFunctionality(
        const vector<string>& docs,
        const vector<string>& requests,
        const std::vector<vector<Entry>>& expected
) {
    std::vector<std::vector<Entry>> result;
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    for (auto &request: requests) {
        std::vector<Entry> word_count = idx.GetWordCount(request);
        std::sort(word_count.begin(), word_count.end(), [](Entry& left_val, Entry& right_val){
            return left_val.doc_id < right_val.doc_id;
        });
        result.push_back(word_count);
    }
    for(auto res : result){
        cout << "{" << endl << "\t";
        for(auto answ : res){
            cout << "{" << answ.doc_id << " => " << answ.count << "}, ";
        }
        cout << endl << "}"<< endl;
    }
    ASSERT_EQ(result, expected);
}

TEST(TestCaseInvertedIndex, TestBasic) {
    const vector<string> docs = {
            "london is the capital of great britain",
            "big ben is the nickname for the Great bell of the striking clock"
    };

    const vector<string> requests = {"london", "the"};

    const vector<vector<Entry>> expected = {
            {
                    {0, 1}
            },
            {
                    {0, 1}, {1, 3}
            }
    };

    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestBasic2) {
    const vector<string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const vector<string> requests = {"milk", "water", "cappuccino"};
    const vector<vector<Entry>> expected = {
            {
                    {0, 4}, {1, 1}, {2, 5}
            },
            {
                    {0, 3}, {1, 2}, {2, 5}
            },
            {
                    {3, 1}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}
TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
    const vector<string> docs = {
            "a b c d e f g h i j k l",
            "statement"
    };
    const vector<string> requests = {"m", "statement"};
    const vector<vector<Entry>> expected = {
            {
            },
            {
                    {1, 1}
            }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}
