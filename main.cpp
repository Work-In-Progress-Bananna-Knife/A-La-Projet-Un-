#include <iostream>
#include "InFileIncludes.h"
#include <dirent.h>
#include <sys/types.h>
#include <vector>


using namespace std;

#pragma region main()
int main(void) {

    std::cout<<"grafy tworzone przy uzyciu Graphviz\n";
    std::cout<<"Wybierz historyjke\n";
    int historyjka;
    std::cin>>historyjka;
    //historyjka=2;
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
    else if(historyjka == 2){

        DIR *dr;
        vector <string> Ours;
        struct dirent *en;
        stringNode * files = NULL;
        dr = opendir("."); //open all directory
        if (dr) {
            while ((en = readdir(dr)) != NULL) {

                std::string p =en->d_name;
                if(p[p.size()-1]=='h' && p[p.size()-2]=='.'){
                   Add(files, p); 
                }
                Ours.push_back(en->d_name);
            }
        closedir(dr); //close all directory
        }

        stringNode * fun = NULL;
        funckja(files,fun);
    }
    else{
        std::cout<<"UPS cos poszlo nie tak :/\n";
    }

   return(0);
}
#pragma endregion
