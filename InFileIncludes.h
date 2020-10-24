#pragma once
#include "header.h"


bool IsAny=0;
ofstream Data("Data.txt");

#pragma region Contains()
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
#pragma endregion

#pragma region Connections()
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
#pragma endregion

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

#pragma region GetX()
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

#pragma region GetFunNode()

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

#pragma endregion

#pragma region CheckIfInNode()
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
#pragma endregion

#pragma region FindCharInString()
bool FindCharInString(string a, char b){

    for(int i = 0;i<a.size();i++){
        if(a[i]==b){
            return true;
        }
    }
    return false;
}
#pragma endregion

#pragma region FunConnections()

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
                    if(wordguard != GetX(functions, where)){
                        cout<<" - "<<GetX(functions, where)<<endl;
                        outFile<<"\t"<<GetX(functions, where)<<"\n";
                    }
                    
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


#pragma endregion



