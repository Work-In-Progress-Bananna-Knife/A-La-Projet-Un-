#pragma once
#include "header.h"     


bool IsAny=0;
ofstream Data("Data.txt");

#pragma region Node

void Add(stringNode * & H, std::string x){
    stringNode *p = new stringNode;
    p->val=x;
    p->next=H;
    H=p;
}


void Show(stringNode * H){
    cout<<"H->";
    stringNode *p=H;
    while(p!=NULL){
        cout<<p->val<<"->";
        p=p->next;
    }
    cout<<"NULL"<<endl;
}


string GetX(stringNode * & H, int x){

    int a=0;
    stringNode *p = H;
    while(p!=NULL){
        if(a == x){
            return p->val;
        }
            p = p->next;
            a++;
    }
    return "ERROR";
}


bool FindCharInString(string a, char b){

    for(int i = 0;i<a.size();i++){
        if(a[i]==b){
            return true;
        }
    }
    return false;
}
#pragma endregion


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


void IsSourceFile(stringNode * H, vector<string>  NotSystem){
    stringNode *p=H;
    while(p!=NULL){

        if((p->val[p->val.size()-1]=='h' && p->val[p->val.size()-2]=='.')||(p->val[p->val.size()-1]=='p'&&p->val[p->val.size()-2]=='p'&&p->val[p->val.size()-3]=='c'&&p->val[p->val.size()-4]=='.'))
        Connections(p->val,NotSystem);
        p=p->next;
    }
}


void GetFunNode(stringNode * & H){
    ifstream File("header.h");
    string word;
    string funName;
    while(!File.eof()){
        funName = "";
        File>>word;
        for(int i=0;i<word.size();i++){
            if(word[i]=='('){
                for(int j=0;j<i;j++){
                    funName+=word[j];
                }
                Add(H, funName);
                break;
            }
        }

    }

}


int CheckIfInNode(string word, stringNode * H){
    
    string fun ="";
    int a=0;
    int ret=-1;
    stringNode *p=H;
    while(p!=NULL){
        if((word.find(p->val)) != string::npos){
            
            if(p->val.size()>fun.size()){
                fun = p->val;
                ret = a;
            }
        }
        p=p->next;
        a++;
    }

    return ret;
}


void FunConnections(string FileName, stringNode * & functions){
    ifstream File(FileName);
    ofstream outFile("functions.txt");
    cout<<FileName<<endl;
    int a; //{
    int b; //}
    string word;
    string wordguard;
    while (!File.eof()){
        a=0;
        b=0;
        File>>word;
        int where = CheckIfInNode(word, functions);
        if(where>-1){
            
            wordguard = GetX(functions, where);
            std::cout<<wordguard<<endl;
            outFile<<wordguard<<"\n";

            while((a!=b)||(a == 0)){
                File>>word;
                where = CheckIfInNode(word, functions);
                if(where>-1){
                
                    cout<<" - "<<GetX(functions, where)<<endl;
                    outFile<<"\t"<<GetX(functions, where)<<"\n";
                    
                }
                if(FindCharInString(word,'{')){
                    a++;
                }
                if(FindCharInString(word,'}')){
                    b++;
                }

            }
        }
    }

}





