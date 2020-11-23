#include "moduleFinderHeader.h"
//ContainDefinitions

void funkcja(stringNode * H, bool isStory5){
    stringNode * nsNode = NULL;
    stringNode * p = H;
    while(p){
        if((p->val[p->val.size()-1]=='h' && p->val[p->val.size()-2]=='.')||(p->val[p->val.size()-1]=='p'&&p->val[p->val.size()-2]=='p'&&p->val[p->val.size()-3]=='c'&&p->val[p->val.size()-4]=='.'))
            findProbableModules(p->val,isStory5);
        p=p->next;
    }
    int a=0;
    p = H;
    while(p){
        if((p->val[p->val.size()-1]=='h' && p->val[p->val.size()-2]=='.')||(p->val[p->val.size()-1]=='p'&&p->val[p->val.size()-2]=='p'&&p->val[p->val.size()-3]=='c'&&p->val[p->val.size()-4]=='.')){
            std::ifstream File(p->val);
            std::string word;
            //nazwa namespa..
            std::string name1;
            //nazwa tego co się w nim znajduje
            std::string name2;
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
                                if((word[j] == '<')||(word[j] == '>')||(word[j] == '(')||(word[j] == '.')||(word[j] == ')')){
                                    break;
                                }
                                if(a == 0){
                                    name1+=word[j];
                                }
                                 else{
                                     if((word[j] == ':'))
                                        break;
                                    name2+=word[j];
                                }
                            }
                        }
                        CheckAndAddVector(vec,name1,name2);
                        break;
                    }
                }
            }
        }
        p=p->next;
    }    
    Draw(isStory5);
}


void findProbableModules(string file, bool isStory5){
    
    bool exist;
    stringNode * p;
    std::ifstream File(file);
    string word;
    string name;
    while(!File.eof()){
        
        name="";

        File>>word;
        if(word == "namespace"){
            File>>word;
            for(int i=0;i<word.size();i++){
                if((word[i]!='{')&&(word[i]!=';')){
                    name+=word[i];
                }
            }
                //story 5
                stringNode * a = NULL;
                Add(a,name);
                vec.push_back(a);
                //
        }
    }
}


void Draw(bool isStory5){

    if(!isStory5){
        Data.open("Data.gv");
        Data.clear();
        Data<<"digraph foo{\n";
        Data<<"label =\"Relacje między moduami\"";
        DrawGv(vec); 
        Data<<"}";
        WriteRunBashFile("GraphStoryThree");
    }
}