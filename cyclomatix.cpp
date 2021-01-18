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
        vector <std::string> FilesInAFolder = StoryOne::Files();
        StoryTwo::RemoveWrongTypeOfFile(FilesInAFolder);
        //stworzyć kontener danych zawierający każdą deklarację funkcji oraz informację ile ta funkcja ma warunków
        map <std::string, map <std::string, int> >;
        ifstream fileToExamine;
        for(int i=0; i<FilesInAFolder.size(); ++i){        
            fileToExamine.open(FilesInAFolder[i]);
            while(!fileToExamine.std::ios::eof()){
                //wyszukaj nazwę funkcji i dodaj ją gdzieś
                GetFunctionName(fileToExamine);
                //dla danej nazwy funkcji wyszukaj ilość wystąpień komend warunkowych
                //jeśli znajdziesz, to 
            }
        }
    //przejdź do danej funkcji (potocznie)
    }

    static std::string GetFunctionName(ifstream &File){
        std::string functionName;
        std::string linePosition;
        while(!File.std::ios::eof()){
            getline(File,linePosition);
            std::string LookFor="(";
            size_t location=linePosition.find(LookFor);            
            if(location!=std::string::npos){            
                std::string name = StoryTwo::ReverseGetWordFromX(linePosition,location);
                if((name != "if") && (name != "while") && (name != "for") && (name != "switch") && (name != "") && (name != "\'")&& (name != "\"")){
                    location = StoryTwo::BracesSkip(linePosition,location);
                    if(linePosition[location+1] == '{'){
                        functionName = name;
                        searchForFunctionNameAndConditionals();                        
                    }
                }
                
            }
        }
        return functionName;
    } 

    
    static void searchForFunctionNameAndConditionals(ifstream &File, map<std::string,map<std::string, int> > & connectionsMap, std::string line, int startLineNumber, std::string functionName){
        int openBrackets = 1; 
        int closedBrackets = 0; 
        int counter;
        size_t where;
        startLineNumber++;
        std::string LookFor="(";
        std::string blabla[6] = { "for(" , "while(" , "if(" , "else(" , "else if" , "case "} ;
        while(openBrackets != closedBrackets){
            for(int i=startLineNumber; i<line.size(); i++){
                startLineNumber=i;
                if((line[i] == '{')&&(line[i-1] !='\'')){
                    openBrackets++;
                }                    
                else if((line[i] == '}')&&(line[i-1] != '\'')){
                    closedBrackets++;
                }
                getline(File,line);
                for(int i=0;i<6;++i){
                    if((line.find(blabla[i]))){
                        counter++;
                    }
                }
            }
            getline(File,line);
            startLineNumber=0;
        }
    }

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
    



    //Pomysł Bartka
    //usuwa elementy innego typu niz zalozone cpp lub header z vectora listy elementow w folderze
    
        vector <string> checked(){
            vector <string> Files=StoryOne::Files();
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
