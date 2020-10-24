#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "header.h"

using namespace std;

bool IsAny=0;
ofstream Data("Data.txt");





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



#pragma region stringNode class
class stringNode{

    public:
    stringNode* next;
    std::string val;
};
#pragma endregion

#pragma region Add()
void Add(stringNode * & H, std::string x){
    stringNode *p = new stringNode;
    p->val=x;
    p->next=H;
    H=p;
}
#pragma endregion 

#pragma region Show()
void Show(stringNode * H){
    cout<<"H->";
    stringNode *p=H;
    while(p!=NULL){
        cout<<p->val<<"->";
        p=p->next;
    }
    cout<<"NULL"<<endl;
}

#pragma endregion


#pragma region IsSourceFile()
void IsSourceFile(stringNode * H, vector<string>  NotSystem){
    stringNode *p=H;
    while(p!=NULL){

        if((p->val[p->val.size()-1]=='h' && p->val[p->val.size()-2]=='.')||(p->val[p->val.size()-1]=='p'&&p->val[p->val.size()-2]=='p'&&p->val[p->val.size()-3]=='c'&&p->val[p->val.size()-4]=='.'))
        Connections(p->val,NotSystem);
        p=p->next;
    }
}
#pragma endregion
