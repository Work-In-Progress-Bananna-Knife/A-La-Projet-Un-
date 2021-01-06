#include <gtest/gtest.h>
#include "class.h"


bool FindInFilesVector(vector<std::string> files, string word){
    for(auto i = files.begin(); i != files.end(); ++i){
        if(*i == word)
            return true;
    }
    return false;
}


TEST(StoryOneTests, Files_test){
    vector<std::string> testFiles = StoryOne::Files();
    EXPECT_TRUE(FindInFilesVector(testFiles,"class.h"));
    EXPECT_TRUE(FindInFilesVector(testFiles,"main.cpp"));
}

TEST(StoryTwoTests, GetWordFromX_test){

    EXPECT_EQ(StoryTwo::GetWordFromX("std::string ",4),"string");
    EXPECT_EQ(StoryTwo::GetWordFromX("std::string()",4),"string");
    EXPECT_EQ(StoryTwo::GetWordFromX("ios::()",4),"");
    EXPECT_EQ(StoryTwo::GetWordFromX("::",2),"");
    EXPECT_EQ(StoryTwo::GetWordFromX("",0),"");
    EXPECT_EQ(StoryTwo::GetWordFromX("",-1),"");
    EXPECT_EQ(StoryTwo::GetWordFromX("",1),"");
}

TEST(StoryTwoTests, ReverseGetWordFromX_test){

    EXPECT_EQ(StoryTwo::ReverseGetWordFromX("std::string ",3),"std");
    EXPECT_EQ(StoryTwo::ReverseGetWordFromX("::std::string",5),"std");
    EXPECT_EQ(StoryTwo::ReverseGetWordFromX("s ios::dw",5),"ios");
    EXPECT_EQ(StoryTwo::ReverseGetWordFromX("::",1),"");
    EXPECT_EQ(StoryTwo::ReverseGetWordFromX("",0),"");
    EXPECT_EQ(StoryTwo::ReverseGetWordFromX("",-1),"");
    EXPECT_EQ(StoryTwo::ReverseGetWordFromX("",1),"");
}

TEST(StoryTwoTests, BracesSkip_test){

    string a = "void function(function2(fun1(),fun2(),arg),argument, function4())";
    EXPECT_EQ(StoryTwo::BracesSkip(a,13),a.size()-1);
    a = "()()()(11((()))))))))))))))";
    EXPECT_EQ(StoryTwo::BracesSkip(a,6),15);
    EXPECT_EQ(StoryTwo::BracesSkip(a,0),1);
}


TEST(StoryTwoTests, CheckAdd_test){

    map<std::string,map<std::string,int>> testMap;
    map<std::string,map<std::string, int> >::iterator itr;
    for(int i=0;i<100;i++){
        for(int j=0;j<100-i;j++){
            map<std::string, int> a;
            string b = "";
            b+=(char)j;
            a.insert({b,j});
            b=(char)i;
            testMap.insert({b,a});
        }
    }
    int i=0;
    for(itr = testMap.begin(); itr != testMap.end(); ++itr){
        string b = "";
        b+=(char)i;
        EXPECT_EQ(itr->first,b);
        int j=0;
        map<std::string,int>::iterator itr2;
        for(itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2){
            b=(char)j;
            EXPECT_EQ(itr2->first,b);
            j++;
        }
        i++;
    }
}

// TEST(StoryTwoTests, FindFunctionCallsInDefinitions_test){

// }


int main(int argc, char* argv[]){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
