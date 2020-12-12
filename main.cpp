#include <iostream>
#include <sys/types.h>
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
        cout<<"Cos poszlo nie tak. Sprobuj ponownie c:\n";
    }
    }
    switch (historyjka)
    {
    case 1:{
        //---------------------------------------------------------------------------------        
        // Historyjka 1:
        /*
        Jako programista, chcę zobaczyć graf pokazujący połączenia pomiędzy plikami z
        kodem źródłowym w projekcie
        */

        //wywolanie metod historyjki pierwszej
        //lista plikow w folderze zapisana do vectora Files   
        vector <string> Files = StoryOne::Files();
        //ustalenie plikow zawierajacych sie w include pomijajac biblioteki systemowe           
        StoryOne::includes(Files,Hi);
        cout<<"haaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
        //stworzenie danych do grafu
        StoryOne::Generategv(Hi);            
        //utworzenie grafu plikow            
        StoryOne::draw();
        StoryOne::showgraph();  
     } break;
    case 2:
        //---------------------------------------------------------------------------------
        // Historyjka 2:
        /*
        Jako programista chcę zobaczyć graf relacji między funkcjami/metodami w podanym
        kodzie źródłowym, w celu analizy zależności w kodzie źródłowym.
        */
        StoryTwo::ST(FunctionsConnectionsMap);
        StoryTwo::draw();
        StoryTwo::showgraph();
        break;
    case 3:{
        //---------------------------------------------------------------------------------        
        // Historyjka 3:
        /*
        Jako architekt oproramowania chcę zobaczyć graf relacji między modułami logicznymi
        w podanym kodzie źródłowym, w celu analizy zależności w programie.
        */
        vector <string> Files = StoryOne::Files(); //Pobranie nazw plikow z folderu.
        StoryThree::Create_Connections_Between_Namespaces(Files);//Wywolanie funkcji tworzacej polaczenia modulow
        StoryThree::Draw_Graph();//Utworzenie grafu
        StoryThree::View_Graph();//Wyswietlenie grafu
    }break;
    case 5:
        //---------------------------------------------------------------------------------        
        // Historyjka 5:
        /*
        Jako architekt oprogramowania chcę mieć możliwość zobaczenia na tym samym grafie
        relacji pomiędzy: plikami, metodami, pakietami, w celu analizy struktury oprogramowania.
        */

        //Przejście przez wszystkie wcześniejsze historyjki i zapytanie go które mają zostać wyświetlone
        //Zrobić różne wywołania dla różnych kombinacji. Przykładowo dla h1,h2,h3 lub h1,h3 lub h2,h3
        


        //Albo zrobić w kompletnie inny sposób 

        break;
         
    default:
        break;
    }
        
    

    return 0;
}