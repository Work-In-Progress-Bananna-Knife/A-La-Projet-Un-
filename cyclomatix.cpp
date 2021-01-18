#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "class.h"

using namespace std;

class StoryEight : public StoryOne{
    //Cała złożoność cyklomatyczna będzie wydzielona do osobnego pliku
    private:
    
    //Metoda obliczająca złożoność cyklomatyczną - pomysł Michała
    static int CyclomaticComplexityOfAFunction(){
    //przejdź do danej funkcji (potocznie)

    // #funkcja obliczająca złożoność cyklomatyczną ma działać wyłącznie w obrębie danej funkcji

    //Każda funkcja ma być prosta w swoim działaniu. Ma wykonywać tylko jedną rzecz, do której została stworzona (by zmniejszyć złożonośc cyklomatyczną)

    /*Określanie dla jakiej funkcji szukamy warunków wyglądałoby następująco
    Musimy znaleźć definicję funkcji i linijkę, w której ta funkcja się znajduje. Następnie szukamy klamer otwierających i zamykających
    metodą Bartka-Diegusza. Linijka z pierwszą klamrą otwierającą ("{" - PKO) najczęściej będzie tą samą linijką, gdzi ejest deklaracja funkcji
    Potem szukamy ostatniej klamry zamykającej ("}" - OKZ) i zapisujemy jej linijkę występowania. Przechodzimy do zliczania
    Funkcja potrzebuje mieć kontener danych przechowujący nazwę funkcji - string i liczbę CC - int.
    Wyszukujemy w kodzie wszystkie conditionale (for, if, else... etc.). Przy okazji potrzeba metody filtrujacej te wyszukane conditionale, aby mieć pewność
    że wyszukujemy występowanie komend, a nie komentarze/odniesienia do nich..
    Po znalezieniu conditionala zapisujemy linijkę jego występowania.. jeśli znajduje się pomiędzy linijką PKO, a OKZ to inkrementujemy licznik.
    */
    //Jako, iż nasze funkcje - metody mają tylko jeden punkt wyjściowy, to formuła na obliczanie CC wynosi

    //CC = E - N + 2 (E - krawędzie, N - wierzchołki)

    //stwórz zmienne zawierające informacje o występowaniu ilości komend: for, if, else, case

    //przeszukaj kod pod względem tych występowania tych komend

    //upewnij się, że dane komendy nie są zakomentowane, bądź nie znajdują się w innym conditionalu (jak w przypadku historyjki 6 i wyszukiwaniu ifów)

    //jeśli wszystko ok, to inkrementuj dany typ countera

    //Zmiana stanów zmiennych, to inkrementacja krawędzi bądź wierzchołka

    //Oblicz CC i zwróć wartość, aby potem GraphViz mógł przedstawić CC na grafie z metodami 
    }



    //Pomysł Bartka
    //usuwa elementy innego typu niz zalozone cpp lub header z vectora listy elementow w folderze
    
        vector <string> checked(){
            vector <string> Files=StoryOne:Files();
            for(int i=0;i<Files.size();++i){
                if(!((Files[i][Files[i].size()-1] == 'h' && Files[i][Files[i].size()-2] == '.' ) || (Files[i][Files[i].size()-1] == 'p' && Files[i][Files[i].size()-2] == 'p' && Files[i][Files[i].size()-3] == 'c' && Files[i][Files[i].size()-4] == '.') )){
                    Files.erase(Files.begin()+i);
                    --i;
                }
            }
            return Files;
        }
    
    //na pojedynczych plikach wywoluje analize cyklometrycznej zlozonosci danego pliku oraz funkcji w niej zawartych wynik to mapa funkcja - zlozonosc
    
    static map<string, int> cyclomatic(vector<string> Files){
        ifstream analyze;
        for(int i=0;i<Files.size();++i){
            analyze.open(Files[i]);
            mapElement point = FunctionComplexicity(analyze);
        }
    }
    
    //do rozbudowania o wykluczanie zakomentowanych obszarow na razie liczy ify w plikach cpp i h tez kozak ale no... jeszcze trzeba funckje ogarnac xd HF <3
    
    static mapElement FunctionComplexicity(ofstream File){
        int counter=0;
        string line;
        while(!File.eof()){
            getline(File,line);
            auto k=line.find("if");
            if(k!=string::npos){
                ++counter;
            }
        }
    }
    public:
    struct mapElement{
        string name;
        int complex;
        mapElement(string n, int c):name(n), complex(c){        }
        ~mapElement(){delete name; delete complex};
    };
    vector <string> Files = checked();
    map <string, int> Complexity = cyclomatic(Files);

    

};
