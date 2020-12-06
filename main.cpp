#include <iostream>
#include <sys/types.h>
#include "StoryTwo.h"
#include "class.h"
#include <vector>
#include <map>

using namespace std;

int main(){
    map<string,map<string, int>> FunctionsConnectionsMap;
    map<string, vector<string>> Hi;
    //deklaracja uzytych programow zewnetrznych
    cout<<"grafy tworzone przy uzyciu Graphviz\n";

    // wybor dzialania programu - wybiera uzytkownik
    cout<<"Wybierz historyjke\n";
    int historyjka;
    while(historyjka!=1 &&historyjka!=2 && historyjka!=3 && historyjka!=5){
    cin>>historyjka;
    if(historyjka <1 || historyjka > 5 || historyjka==4){
        cout<<"wprowadzono nieprawidlowe dane. Sprobuj ponownie\n";
    }
    }
    switch (historyjka)
    {
    case 1:{
            //wywolanie metod historyjki pierwszej
            
            //lista plikow w folderze zapisana do vectora Files
            
            vector <string> Files = StoryOne::Files();
            
            //ustalenie plikow zawierajacych sie w include pomijajac biblioteki systemowe
            
            StoryOne::includes(Files,Hi);
            
            //stworzenie danych do grafu

            StoryOne::Generategv(Hi);
            
            //utworzenie grafu plikow
            
            StoryOne::draw();
            StoryOne::showgraph();


            
    }
        
        break;
    case 2:
        StoryTwo::ST(FunctionsConnectionsMap);
        StoryTwo::draw();
        StoryTwo::showgraph();
        break;
    case 3:
        /* code */
        break;
    case 5:
        /* code */
        break;
         
    default:
        break;
    }
        
    

    return 0;
}