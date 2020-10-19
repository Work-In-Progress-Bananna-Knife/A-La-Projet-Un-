#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool IsAny=0;
void Contains(string Line);
void Connections(string FileName);  

void Connections(string FileName){
ifstream File(FileName);
cout<<FileName<<endl;
IsAny=0;
while(!File.eof()){
    string Line;
    getline(File,Line);
    Contains(Line);
}
if(!IsAny){
    cout<<"None"<<endl;
}
 
}

void Contains(string Line){
    string LookFor="#include";
    size_t Where=Line.find(LookFor);
    if(Line.find(LookFor)!=string::npos){
        Where+=LookFor.size();
        string Contain = Line.substr(Where);
        cout<<Contain<<endl;
        IsAny=1;
    }
    
}