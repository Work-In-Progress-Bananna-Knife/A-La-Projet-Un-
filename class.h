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
    static vector<string> Files(const char * directory = "."){
        DIR *dr;
        vector <string> Ours;
        struct dirent *en;
        dr = opendir(directory); //open all directory
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
struct StoryTwo : public StoryOne{

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
//zwraca string od miejsca x do następnego napotkanego znaku (idąc w prawo) nie będącego literą
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

//zwraca string od miejsca x do następnego napotkanego znaku (idąc w lewo) nie będącego literą
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

//zwraca miejsce w którym kończy się nawiaz którego początek został podany w x
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

//dodaje połączenie do mapy połączeń 
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
    
    //wyszukuje wywołań funkcji w funkcji któ©ej nazwa została podana w functionName
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
                            CheckAdd(connectionsMap,functionName,name);
                        }
                    }
                }
            }
                
            getline(File,line);
            x=0;   
        }
    }

//wyszukuje definicji funkcji i wywołuje FindFunctionCallsInDefinitions
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

                        FindFunctionCallsInDefinitions(File,connectionsMap,line,where+1, name);
                    }
                }
                
            }
        }
    }

//wywoływanie funkcji do historyjki druiej
    static void ST(map<string,map<string, int>> & connectionsMap, const char * directory = "."){
        //tworzenie listy plików w folderze
        vector<string> files = Files(directory);
        RemoveWrongTypeOfFile(files);
        for (auto i = files.begin(); i != files.end(); ++i){
            ifstream File(*i);
            GetFunctionConnections(File,connectionsMap);
            
        }
        Generategv(connectionsMap);
    }
//tworzenie grafu połączeń między funkcjami
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

class StoryThree : StoryOne{
    public:

    //Głowna funkcja do historyjki nr. 3. Tworzy polaczenia polaczenia pomiedzy plikami i zapisuje
    static void Create_Connections_Between_Namespaces(vector <string> H){
        //2# z tych plikow odrzucic wszystkie pliki ktore nie maja koncowki .h lub .cpp       
        vector<string>Files;
        for(int i=0;H.size();++i){
            if((H[i][H[i].size()-1]=='h' && H[i][H[i].size()-2]=='.') || (H[i][H[i].size()-1]=='p' && H[i][H[i].size()-2]=='p' && H[i][H[i].size()-3]=='c' && H[i][H[i].size()-4]=='.')){
                Files.push_back(H[i]);
            }
        }
        //3# przeszukac pliki pod katem namespace
        map<string,map<string,int>> namespace_connections_map;
        for( int i=0; i <Files.size();++i){
            ifstream Input(Files[i]);
            string namespace_name;
            string namespace_contains;
            string line;
            while(!Input.eof()){
                //3.1# wyszukaj sama lokalizacje namespace i co sie w nim znajduje        
                getline(Input,line);
                size_t line_location=line.find("::");
                if(line_location!=string::npos){                   
                    namespace_name = StoryTwo::ReverseGetWordFromX(line,line_location);
                    namespace_contains = StoryTwo::GetWordFromX(line,line_location+1);
                    StoryTwo::CheckAdd(namespace_connections_map,namespace_name,namespace_contains);
                    //4# zapisz to info
                }
            }       
        }
        //5# wygeneruj polaczenia na podstawie danych
        StoryTwo::Generategv(namespace_connections_map);
    }

    //Funkcja generujaca skrypt uruchamiajacy plik z grafem polaczen modulow
    static void Draw_Graph(){
        ofstream script("script.sh");
        script<<"#/bin/bash\ndot -Tpng Data.gv -o graf.png"<<"\ndisplay graf.png";
        script.close();
    }

    //Funkcja wyswietlajaca graf polaczen
    static void View_Graph(){
        system("bash script.sh");
        system("graf.png");
    }
};