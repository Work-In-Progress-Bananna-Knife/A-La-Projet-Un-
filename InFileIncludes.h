#pragma once
#include "header.h"   
#include "stringNode.h"
//ContainDefinitions

bool IsAny=0;

std::ofstream Data("Data.gv");
vector< stringNode* > vec;

void Contains(string Line,vector<string> Ours,string file){
    int a=0;
    string LookFor="#include";
    size_t dziee=Line.find(LookFor);
    if(Line.find(LookFor)!=string::npos){
        dziee+=LookFor.size();
        string Contain = Line.substr(dziee);
        for(int i=0;i<Contain.size();i++){
            if(Contain[i]==' ' || Contain[i]==34){
                Contain.erase(i,1);
                i--;
            }
        }
        for(int i =0;i<Ours.size();i++){
            
            if(Ours[i]==Contain){
                CheckAndAddVector(vec,file,Contain);
                //Data<<"\""<<file<<"\""<<"->"<<"\""<<Contain<<"\""<<" [label = \"1\"];\n";
                IsAny=1;
                break;
            }
        }  
    }
    
    
}


void Connections(string FileName,vector <string> NotSystem){
    std::ifstream File(FileName);
    IsAny=0;
    while(!File.std::ios::eof()){
        string Line;
        getline(File,Line);
        Contains(Line,NotSystem,FileName);
    }
}


void IsSourceFile(stringNode * H, vector<string>  NotSystem, bool isStory5){
    stringNode *p=H;
    if(!isStory5)
        Data<<"digraph weighted{\n";
    while(p!=NULL){
        if((p->val[p->val.size()-1]=='h' && p->val[p->val.size()-2]=='.')||(p->val[p->val.size()-1]=='p'&&p->val[p->val.size()-2]=='p'&&p->val[p->val.size()-3]=='c'&&p->val[p->val.size()-4]=='.'))
        Connections(p->val,NotSystem);
        p=p->next;
    }
     
    if(!isStory5){
        DrawGv(vec);
        Data<<"}";
        WriteRunBashFile("GraphStoryOne");
    }
    
}


void WriteRunBashFile(string name){
    Data.close();
    string run=name+".sh";
    string scriptname=run;
    std::ofstream script(run);
    string grr=run.substr(0,run.size()-2);
    grr=grr+"png";
    
    script<<"#/bin/bash\ndot -Tpng Data.gv -o "<<grr<<"\ndisplay "<<grr;

    //dolinuxa
    #if !(defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__))
        scriptname = "bash "+scriptname;
    #endif

    const char* c=scriptname.c_str();
    script.close();
    //tymczasowo(?) zakomentowane
    //system(c);
    //c=grr.c_str();
    //system(c);
    }


void GetFunNode(stringNode * & H, string a){
    std::ifstream File(a);
    string word;
    string funName;
    while( !File.eof() ){
        funName = "";
        File>>word;
        for(int i=0;i<word.size();i++){
            if(word[i]=='('){
                for(int j=0;j<i;j++){
                    funName+=word[j];
                }
                Add(H, funName);

                //story 5
                stringNode * a = NULL;
                Add(a,funName);
                vec.push_back(a);
                //

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
    
    std::ifstream File(FileName);
    int a; // ilość: { 
    int b; //ilość: }
    int tabsize=0;
    std::string word;
    std::string wordguard;
    stringNode * p = NULL;

    p = functions;
    while(p != NULL){

        tabsize++;    
        p = p->next;
    }
    int tab[tabsize];

    while(!File.eof()){
        a=0;
        b=0;
        File>>word;
        int dzie = CheckIfInNode(word, functions);
        if(dzie>-1){
            for(int i=0;i<tabsize;i++){
                tab[i]=0;
            }
            wordguard = GetX(functions, dzie);
            std::cout<<wordguard<<endl;
            
            while((a!=b)||(a == 0)){
                File>>word;
                dzie = CheckIfInNode(word, functions);
                if(dzie>-1){
                    std::cout<<" - "<<GetX(functions, dzie)<<endl;
                    tab[dzie]++;  
                }
                if(FindCharInString(word,'{'))
                    a++;
                if(FindCharInString(word,'}'))
                    b++;
            }
            for(int i=0;i<tabsize;i++){
                
                if(tab[i] != 0)
                    //Data<<"\""<<wordguard<<"\""<<" -> \""<<GetX(functions,i)<<"\""<<"[label =  \""<<tab[i]<<"\"]\n";
                    CheckAndAddVector(vec,wordguard,GetX(functions,i));
            }
        }
    }
}


void StoryTwo(stringNode *  H, stringNode * & fun, bool isStory5){
    if(!isStory5){
        Data.open("Data.gv");
        Data.clear();
        Data<<"digraph foo{\n";
        Data<<"label =\"Relacje między funcjami\"";
    }
    stringNode *p = H;
    stringNode *dec = NULL;
    stringNode *def = NULL;
    string word="";
    string wordHolder="";
    while(p != NULL){
        std::ifstream File(p->val);
        while(!File.eof()){
            File>>word;
            if(word == "//ContainDeclarations"){
                Add(dec,p->val);
                break;
            }
            else if( word == "//ContainDefinitions"){
                Add(def,p->val);
                break;
            }
        }
        p=p->next;
    }

    while (dec != NULL)
    {
        GetFunNode(fun, dec->val);
        dec = dec->next;
    }
     
    while (def != NULL)
    {
        FunConnections(def->val,fun);
        def = def->next;
    }

    if(!isStory5){
        DrawGv(vec); 
        Data<<"}";
        WriteRunBashFile("GraphStoryTwo");
    }
}


// przyjmuje jako argument vector list
//na początku każdej listy musi znajdować się nazwa tego, co łączy się z resztą obiektów na liście
void DrawGv(vector<stringNode*> v){
    
        for (auto i = v.begin(); i != v.end(); ++i) {
                stringNode * p=(*i);
                p=p->next;
            while(p){
                Data<<"\""<<(*i)->val<<"\""<<"->"<<"\""<<p->val<<"\""<<" [label = \""<<p->val1<<"\"];\n";
                p=p->next;
            }
        }
}


void CheckAndAddVector(vector<stringNode*> & v, string head, string connection){
    bool exist = false;
    for (auto i = v.begin(); i != v.end(); ++i) {
        stringNode * p = (*i);
        //pomijamy pierwszy objekt, bo łączone objekty są od następnego
        //jeżeli nie null
        if(*i){
            p=p->next;
            if((*i)->val == head){
                while(p){
                    if(p->val == connection){
                        exist = true;
                        p->val1++;
                    }
                    p=p->next;
                }
                if(!exist){
                    AddSecond((*i),connection);
                    exist = true;
                }
            }
        }
    }
    if(!exist){
        stringNode * a = NULL;
        Add(a,head);
        v.push_back(a);
        AddSecond(*(v.rbegin()),connection);
    }
}



void storyFive(){

    if(0==0){
        Data.open("Data.gv");
        Data.clear();
        Data<<"digraph foo{\n";
        Data<<"label =\"Relacje między wszystkim\""; 
        DrawGv(vec);  
        Data<<"}";
        WriteRunBashFile("GraphStoryFive");
    }
    
}