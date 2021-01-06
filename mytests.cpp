#include <gtest/gtest.h>
#include "class.h"


bool FindInFilesVector(vector<std::string> files, string word){
    for(auto i = files.begin(); i != files.end(); ++i){
        if(*i == word)
            return true;
    }
    return false;
}


TEST(StoryOneTests, Files_methodTest){
    vector<std::string> testFiles = StoryOne::Files();
    EXPECT_TRUE(FindInFilesVector(testFiles,"class.h"));
    EXPECT_TRUE(FindInFilesVector(testFiles,"main.cpp"));
}
int main(int argc, char* argv[]){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
