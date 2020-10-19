#include <iostream>
#include "fun.h"
#include <dirent.h>
#include<sys/types.h>
#include "InFileIncludes.h"

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
   for(auto it=files.begin();it!=files.end();++it){
       if((it.val[it.val.size()-1]=='h' && it.val[it.val.size()-2]=='.')||(it.val[it.val.size()-1]=='p'&&it.val[it.val.size()-2]=='p'&&it.val[it.val.size()-3]=='c'&&it.val[it.val.size()-4]=='.'))
       Connections(it.val);
   }



   return(0);
}