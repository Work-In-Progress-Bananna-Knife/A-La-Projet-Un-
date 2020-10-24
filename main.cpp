#include <iostream>
#include "InFileIncludes.h"
#include <dirent.h>
#include<sys/types.h>
#include <vector>


using namespace std;

#pragma region main()
int main(void) {
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



   return(0);
}
#pragma endregion
