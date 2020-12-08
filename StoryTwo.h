#include "class.h"


class StoryTwo : public StoryOne{
public: 
    //tworzy liste plikow w folderze zawierajacym
    
    //Usuwanie plików złego typu (nie .cpp czy .h)
    static void RemoveWrongTypeOfFile(vector<string>  &f){
        vector <string> F;
        for(int i=0;i<f.size();++i){
            if((f[i][f[i].size()-1]=='p' && f[i][f[i].size()-2]=='p' && f[i][f[i].size()-3]=='c' && f[i][f[i].size()-4]=='.') || (f[i][f[i].size()-1]=='h' && f[i][f[i].size()-2]=='.'))
                F.push_back(f[i]);
        } 
        f=F;
    }
// ( >63&& <91 ) || (>96 && <123)
    static string GetWordFromX(string word,int x){
        x++;
        string result = "";
        for(int i=x;i<word.size();++i){
            if((word[i]>63 && word[i]<91) || (word[i]>96 && word[i]<123)){
                result += word[i];
            }
            else{
                break;
            }
        }
        return result;
    }

    static string ReverseGetWordFromX(string word,int x){
        x--;
        string result = "";
        for(int i=x;i>=0;i--){
            if((word[i]>63 && word[i]<91) || (word[i]>96 && word[i]<123)){
                result = word[i] + result;
            }
            else{
                break;
            }
        }
        return result;
    }

    static int skip(string word,int x){
        int a = 0; //liczba otwierających nawiasów
        int b = 0; //liczba zamykających nawiasów
        for(int i=x; i<word.size(); i++){
            x=i;
            if(word[i] == '(')
                a++;
            else if(word[i] == ')')
                b++;
            if(a == b){
               break;
            } 
        }
        return x;
    }

    static void CheckAdd( map<string,map<string, int>> & connectionMap, string name, string conta){
        bool exist1 = false;
        bool exist2 = false;
        map<string,map<string, int>>::iterator itr;
        for(itr = connectionMap.begin(); itr != connectionMap.end(); ++itr){
            if(itr->first == name){
                exist1 = true;
                map<string,int>::iterator itr2;
                for(itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2){
                    if(itr2->first == conta){
                        int a=itr2->second;
                        a++;
                        itr->second.erase(conta);
                        itr->second.insert({conta,a});
                        
                        exist2 = true;
                    }
                }
                if(!exist2){
                    itr->second.insert({conta,1});
                }
            } 
        }
        if(!exist1){
            map<string, int> a;
            a.insert({conta, 1});
            connectionMap.insert({name,a});
        }
    }
    
    static void FindFunctionCallsInDefinitions(ifstream &File, map<string,map<string, int>> & connectionsMap, string line, int x, string functionName){
        int a = 1; //ammount of '{'
        int b = 0; //ammount of '}'
        size_t where;
        x++;
        string LookFor="(";
        while(a != b){
            for(int i=x; i<line.size(); i++){
                x=i;
                if((line[i] == '{')&&(line[i-1] != '\''))
                    a++;
                else if((line[i] == '}')&&(line[i-1] != '\''))
                    b++;
                where = i;
                if(line[where] == '('){
                    string name = ReverseGetWordFromX(line,where);
                    if((name != "if") && (name != "while") && (name != "for") && (name != "switch") && (name != "") && (name != "\'")&& (name != "\"")){
                        where = skip(line,where);
                        if(line[where+1] == ';'){
                            cout<<" - "<<name<<endl;
                            CheckAdd(connectionsMap,functionName,name);
                        }
                    }
                }
            }  
            getline(File,line);
            x=0;   
        }
    }
    static void GetFunctionConnections(ifstream &File, map<string,map<string, int>> & connectionsMap){
        string word;
        string line;
        while(!File.std::ios::eof()){
            //File>>word;
            getline(File,line);
            string LookFor="(";
            size_t where=line.find(LookFor);
            
            if(where!=string::npos){            
                string name = ReverseGetWordFromX(line,where);
                if((name != "if") && (name != "while") && (name != "for") && (name != "switch") && (name != "") && (name != "\'")&& (name != "\"")){
                    where = skip(line,where);
                    if(line[where+1] == '{'){
                        cout<<name<<endl;
                        FindFunctionCallsInDefinitions(File,connectionsMap,line,where+1, name);
                    }
                }
                
            }
        }

    }

    
    static void ST(map<string,map<string, int>> & connectionsMap, const char * directory = "."){
        //tworzenie listy plików w folderze
        vector<string> files = Files(directory);
        RemoveWrongTypeOfFile(files);
        for (auto i = files.begin(); i != files.end(); ++i){
            ifstream File(*i);
            cout<<(*i)<<"-------------------------------"<<endl;
            GetFunctionConnections(File,connectionsMap);
            Generategv(connectionsMap);
        }
    }

    static void Generategv(map<string,map<string, int>> connectionMap){
        ofstream plik;
        plik.open("Data.gv");
        plik<<"digraph foo{\n";
        map<string,map<string, int>>::iterator itr;
        for(itr = connectionMap.begin(); itr != connectionMap.end(); ++itr){
            map<string, int >::iterator itr2;
            for(itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2){
                plik<<"\""<<itr->first<<"\""<<"->"<<"\""<<itr2->first<<"\""<<"[label = \""<<itr2->second<<"\"];\n";
            }

        }
                //plik<<"\""<<itr->first<<"\""<<"->"<<"\""<<itr2->second<<"\""<<"[label = \""<<itr2->first<<"\"];\n";

        plik<<"}";
        plik.close();
    }

};