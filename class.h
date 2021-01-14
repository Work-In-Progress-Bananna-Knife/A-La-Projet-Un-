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
    static vector<std::string> Files(const char * directory = "."){
        DIR *dr;
        vector <std::string> Ours;
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
    static void includes(vector<std::string> f, map<std::string, vector<std::string> > & k){
        for(int i=0;i<f.size();++i){
            if( (f[i][f[i].size()-1]=='p' && f[i][f[i].size()-2]=='p' && f[i][f[i].size()-3]=='c' && f[i][f[i].size()-4]=='.') || (f[i][f[i].size()-1]=='h' && f[i][f[i].size()-2]=='.')){
                connections(f[i],k,f);
            }
        }
    }

    //po otwarciu pliku przechodzimy linijka po linijce
    static void connections(std::string name, map<std::string,vector<std::string> > & list,vector<std::string>h){
        ifstream File(name);
        std::string line;
        while(!File.eof()){
            getline(File,line);
            Contains(line,list,name,h);
        }
    }

    //jesli znalezlismy include sprawdzamy czy jest to plik systemowy czy nasz wlasny
    static void Contains(std::string line, map <std::string,vector<std::string> > & list, std::string name,vector<std::string>h){
        bool system=1;
        std::string LookFor="#include";
        size_t gdzie=line.find(LookFor);
        if(gdzie!=std::string::npos){
            gdzie+=LookFor.size();
            std::string conta=line.substr(gdzie);
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
    static void CheckAdd(map <std::string,vector<std::string> > & list, std::string name,std::string conta){
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
    static void Generategv(map<std::string,vector<std::string> > k){
        GenerateXML(k);
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
    static void GenerateXML(map<std::string,vector<std::string> > k){
        ofstream plik;
        plik.open("paradigm.xml");
        plik<<"<?xml version=\"1.0\"?>\n"<<"<!DOCTYPE GraphXML SYSTEM \"file:GraphXML.dtd\">\n"<<"<GraphXML>\n"<<"<graph>\n";
        //for( auto it=k.begin();it!=k.end();++it){
        //    plik<<"<node name=\""<<it->first<<"\"/>\n";
        //}
        for( auto it=k.begin();it!=k.end();++it){
            plik<<"<node name=\""<<it->first<<"\"/>\n";
            for(int i=0;i<it->second.size();++i){
                plik<<"<node name = \""<<it->second[i]<<"\"/>";
                plik<<"<edge source=\""<<it->first<<"\" target=\""<<it->second[i]<<"\"/>\n";
            }
            plik<<"</graph>\n </GraphXML>";
        }
    }

    static void draw(){
         ofstream script("script.sh");

        script<<"#/bin/bash\ndot -Tpng Data.gv -o graf.png"<<"\ndisplay graf.png"<<"\nopen graf.png";
        script.close();
    }

    static void showgraph(){
        system("bash script.sh");
        system("graf.png");
    }

};
struct StoryTwo : public StoryOne{

    //Usuwanie plików złego typu (nie .cpp czy .h)
    static void RemoveWrongTypeOfFile(vector<std::string>  &f){
        vector <std::string> F;
        for(int i=0;i<f.size();++i){
            if((f[i][f[i].size()-1]=='p' && f[i][f[i].size()-2]=='p' && f[i][f[i].size()-3]=='c' && f[i][f[i].size()-4]=='.') || (f[i][f[i].size()-1]=='h' && f[i][f[i].size()-2]=='.'))
                F.push_back(f[i]);
        } 
        f=F;
    }

// ( >63&& <91 ) || (>96 && <123)
//zwraca std::string od miejsca x do następnego napotkanego znaku (idąc w prawo) nie będącego literą
    static std::string GetWordFromX(std::string word,int x){
        x++;
        std::string result = "";
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

//zwraca std::string od miejsca x do następnego napotkanego znaku (idąc w lewo) nie będącego literą
    static std::string ReverseGetWordFromX(std::string word,int x){
        x--;
        std::string result = "";
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
    static int BracesSkip(std::string word,int x){
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
    static void CheckAdd( map<std::string,map<std::string, int> > & connectionMap, std::string name, std::string conta){
        bool exist1 = false;
        bool exist2 = false;
        map<std::string,map<std::string, int> >::iterator itr;
        for(itr = connectionMap.begin(); itr != connectionMap.end(); ++itr){
            if(itr->first == name){
                exist1 = true;
                map<std::string,int>::iterator itr2;
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
            map<std::string, int> a;
            a.insert({conta, 1});
            connectionMap.insert({name,a});
        }
    }
    
    //wyszukuje wywołań funkcji w funkcji któ©ej nazwa została podana w functionName
    static void FindFunctionCallsInDefinitions(ifstream &File, map<std::string,map<std::string, int> > & connectionsMap, std::string line, int x, std::string functionName){
        int a = 1; //ammount of '{'
        int b = 0; //ammount of '}'
        size_t where;
        x++;
        std::string LookFor="(";
        while(a != b){
            for(int i=x; i<line.size(); i++){
                x=i;
                if((line[i] == '{')&&(line[i-1] != '\''))
                    a++;
                else if((line[i] == '}')&&(line[i-1] != '\''))
                    b++;

                where = i;
                if(line[where] == '('){
                    std::string name = ReverseGetWordFromX(line,where);
                    if((name != "if") && (name != "while") && (name != "for") && (name != "switch") && (name != "") && (name != "\'")&& (name != "\"")){
                        where = BracesSkip(line,where);
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
    static void GetFunctionConnections(ifstream &File, map<std::string,map<std::string, int> > & connectionsMap){
        std::string word;
        std::string line;
        while(!File.std::ios::eof()){
            //File> >word;
            getline(File,line);
            std::string LookFor="(";
            size_t where=line.find(LookFor);
            
            if(where!=std::string::npos){            
                std::string name = ReverseGetWordFromX(line,where);
                if((name != "if") && (name != "while") && (name != "for") && (name != "switch") && (name != "") && (name != "\'")&& (name != "\"")){
                    where = BracesSkip(line,where);
                    if(line[where+1] == '{'){

                        FindFunctionCallsInDefinitions(File,connectionsMap,line,where+1, name);
                    }
                }
                
            }
        }
    }

//wywoływanie funkcji do historyjki druiej
    static void ST(map<std::string,map<std::string, int> > & connectionsMap, const char * directory = "."){
        //tworzenie listy plików w folderze
        vector<std::string> files = Files(directory);
        RemoveWrongTypeOfFile(files);
        for (auto i = files.begin(); i != files.end(); ++i){
            ifstream File(*i);
            GetFunctionConnections(File,connectionsMap);
            
        }
//        Generategv(connectionsMap);

    }
//tworzenie grafu połączeń między funkcjami
    static void Generategv(map<std::string,map<std::string, int> > connectionMap){
        ofstream plik;
        plik.open("Data.gv");
        plik<<"digraph foo{\n";
        map<std::string,map<std::string, int> >::iterator itr;
        for(itr = connectionMap.begin(); itr != connectionMap.end(); ++itr){
            map<std::string, int >::iterator itr2;
            for(itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2){
                plik<<"\""<<itr->first<<"\""<<"->"<<"\""<<itr2->first<<"\""<<"[label = \""<<itr2->second<<"\"];\n";
            }

        }

        plik<<"}";
        plik.close();
    }
};

class StoryThree : StoryOne{
    public:
    //Głowna funkcja do historyjki nr. 3. Tworzy polaczenia polaczenia pomiedzy plikami i zapisuje
    static void CreateConnectionsBetweenNamespaces(vector <std::string> H, map<std::string,map<std::string,int> > &namespace_connections_map){
        //2# z tych plikow odrzucic wszystkie pliki ktore nie maja koncowki .h lub .cpp       
        vector<std::string>Files;
        for(int i=0;i<H.size();++i){
            if((H[i][H[i].size()-1]=='h' && H[i][H[i].size()-2]=='.') || (H[i][H[i].size()-1]=='p' && H[i][H[i].size()-2]=='p' && H[i][H[i].size()-3]=='c' && H[i][H[i].size()-4]=='.')){
                Files.push_back(H[i]);
            }
        }
        //3# przeszukac pliki pod katem namespace
//        map<std::string,map<std::string,int> > namespace_connections_map;
        vector<std::string> class_list = CheckIfClassOrStruct(Files);
        for( int i=0;i<Files.size();++i){
            ifstream Input(Files[i]);
            std::string namespace_name;
            std::string namespace_contains;
            std::string line;            
            while(!Input.eof()){
                //3.1# wyszukaj sama lokalizacje namespace i co sie w nim znajduje        
                getline(Input,line);
                size_t line_location=line.find("::");
                if(line_location!=std::string::npos){ 
                    namespace_name = StoryTwo::ReverseGetWordFromX(line,line_location);
                    if(namespace_name!=""){
                        bool condition = CheckIfInVector(namespace_name,class_list);
                        if(condition==false){  
                            //4# zapisz to info                      
                            namespace_contains = StoryTwo::GetWordFromX(line,line_location+1);
                            if(namespace_contains!=""){
                                StoryTwo::CheckAdd(namespace_connections_map,namespace_name,namespace_contains);
                                //4.1# sprawdź czy w tej linijce coś jeszcze się znajduje
                                size_t location2= line_location+namespace_contains.size()+2;                        
                                while(line[location2] == ':'){                            
                                    if(line[location2+1]== ':'){
                                        namespace_name=namespace_contains;
                                        namespace_contains = StoryTwo::GetWordFromX(line,location2+1);
                                        StoryTwo::CheckAdd(namespace_connections_map,namespace_name,namespace_contains);
                                        location2 += (namespace_contains.size()+2);
                                    }
                                    else{
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }       
        }
        //5# wygeneruj polaczenia na podstawie danych
//        StoryTwo::Generategv(namespace_connections_map);
    }

    static vector<string> CheckIfClassOrStruct(vector <std::string> H){
        //wczytaj kontener z plikami
        vector<string> class_container;
        for(int i=0;i<H.size();++i){
            ifstream Input(H[i]);
            std::string class_name;
            std::string line;
            while(!Input.eof()){
                getline(Input,line);
                string lookfor = "class";
                lookfor+=" ";
                size_t line_location=line.find(lookfor);
                if(line_location!=std::string::npos){
                    class_name=StoryTwo::GetWordFromX(line,line_location+5);
                    class_container.push_back(class_name);
                }
                else{
                    lookfor = "struct";
                    lookfor+= " ";
                    line_location=line.find(lookfor);
                    if(line_location!=std::string::npos){
                        class_name=StoryTwo::GetWordFromX(line,line_location+6);
                        class_container.push_back(class_name);
                    }
                }
            }
        }
        return class_container;
        //przeszukaj ten plik pod wzgledem słowa klucz "class"
        //jeśli jest class-to zapisz nazwę stojącą po prawej stronie
        //zapisz wynik do vectora
        //zwróć vector
    }

    static bool CheckIfInVector(std::string word,vector<std::string> container){
        bool isInside=false;
        for(int i=0;i<container.size();++i){
            if(word==container[i]){
                isInside=true;
                break;
            }
        }
        return isInside;
    }

    
};

class StoryFour{
    
};

class StoryFive : StoryOne{

    public:
    //Story 1
    static void Generategv(map<std::string,vector<std::string> > k){
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
//    Story 2 i 3
    static void Generategv(map<std::string,map<std::string, int> > connectionMap){
        ofstream plik;
        plik.open("Data.gv");
        plik<<"digraph foo{\n";
        map<std::string,map<std::string, int> >::iterator itr;
        for(itr = connectionMap.begin(); itr != connectionMap.end(); ++itr){
            map<std::string, int >::iterator itr2;
            for(itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2){
                plik<<"\""<<itr->first<<"\""<<"->"<<"\""<<itr2->first<<"\""<<"[label = \""<<itr2->second<<"\"];\n";
            }
        }

        plik<<"}";
        plik.close();
    }
    
//    Story 6
    static void GenerateGraph(map<std::string,std::string> Connections){
        ofstream plik;
        plik.open("Data.gv");
        plik<<"digraph foo{\n";
        map<std::string,std::string>::iterator itr;
        for(itr = Connections.begin(); itr != Connections.end(); ++itr){
            plik<<"\""<<itr->second<<"\""<<"->"<<"\""<<itr->first<<"\""<<"[label = \"1\"];\n";
        }
       
        plik<<"}";
        plik.close();
    }
    
//    One Graph to rule them all, one Hraph to find them,
//    One Graph to bring them all, and in the darkness bind them;
    static void OneGraphToShowThemAll(map<std::string,vector<std::string> > k,map<std::string,map<std::string, int> > connectionMap,map<std::string,std::string> Connections){
        ofstream plik;
        plik.open("Data.gv");
        plik<<"digraph foo{\n";
        //3 for elven kings
        for( auto it=k.begin();it!=k.end();++it){
            for(int i=0;i<it->second.size();++i){
                plik<<"\""<<it->first<<"\""<<"->"<<"\""<<it->second[i]<<"\""<<"[label = \"1\"];\n";
            }
        }
        //7 for dwarf lords
        map<std::string,map<std::string, int> >::iterator itr;
        for(itr = connectionMap.begin(); itr != connectionMap.end(); ++itr){
            map<std::string, int >::iterator itr2;
            for(itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2){
                plik<<"\""<<itr->first<<"\""<<"->"<<"\""<<itr2->first<<"\""<<"[label = \""<<itr2->second<<"\"];\n";
            }
        }
        //9 for mortal men
        map<std::string,std::string>::iterator iter;
        for(iter = Connections.begin(); iter != Connections.end(); ++iter){
            plik<<"\""<<iter->second<<"\""<<"->"<<"\""<<iter->first<<"\""<<"[label = \"1\"];\n";
        }
        plik<<"}";
        plik.close();
    }
    
};

class StorySix : StoryOne{

    public:
    
    static void draw(){ //Draw graph with circo instead of Dot
         ofstream script("script.sh");
        script<<"#/bin/bash\ncirco -Tpng Data.gv -o graf.png"<<"\ndisplay graf.png"<<"\nopen graf.png";
        script.close();
    }
    
    //generowanie grafu dla S6 
    static void GenerateGraph(map<std::string,std::string> Connections){
        ofstream file;
        file.open("Data.gv");
        file<<"digraph foo{\n";
        map<std::string,std::string>::iterator itr;
        for(itr = Connections.begin(); itr != Connections.end(); ++itr){
            file<<"\""<<itr->second<<"\""<<"->"<<"\""<<itr->first<<"\""<<"[label = \"1\"];\n";
        }
       
        file<<"}";
        file.close();
    }
    
//metoda pozbywająca się klamer
    static void BuckleSkip(ifstream &File, std::string line, int x){
                int a = 1; //ammount of '{'
                int b = 0; //ammount of '}'
                x++;
                while(a != b){
                    for(int i=x; i<line.size(); i++){
                        x=i;
                        if((line[i] == '{')&&(line[i-1] != '\''))
                            a++;
                        else if((line[i] == '}')&&(line[i-1] != '\''))
                            b++;
                    }
                        
                    getline(File,line);
                    x=0;
                }
            }
//metoda znajduje w podanych plikach metody/funkcje
//zapisuje je w mapie i tworzy graf
    static void CreateConnectionsBetweenFilesAndMethods(vector<string> Files, map<string, string> &Connections){
        std::string line;
//        map<string, string> Connections;
        for(int i=0;i<Files.size();++i){
            ifstream inFiles(Files[i]);
            
            while(!inFiles.std::ios::eof()){
                std::getline(inFiles,line);
                size_t where=line.find("(");
               
                if(where!=std::string::npos){
                    std::string name = StoryTwo::ReverseGetWordFromX(line,where);
                
                    if((name != "if") && (name != "while") && (name != "for") && (name != "switch") && (name != "") && (name != "\'")&& (name != "\"")){
                        where = StoryTwo::BracesSkip(line,where);
                        
                        if(line[where+1] == '{'){
                            Connections.insert({name,Files[i]});
                            BuckleSkip(inFiles, line, where+2);
                        }
                    }
                }
            }
        }
//            GenerateGraph(Connections);
    }
    
};

static void Git_ID(){
//Funkcja wywyłuje skrypt dodający aktualną wersję repozytorium 
    system("bash id.sh");
}
