#include <iostream>
#include "InFileIncludes.h"
#include <dirent.h>
#include <sys/types.h>
#include <vector>
#include "moduleFinder.h"
//ContainDefinitions

using namespace std;


int main(void) {


        //wybor historyjki uzytkownika z zajec

    std::cout<<"grafy tworzone przy uzyciu Graphviz\n";
    std::cout<<"Wybierz historyjke\n";
    int historyjka;
    std::cin>>historyjka;
    //historyjka=1;

        //historyjka 1 - graf polaczen fizycznych

    if(historyjka == 1){

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
        Show(files);
        closedir(dr); //close all directory
        }
        IsSourceFile(files,Ours);

    }

        //historyjka 2 graf polaczen logicznych

    else if(historyjka == 2){

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
    }

    //historyjka 3 pokazuje graf połączeń między modułami

    else if(historyjka == 3){

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

    }
    
    
    else{
        std::cout<<"UPS cos poszlo nie tak :/\n";
    }

   return(0);
}
