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
    //std::cin>>historyjka;
    historyjka=1;
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
    else if(historyjka ==2){

        stringNode * fun = NULL;
        GetFunNode(fun);
        Show(fun);
        FunConnections("InFileIncludes.h", fun);

    }
    else{
        std::cout<<"UPS cos poszlo nie tak :/\n";
        
    }

   return(0);
}
#pragma endregion
