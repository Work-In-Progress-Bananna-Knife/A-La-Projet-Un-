#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void Connections(string FileName){
ifstream File(FileName);
while(!File.eof()){
    string Line;
    getline(File,Line);
    Contains(Line);
}
 
}

void Contains(string Line){
    string LookFor="#include";
    size_t Where=Line.find(LookFor);
    if(Line.find(LookFor)!=string::npos){
        Where+=LookFor.size();
        string Contain = Line.substr(Where);
        cout<<Contain<<endl;
    }

}