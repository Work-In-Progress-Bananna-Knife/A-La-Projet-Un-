#include <iostream>
#include "fun.h"
#include <dirent.h>
#include<sys/types.h>

using namespace std;

int main(void) {
   DIR *dr;
   struct dirent *en;
   stringNode * files = NULL;
   dr = opendir("."); //open all directory
   if (dr) {
        while ((en = readdir(dr)) != NULL) {
            
            Add(files, en->d_name);
            
        }
        Show(files);
        closedir(dr); //close all directory
   }
   return(0);
}