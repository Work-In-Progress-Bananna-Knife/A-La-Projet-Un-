#include "moduleFinderHeader.h"
//ContainDefinitions

void funkcja(stringNode * H){

    stringNode * nsNode = NULL;

    stringNode * p = H;
    while(p!=NULL){
        if((p->val[p->val.size()-1]=='h' && p->val[p->val.size()-2]=='.')||(p->val[p->val.size()-1]=='p'&&p->val[p->val.size()-2]=='p'&&p->val[p->val.size()-3]=='c'&&p->val[p->val.size()-4]=='.')){ 
            findProbableModules(p->val, nsNode);
        }
        p=p->next;
    }

    int nsTabSize =0;
    p = nsNode;
    while(p!=NULL){
        nsTabSize++;
        p=p->next;
    }
    stringNode ** nsTab = new stringNode *[nsTabSize]; 
    int a=0;
    p = H;
    while(p!=NULL){
        if((p->val[p->val.size()-1]=='h' && p->val[p->val.size()-2]=='.')||(p->val[p->val.size()-1]=='p'&&p->val[p->val.size()-2]=='p'&&p->val[p->val.size()-3]=='c'&&p->val[p->val.size()-4]=='.')){
            std::ifstream File(p->val);

            string word;
            //nazwa namespa..
            string name1;
            //nazwa tego co się w nim znajduje
            string name2;
            while(!File.eof()){
                File>>word;
                bool loop=true;
                //przeszukiwanie czy w słowie jest ::
                for(int i=0; i<word.size()-1; i++){
                    name1="";
                    name2="";
                    a=0;
                    if((word[i] == ':')&&(word[i+1] == ':')&&(word.size()>2)){
                        //od :: w prawo do ;
                        for( int j=0; j<word.size(); j++){
                            if((word[j] == ':')){
                                a=1;
                            }
                            else{
                                if((word[j] == '<')||(word[j] == '>')||(word[j] == '(')){
                                    break;
                                }
                                if(a == 0){
                                    name1+=word[j];
                                }
                                 else{
                                    name2+=word[j];
                                }
                            }
                        }
                        if(where(name1,nsNode) >= 0 )
                            Add(nsTab[where(name1,nsNode)],name2);
                        break;
                    }
                }
            }
        }
        p=p->next;
    }    
    countAndDraw(nsTabSize,nsTab,nsNode);
}


void findProbableModules(string file, stringNode * & nsNode){
    
    bool exist;
    stringNode * p;
    std::ifstream File(file);
    string word;
    string name;
    while(!File.eof()){
        
        name="";
        exist = false;
        p = nsNode;

        File>>word;
        if(word == "namespace"){
            File>>word;
            for(int i=0;i<word.size();i++){
                if((word[i]!='{')&&(word[i]!=';')){
                    name+=word[i];
                }
            }
            while(p != NULL){
                if(p->val == name){
                    exist = true;
                }
                p=p->next;
            }
            if(!exist){
                Add(nsNode,name);
            }
        }
    }
}


void countAndDraw(int nsTabSize, stringNode ** nsTab, stringNode * nsNode){

    Data.open("Data.gv");
    Data.clear();
    Data<<"digraph foo{\n";
    Data<<"label =\"Relacje między modułami\"";

    for(int i=0;i<nsTabSize;i++){
        stringNode * p = nsTab[i];
        stringNode * p1 = NULL;
        stringNode * p2 = NULL;
        int a=0;
        while (p!=NULL)
        {
            if(where(p->val,p1)<0){
                Add(p1,p->val);
                a++;
            } 
            p=p->next;
        }
        int tab[a];
        a=0;
        p2=p1;
        p = nsTab[i];
        while (p2!=NULL){
            tab[a]=howManyTimes(p2->val,p);
            a++;
            p2=p2->next;
        }

        a=0;
        p=nsNode;
        while (p!=NULL){
            while (p1!=NULL){
                Data<<"\""<<p->val<<"\""<<" -> \""<<p1->val<<"\""<<"[label =  \""<<tab[a]<<"\"]\n";
                a++;
                p1=p1->next;
            }
            p=p->next;
        }
    }
    Data<<"}";
    WriteRunBashFile("GraphStoryThree");
}