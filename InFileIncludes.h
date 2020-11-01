#pragma once

#include "header.h"   
#include "stringNode.h"
//ContainDefinitions

bool IsAny=0;
ofstream Data("Data.gv");


void Contains(string Line,vector<string> Ours,string file){
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
                Data<<"\""<<file<<"\""<<"->"<<"\""<<Contain<<"\""<<" [label = \"1\"];\n";
                //cout<<"\t"<<Contain<<endl;
                IsAny=1;
                break;
            }
        }
        
    }
    
}


void Connections(string FileName,vector <string> NotSystem){
    ifstream File(FileName);
    //cout<<FileName<<endl;
    IsAny=0;
    while(!File.eof()){
        string Line;
        getline(File,Line);
        Contains(Line,NotSystem,FileName);
    }
    if(!IsAny){
        cout<<"None"<<endl;
    }
    
}


void IsSourceFile(stringNode * H, vector<string>  NotSystem){
    stringNode *p=H;
    Data<<"digraph weighted{\n";
    while(p!=NULL){

        if((p->val[p->val.size()-1]=='h' && p->val[p->val.size()-2]=='.')||(p->val[p->val.size()-1]=='p'&&p->val[p->val.size()-2]=='p'&&p->val[p->val.size()-3]=='c'&&p->val[p->val.size()-4]=='.'))
        Connections(p->val,NotSystem);
        p=p->next;
    }
    Data<<"}";
    WriteRunBashFile("GraphStoryOne");
}


void WriteRunBashFile(string name){
    Data.close();
    string run=name+".sh";
    string scriptname=run;
    ofstream script(run);
    string grr=run.substr(0,run.size()-2);
    grr=grr+"png";
    
    script<<"#/bin/bash\ndot -Tpng Data.gv -o "<<grr<<"\ndisplay "<<grr;

    //dolinuxa
    #if !(defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__))
        scriptname = "bash "+scriptname;
    #endif

    const char* c=scriptname.c_str();
    script.close();
    system(c);
    c=grr.c_str();
    system(c);
    }


void GetFunNode(stringNode * & H, string a){
    ifstream File(a);
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
        int where = CheckIfInNode(word, functions);
        if(where>-1){

            for(int i=0;i<tabsize;i++){
                tab[i]=0;
            }
            wordguard = GetX(functions, where);
            std::cout<<wordguard<<endl;
            outFile<<wordguard<<"\n";
            
            while((a!=b)||(a == 0)){
                File>>word;
                where = CheckIfInNode(word, functions);
                if(where>-1){
                
                    cout<<" - "<<GetX(functions, where)<<endl;
                    outFile<<"\t"<<GetX(functions, where)<<"\n";
                    tab[where]++;
                    
                }
                if(FindCharInString(word,'{')){
                    a++;
                }
                if(FindCharInString(word,'}')){
                    b++;
                }

            }
            for(int i=0;i<tabsize;i++){
                
                if(tab[i] != 0){
                    
                    Data<<"\""<<wordguard<<"\""<<" -> \""<<GetX(functions,i)<<"\""<<"(label =  \""<<tab[i]<<"\")\n";
                }
            }
        }
    }
}
void funckja(stringNode * & H, stringNode * & fun){
    Data.open("Data.gv");
    Data.clear();
    Data<<"digraph foo{\n";

    stringNode *p = H;
    stringNode *dec = NULL;
    stringNode *def = NULL;
    string word="";
    string wordHolder="";
    while(p != NULL){
        ifstream File(p->val);
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

    Data<<"}";
    WriteRunBashFile("GraphStoryTwo");
}



