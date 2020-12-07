#pragma once
#include <iostream>
#include <dirent.h>
#include <vector>
#include <map>
#include <fstream>


using namespace std;

class StoryOne{
    

    public:
    //zmienna przetrzymujaca dane o wezlach połączeniach oraz ilosciach wystąpień
    map<string,map<string, int>> FunctionsConnectionsMap;

    //tworzy liste plikow w folderze zawierajacym
    static vector<string> Files(const char * directory = "."){
        DIR *dr;
        vector <string> Ours;
        struct dirent *en;
        dr = opendir("."); //open all directory
        if (dr) {
        while ((en = readdir(dr)) != NULL) {  
            Ours.push_back(en->d_name);   
        }
        closedir(dr); //close all directory
        }
        return Ours;
    }

    //jesli plik jest typu cpp lub .h otwieramy go i sprawdzamy jego zawartosc
    static void includes(vector<string> f, map<string, vector<string>> & k){
        for(int i=0;i<f.size();++i){
            if( (f[i][f[i].size()-1]=='p' && f[i][f[i].size()-2]=='p' && f[i][f[i].size()-3]=='c' && f[i][f[i].size()-4]=='.') || (f[i][f[i].size()-1]=='h' && f[i][f[i].size()-2]=='.')){
                connections(f[i],k,f);
            }
        }
    }

    //po otwarciu pliku przechodzimy linijka po linijce
    static void connections(string name, map<string,vector<string>> & list,vector<string>h){
        ifstream File(name);
        string line;
        while(!File.eof()){
            getline(File,line);
            Contains(line,list,name,h);
        }
    }

    //jesli znalezlismy include sprawdzamy czy jest to plik systemowy czy nasz wlasny
    static void Contains(string line, map <string,vector<string>> & list, string name,vector<string>h){
        bool system=1;
        string LookFor="#include";
        size_t gdzie=line.find(LookFor);
        if(gdzie!=string::npos){
            gdzie+=LookFor.size();
            string conta=line.substr(gdzie);
            for(int i=0;i<conta.size();i++){
                if(conta[i]==' ' || conta[i]==34){
                    conta.erase(i,1);
                    i--;
                }
            }
            for(int i=0;i<h.size();++i){
                if(conta==h[i]){
                    system=0;
                    break;
                }
            }
            if(!system){
                CheckAdd(list,name,conta);
            }
        }
       
    }

    //jesli plik nie wystepuje dopisujemy go do vectora
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

    //generowanie .gv wykorzystywanego przez graphviz- do zmiany przy zmianie programu do grafow
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

    static void draw(){
         ofstream script("script.sh");
        script<<"#/bin/bash\ndot -Tpng Data.gv -o graf.png"<<"\ndisplay graf.png";
        script.close();
    }

    static void showgraph(){
        system("bash script.sh");
        system("graf.png");
    }

};