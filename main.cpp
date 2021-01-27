#include <iostream>
#include <sys/types.h>
#include "class.h"
#include <vector>
#include <map>
#include "cyclomatix.cpp"
#include <string>

using namespace std;
// obecnosc 7.01.2021 
// Bartosz Tonderski
// Krystian Zapart
// Diego Vega
// Michał Zając 
int main(){
    map<string,map<string, int>> FunctionsConnectionsMap;
    map<string, vector<string>> Hi;
    //deklaracja uzytych programow zewnetrznych
    cout<<"grafy tworzone przy uzyciu Graphviz\n";

    // wybor dzialania programu - wybiera uzytkownik
    cout<<"Wpisz sciezke do folderu\n";
    string path;
    cin>>path;
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
        vector <string> Files = StoryOne::Files(path.string::c_str());
        //ustalenie plikow zawierajacych sie w include pomijajac biblioteki systemowe           
        StoryOne::includes(Files,Hi,path.string::c_str());
        cout<<"haaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
        //stworzenie danych do grafu
        StoryOne::Generategv(Hi);
        StoryNine::Git_ID();
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
        StoryTwo::ST(FunctionsConnectionsMap,path.string::c_str());
        StoryTwo::Generategv(FunctionsConnectionsMap);
        StoryNine::Git_ID();
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
        StoryThree::CreateConnectionsBetweenNamespaces(Files,namespace_connections_map,path.string::c_str());//Wywolanie funkcji tworzacej polaczenia modulow
        StoryTwo::Generategv(namespace_connections_map);
        StoryNine::Git_ID();
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
        
            vector <string> Files = StoryOne::Files(path.string::c_str());
            vector <string> Files2 = StoryOne::Files(path.string::c_str());
            map<string, string> Connections;
            vector <string> Files3 = StoryOne::Files(path.string::c_str());

            char a = 'n';
            cout<<"Chcesz zobazczyc historyjke  1\n";
            cin>>a;
            if(a=='y'){
                cout<<"aaaaaaaaaaaaaaaaaaaaaaaa";
                StoryOne::includes(Files,Hi,path.string::c_str());
                a='n';
            }

            cout<<"Chcesz zobazczyc historyjke  2\n";
            cin>>a;
            if(a=='y'){
                StoryTwo::ST(FunctionsConnectionsMap);
                a='n';
            }

            cout<<"Chcesz zobazczyc historyjke  3\n";
            cin>>a;
            if(a=='y'){
                StoryThree::CreateConnectionsBetweenNamespaces(Files2,FunctionsConnectionsMap,path.string::c_str());
                a='n';
            }

            cout<<"Chcesz zobazczyc historyjke  6\n";
            cin>>a;
            if(a=='y'){
                StoryTwo::RemoveWrongTypeOfFile(Files3);
                StorySix::CreateConnectionsBetweenFilesAndMethods(Files3,Connections,path.string::c_str());
                a='n';
            }
            
            StoryFive::OneGraphToShowThemAll(Hi, FunctionsConnectionsMap, Connections);
            StoryNine::Git_ID();
            //Option between Circo(6) And Dot(1)
//            StorySix::draw();
            StoryOne::draw();
            StoryOne::showgraph();
        //Albo zrobić w kompletnie inny sposób 

        }break;
         
        case 6:{
//          ------------------------------------------------------------------
//            Historyjka 6:
//            Jako programista chcę zobaczyć graf relacji między plikami a
//            funkcjami/metodami w podanym kodzie źródłowym,
//            w celu analizy zależności w kodzie źródłowym.
            map<string, string> Connections;
            vector <string> Files = StoryOne::Files(path.string::c_str());
            StoryTwo::RemoveWrongTypeOfFile(Files);
            StorySix::CreateConnectionsBetweenFilesAndMethods(Files,Connections,path.string::c_str());
            StorySix::GenerateGraph(Connections);
            StoryNine::Git_ID();
            //Option between Circo(6) And Dot(1)
//            StorySix::draw();
            StoryOne::draw();
            StoryOne::showgraph();
        }break;

        case 8:{
            //Jeszcze raz przemyśleć w jaki sposób chcemy wyświetlić złożoność cyklomatyczną
            //No i pozostaje tylko wywołanie funkcji w mainie
            map <std::string, map <std::string, int> > cyclomaticMap;
            StoryEight::CyclomaticComplexityOfAFunction(cyclomaticMap,path.string::c_str());
            StoryEight::PrintConnectionMapContents(cyclomaticMap);
            StoryEight::GenerateCycloGraph(cyclomaticMap);            
            StoryNine::Git_ID();
            StoryEight::draw();
            StoryEight::showgraph();
           
            //To wszystko bylo robione na windowsie, dlatego pamietajcie o zmianie argumentow dla file.open w cyclomatix.cpp
            //ehhhhh... chyba sie na linuxa będę przenosił przy kodowaniu
        }break;
//          ------------------------------------------------------------------
//            Historyjka 9:
//            Dodanie do grafów aktuaną wersję komita  
//            Historyjka została zrealizowana poprzez wywołanie funkcji Git_ID przy każdej historyjce
            
        case 10:{
            StoryTen::CheckChanges();
            StoryTen::Id_compare();
            StoryTen::GenerateAndShowChangeGraph();
        }
        default:{
            cout<<"Cos poszlo nie tak. Sp8robuj ponownie c:\n";
        }break;
    }
        
    

    return 0;
}
