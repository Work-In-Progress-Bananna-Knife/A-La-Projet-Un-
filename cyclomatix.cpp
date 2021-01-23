#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "class.h"

using namespace std;

class StoryEight : public StoryOne{
    //Cała złożoność cyklomatyczna będzie wydzielona do osobnego pliku
    public:
    
    //Metoda obliczająca złożoność cyklomatyczną - pomysł Michała
    static void CyclomaticComplexityOfAFunction(map <std::string, map <std::string, int> > &cyclomaticMap){
        vector <std::string> FilesInAFolder = StoryEight::AddFilesWithSourceCode("E:\\GitHub\\A-La-Projet-Un-\\"); //dla linuxa usunąć argument
        cout << "W kontenerze danych znadują się następujące pliki:" << endl << endl;
        for(int i=0; i<FilesInAFolder.size();++i){
            cout << FilesInAFolder[i] <<endl;
        }
        //StoryTwo::RemoveWrongTypeOfFile(FilesInAFolder); //Właściwie, to może bez tej funkcji się obejdzie
        //stworzyć kontener danych zawierający każdą deklarację funkcji oraz informację ile ta funkcja ma warunków
        cout << "Test 1. Wypisywanie wyszukanych funkcji " <<endl;
        std::string path = "E:\\GitHub\\A-La-Projet-Un-\\";
        for(int i=0; i<FilesInAFolder.size(); ++i){   
            //ifstream fileToExamine;     
            //fileToExamine.open(FilesInAFolder[i]);
            ifstream fileToExamine;
            FilesInAFolder[i]=path+FilesInAFolder[i];
            fileToExamine.open(FilesInAFolder[i]); 
            cout << FilesInAFolder[i] << endl;
            while(!fileToExamine.std::ios::eof()){
                //wyszukaj nazwę funkcji i dodaj ją gdzieś
                //dla danej nazwy funkcji wyszukaj ilość wystąpień komend warunkowych
                GetFunctionNameWithConditionals(fileToExamine,cyclomaticMap,FilesInAFolder[i]);   
                cout << endl;          
            }          
        }
    }

    static void GetFunctionNameWithConditionals(ifstream &File, map<std::string,map<std::string, int> > & connectionsMap, std::string fileName){
        std::string functionName;
        std::string linePosition;
        while(!File.std::ios::eof()){            
            std::getline(File,linePosition);            
            std::string LookFor="(";            
            size_t location=linePosition.find(LookFor);
            //cout << location << endl;
            //cout << linePosition<< endl;
            if(location!=std::string::npos){
                //cout << "Test 4" <<endl;         
                std::string name = StoryTwo::ReverseGetWordFromX(linePosition,location);
                if((name != "if") && (name != "while") && (name != "for") && (name != "switch") && (name != "") && (name != "\'")&& (name != "\"")){
                    location = StoryTwo::BracesSkip(linePosition,location);
                    //cout << "Test 5" <<endl;
                    if(linePosition[location+1] == '{'){
                        functionName = name;
                        //cout << "Test 6" <<endl;
                        cout << linePosition << endl;
                        lookForAndAddConditionals(File,connectionsMap,linePosition,fileName,location+1,functionName);                        
                    }
                }                
            }
        }
    } 

    
    // File - plik który przeszukujesz
    // connectionsMap - mapa do której chcesz wrzucać wyniki
    // line - linia (z getline) od której szukasz
    // startLineNumber - miejsce w linii od którego szukasz
    // functionName - nazwa funkcji którą przeszukujesz
    static void lookForAndAddConditionals(ifstream &File, map<std::string,map<std::string, int> > & connectionsMap, std::string line, std::string fileName, int startLineNumber, std::string functionName){
        int openBrackets = 1; 
        int closedBrackets = 0; 
        int counterOfConditionals = 1;
        size_t where;
        startLineNumber++;
        std::string LookFor="(";
        std::string conditionalName[8] = { "for(" , "while(" , "if(" , "else(" , "else if" , "case ", "&&" , "||" } ;
        //cout << "Test 7" <<endl;
        getline(File,line);
        while(openBrackets != closedBrackets){
            //cout << "Test 8" <<endl;
            for(int i=0;i<8;++i){
                //cout << "Test 9" <<endl;
                size_t comparisonValue = line.find(conditionalName[i]);
                if((comparisonValue!=std::string::npos)){
                    //cout << "Test 10" <<endl;
                    if(line[comparisonValue-1] != '\"' && line[comparisonValue-1]!= '\''){
                            //cout << "Test 11" <<endl;
                            counterOfConditionals++;
                    }                        
                }
            }    
            for(int i=startLineNumber; i<line.size(); i++){
                startLineNumber=i;
                if((line[i] == '{')&&(line[i-1] !='\'')){
                    openBrackets++;
                }                    
                else if((line[i] == '}')&&(line[i-1] != '\'')){
                    closedBrackets++;
                }
            }            
            getline(File,line);
            startLineNumber=0;
        }
        //map<std::string, int> cyclomaticInfo;
        //cyclomaticInfo.insert({functionName,counterOfConditionals});
        //connectionsMap.insert({fileName,cyclomaticInfo});

        ehhhhAdd(connectionsMap,fileName,functionName,counterOfConditionals);


    }

    static void PrintConnectionMapContents(map <std::string, map <std::string, int> > connectionMap){
        for(map<string, map<string, int>>::iterator it = connectionMap.begin(); it != connectionMap.end(); ++it){
            cout << it-> first << " : ";
            map<string, int> internal_map = it->second;
            for(map<string,int>::iterator it2=internal_map.begin(); it2 != internal_map.end(); ++it2){
                cout << it2->first << ":" << it2->second;
                cout<< endl;
            }
            cout << endl;
        }
    }

    static vector<std::string> AddFilesWithSourceCode(const char * directory = "."){
        DIR *workingDirectory;
        vector <std::string> listOfFiles;
        struct dirent *file;
        if(workingDirectory = opendir(directory)){
            while(file = readdir(workingDirectory)){
                if(CheckIfValidExtension(file->d_name) == true){
                    listOfFiles.push_back(file->d_name);
                }
            }
        }
        closedir(workingDirectory);
        return listOfFiles;
    }

    static bool CheckIfValidExtension(const string& fileName){
        size_t extensionPosition = fileName.rfind('.');
        if(extensionPosition == string::npos){
            return false;
        }
        string extension = fileName.substr(extensionPosition+1);
        if(extension == "cpp" || extension == "h"){
            return true;
        }
        return false; //jesli wszystko szlak trafi 
    }

static void ehhhhAdd( map<std::string,map<std::string, int> > & connectionMap, std::string name, std::string conta, int conditionalsNumber){
        bool exist1 = false;
        bool exist2 = false;
        map<std::string,map<std::string, int> >::iterator itr;
        for(itr = connectionMap.begin(); itr != connectionMap.end(); ++itr){
            if(itr->first == name){
                exist1 = true;
                map<std::string,int>::iterator itr2;
                for(itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2){
                    if(itr2->first == conta){

                        itr->second.erase(conta);
                        itr->second.insert({conta,conditionalsNumber});
                        return;
                        exist2 = true;
                    }
                }
                if(!exist2){
                    itr->second.insert({conta,conditionalsNumber});
                    return;
                }
            } 
        }
        if(!exist1){
            map<std::string, int> a;
            a.insert({conta, conditionalsNumber});
            connectionMap.insert({name,a});
            return;
        }
    }

    static void GenerateCycloGraph(map <std::string, map <std::string, int> > connectionMap)
    {
        ofstream file;
        std::string path = "E:\\GitHub\\A-La-Projet-Un-\\";
        file.open("E:\\GitHub\\A-La-Projet-Un-\\Data.gv");
        file<<"digraph foo{\n";
        map<std::string,map <std::string, int> >::iterator itr;
        for(itr = connectionMap.begin(); itr != connectionMap.end(); ++itr)
        {
            map<std::string, int >::iterator itr2;
            for(itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2)
            {
                file<<"\""<<itr->first<<"\""<<"->"<<"\""<<itr2->first<<"\""<<"[label = \""<<itr2->second<<"\"];\n";

            }
        }
        file<<"}";
        file.close();
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
    
};
