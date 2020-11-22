#include <iostream>
#include "InFileIncludes.h"
#include <dirent.h>
#include <sys/types.h>
#include "moduleFinder.h"
//ContainDefinitions

using namespace std;


int main(void) {
    //wybor historyjki
    std::cout<<"grafy tworzone przy uzyciu Graphviz\n";
    std::cout<<"Wybierz historyjke\n";
    int historyjka;
    std::cin>>historyjka;
    //historyjka 1 - graf polaczen fizycznych
    if(historyjka == 1){
        //pobieranie nazw plików z folderu
        DIR *dr;
        vector <string> Ours;
        struct dirent *en;
        stringNode * files = NULL;
        dr = opendir("."); //open all directory
        if (dr) {
        while ((en = readdir(dr)) != NULL) {  
            Add(files, en->d_name);
            Ours.push_back(en->d_name);   
        }
        //Show(files);
        closedir(dr); //close all directory
        }
        
        IsSourceFile(files,Ours);
        
        // wywołanie okienka z grafem
        string scriptname = "GraphStoryOne.sh";
        #if !(defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__))
        scriptname = "bash "+scriptname;
        #endif
        const char* c=scriptname.c_str();
        system(c);
        
    }
    //historyjka 2 graf polaczen logicznych
    else if(historyjka == 2){
        //pobieranie nazw plików z folderu
        DIR *dr;
        vector <string> Ours;
        struct dirent *en;
        stringNode * files = NULL;
        dr = opendir("."); //open all directory
        if (dr) {
            while ((en = readdir(dr)) != NULL) {
                std::string p =en->d_name;
                if((p[p.size()-1]=='h' && p[p.size()-2]=='.')||(p[p.size()-1]=='p'&&p[p.size()-2]=='p'&&p[p.size()-3]=='c'&&p[p.size()-4]=='.')){
                   Add(files, p); 
                }
                Ours.push_back(en->d_name);
            }
        closedir(dr); //close all directory
        }
        stringNode * fun = NULL;
        StoryTwo(files,fun);

        // wywołanie okienka z grafem
        string scriptname = "GraphStoryTwo.sh";
        #if !(defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__))
        scriptname = "bash "+scriptname;
        #endif
        const char* c=scriptname.c_str();
        system(c);
        
    }
    //historyjka 3 pokazuje graf połączeń między modułami
    else if(historyjka == 3){
        //pobieranie nazw plików z folderu
        DIR *dr;
        vector <string> Ours;
        struct dirent *en;
        stringNode * files = NULL;
        dr = opendir("."); //open all directory
        if (dr) {
            while ((en = readdir(dr)) != NULL) {
                Add(files, en->d_name);
                Ours.push_back(en->d_name);
            }
            closedir(dr); //close all directory
        }
        funkcja(files);

        // wywołanie okienka z grafem
        string scriptname = "GraphStoryThree.sh";
        #if !(defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__))
        scriptname = "bash "+scriptname;
        #endif
        const char* c=scriptname.c_str();
        system(c);
    }
    //historyjka 4
    else if(historyjka == 4){

        /*int h1,h2,h3;
        cout<<"Wyswietlic graf 1?\n";
        cin>>h1;
        cout<<"Wyswietlic graf 2?\n";
        cin>>h2;
        cout<<"Wyswietlic graf 3?\n";
        cin>>h3;
        if(h1){

        }
        if(h2){

        }
        if(h3){

        }
        

       */

    }
    //obsługa błędu
    else{
        std::cout<<"UPS cos poszlo nie tak :/\n";
    }
   return(0);
}
