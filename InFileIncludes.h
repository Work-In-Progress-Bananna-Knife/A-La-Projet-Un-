#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
///
///globalne zmienne wykorzystywane do sprawdzania czy sa polaczenia miedzy plikami 
///
bool IsAny=0;
ofstream Data("Data.txt");

void Contains(string Line,vector<string> Ours);
void Connections(string FileName,vector <string> NotSystem);

void Connections(string FileName,vector <string> NotSystem){
ifstream File(FileName);

cout<<FileName<<endl;
Data<<FileName<<"-\n";
IsAny=0;
while(!File.eof()){
    string Line;
    getline(File,Line);
    Contains(Line,NotSystem);
}
if(!IsAny){
    cout<<"None"<<endl;
}
 
}

void Contains(string Line,vector<string> Ours){
    string LookFor="#include";
    size_t Where=Line.find(LookFor);
    if(Line.find(LookFor)!=string::npos){
        Where+=LookFor.size();
        string Contain = Line.substr(Where);
        for(int i=0;i<Contain.size();i++){
            if(Contain[i]==' ' || Contain[i]==34){
                Contain.erase(i,1);
                i--;
            }
        }
        for(int i =0;i<Ours.size();i++){
            if(Ours[i]==Contain){
                Data<<"\t"<<Contain<<"\n";
                cout<<"\t"<<Contain<<endl;
                IsAny=1;
                break;
            }
        }
        
    }
    
}

void Connections(string FileName,vector <string> NotSystem){
ifstream File(FileName);
cout<<FileName<<endl;
IsAny=0;
while(!File.eof()){
    string Line;
    getline(File,Line);
    Contains(Line,NotSystem);
}
if(!IsAny){
    cout<<"None"<<endl;
}
 
}

