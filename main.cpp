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
    cin>>historyjka;
//    while(historyjka!=1 &&historyjka!=2 && historyjka!=3 && historyjka!=6){
//    cin>>historyjka;
//    if(historyjka <1 || historyjka > 6 || historyjka==4){
//        cout<<"Cos poszlo nie tak. Sprobuj ponownie c:\n";
//    }
//    }
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
        case 2:{
        //---------------------------------------------------------------------------------
        // Historyjka 2:
        /*
        Jako programista chcę zobaczyć graf relacji między funkcjami/metodami w podanym
        kodzie źródłowym, w celu analizy zależności w kodzie źródłowym.
        */
        StoryTwo::ST(FunctionsConnectionsMap);
        StoryTwo::Generategv(FunctionsConnectionsMap);
        StoryTwo::draw();
        StoryTwo::showgraph();
        }break;
    case 3:{
        //---------------------------------------------------------------------------------        
        // Historyjka 3:
        /*
        Jako architekt oproramowania chcę zobaczyć graf relacji między modułami logicznymi
        w podanym kodzie źródłowym, w celu analizy zależności w programie.
        */
        map<string,map<string, int>> namespace_connections_map;//mapa pomocnicza 
        
        vector <string> Files = StoryOne::Files(); //Pobranie nazw plikow z folderu.
        StoryThree::Create_Connections_Between_Namespaces(Files,namespace_connections_map);//Wywolanie funkcji tworzacej polaczenia modulow
        StoryTwo::Generategv(namespace_connections_map);
        StoryOne::draw();//Utworzenie grafu
        StoryOne::showgraph();//Wyswietlenie grafu
    }break;
            
        case 5:{
        //---------------------------------------------------------------------------------        
        // Historyjka 5:
        /*
        Jako architekt oprogramowania chcę mieć możliwość zobaczenia na tym samym grafie
        relacji pomiędzy: plikami, metodami, pakietami, w celu analizy struktury oprogramowania.
        */

        //Przejście przez wszystkie wcześniejsze historyjki i zapytanie go które mają zostać wyświetlone
        //Zrobić różne wywołania dla różnych kombinacji. Przykładowo dla h1,h2,h3 lub h1,h3 lub h2,h3
        
            vector <string> Files = StoryOne::Files();
            vector <string> Files2 = StoryOne::Files();
            map<string, string> Connections;
            vector <string> Files3 = StoryOne::Files();

            char a = 'n';
            cout<<"Chcesz zobazczyc historyjke  1\n"<<endl;
            cin>>a;
            if(a=='y'){
                StoryOne::includes(Files,Hi);
                a='n';
            }

            cout<<"Chcesz zobazczyc historyjke  2\n"<<endl;
            cin>>a;
            if(a=='y'){
                StoryTwo::ST(FunctionsConnectionsMap);
                a='n';
            }

            cout<<"Chcesz zobazczyc historyjke  3\n"<<endl;
            cin>>a;
            if(a=='y'){
                StoryThree::Create_Connections_Between_Namespaces(Files2,FunctionsConnectionsMap);
                a='n';
            }

            cout<<"Chcesz zobazczyc historyjke  6\n"<<endl;
            cin>>a;
            if(a=='y'){
                StoryTwo::RemoveWrongTypeOfFile(Files3);
                StorySix::CreateConnectionsBetweenFilesAndMethods(Files3,Connections);
                a='n';
            }
            
            StoryFive::OneGraphToShowThemAll(Hi, FunctionsConnectionsMap, Connections);
            StoryOne::draw();
            StoryOne::showgraph();
        //Albo zrobić w kompletnie inny sposób 

        }break;
         
        case 6:{
//          ------------------------------------------------------------------
//             Historyjka 6:
//            Jako programista chcę zobaczyć graf relacji między plikami a
//            funkcjami/metodami w podanym kodzie źródłowym,
//            w celu analizy zależności w kodzie źródłowym.
            map<string, string> Connections;
            vector <string> Files = StoryOne::Files();
            StoryTwo::RemoveWrongTypeOfFile(Files);
            StorySix::CreateConnectionsBetweenFilesAndMethods(Files,Connections);
            StorySix::GenerateGraph(Connections);
            StorySix::draw();
            StoryOne::showgraph();
        }break;
            
        default:{
            cout<<"Cos poszlo nie tak. Sprobuj ponownie c:\n";
        }break;
    }
        
    

    return 0;
}
