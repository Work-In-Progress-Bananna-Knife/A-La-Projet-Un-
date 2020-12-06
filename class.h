#pragma once
#include <iostream>
#include <dirent.h>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

class StoryOne{
    

    public:

    //tworzy liste plikow w folderze zawierajacym
    static vector<string> Files(){
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
    static void CheckAdd(map <string,vector<string>> & list, string name,string conta){
        bool is=0;
        for(int j=0;j<list[name].size();++j){
            if(list[name][j]==conta){
                is=1;
            }
        }
        if(is==0){
            list[name].push_back(conta);
        }
    }

    //generowanie .gv wykorzystywanego przez graphviz- do zmiany przy zmianie programu do grafow
    static void Generategv(map<string,vector<string>> k){
        ofstream plik;
        plik.open("Data.gv");
        plik<<"digraph foo{\n";
        for( auto it=k.begin();it!=k.end();++it){
            for(int i=0;i<it->second.size();++i){
                plik<<"\""<<it->first<<"\""<<"->"<<"\""<<it->second[i]<<"\""<<"[label = \"1\"];\n";
            }
        }
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