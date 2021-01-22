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
        vector <std::string> FilesInAFolder = StoryEight::AddFilesWithSourceCode("E:\\GitHub\\A-La-Projet-Un-");
        cout << "Test funkcji po wrzuceniu plikow." << endl << endl;
        for(int i=0; i<FilesInAFolder.size();++i){
            cout << FilesInAFolder[i] <<endl;
            //FilesInAFolder.size == 0
        }

        cout << "Test funkcji po usunieciu zlych typow plikow." << endl << endl;
        StoryTwo::RemoveWrongTypeOfFile(FilesInAFolder); //Właściwie, to może bez tej funkcji się obejdzie
        //stworzyć kontener danych zawierający każdą deklarację funkcji oraz informację ile ta funkcja ma warunków
        cout << "Test 1" <<endl;
        
        for(int i=0; i<FilesInAFolder.size(); ++i){   
            //ifstream fileToExamine;     
            //fileToExamine.open(FilesInAFolder[i]);
            ifstream fileToExamine(FilesInAFolder[i]); 
            if(fileToExamine.is_open()){
                cout << "plik otwarty" << endl;
            }
            else{
                cout <<" plik nie jest otwarty" << endl;
            }
            cout << FilesInAFolder[i] << endl;
            while(!fileToExamine.std::ios::eof()){
                //wyszukaj nazwę funkcji i dodaj ją gdzieś
                //dla danej nazwy funkcji wyszukaj ilość wystąpień komend warunkowych
                cout << "Test 3.1" <<endl;  
                GetFunctionNameWithConditionals(fileToExamine,cyclomaticMap,FilesInAFolder[i]);   
                cout << "Test 3.2" <<endl;          
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
                cout << "Test 4" <<endl;         
                std::string name = StoryTwo::ReverseGetWordFromX(linePosition,location);
                if((name != "if") && (name != "while") && (name != "for") && (name != "switch") && (name != "") && (name != "\'")&& (name != "\"")){
                    location = StoryTwo::BracesSkip(linePosition,location);
                    cout << "Test 5" <<endl;
                    if(linePosition[location+1] == '{'){
                        functionName = name;
                        cout << "Test 6" <<endl;
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
        int counterOfConditionals = 0;
        size_t where;
        startLineNumber++;
        std::string LookFor="(";
        std::string conditionalName[8] = { "for(" , "while(" , "if(" , "else(" , "else if" , "case ", "&&" , "||" } ;
        cout << "Test 7" <<endl;
        while(openBrackets != closedBrackets){
            cout << "Test 8" <<endl;
            for(int i=0;i<8;++i){
                cout << "Test 9" <<endl;
                size_t comparisonValue = line.find(conditionalName[i]);
                if((comparisonValue!=std::string::npos)){
                    cout << "Test 10" <<endl;
                    if(line[comparisonValue-1] != '\"' && line[comparisonValue-1]!= '\''){
                            cout << "Test 11" <<endl;
                            counterOfConditionals++;
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
            }
            getline(File,line);
            startLineNumber=0;
        }
        map<std::string, int> cyclomaticInfo;
        cyclomaticInfo.insert({functionName,counterOfConditionals});
        connectionsMap.insert({fileName,cyclomaticInfo});
    }

    static void PrintConnectionMapContents(map <std::string, map <std::string, int> > connectionMap){
        //for(auto iter = connectionMap.begin(); iter != connectionMap.end(); ++iter){
        //    std::cout << iter->first << " : ";
        //    map < std::string, int> const &internalMap;
        //    for(auto iter2 = internalMap.begin(); iter2!= internalMap.end(); ++iter2){
        //        cout<< iter2->first << " : " << iter2->second;
        //    }
        //}
        
        for(map<string, map<string, int>>::iterator it = connectionMap.begin(); it != connectionMap.end(); ++it){
            cout << it-> first << " : ";
            map<string, int> &internal_map = it->second;
            for(map<string,int>::iterator it2=internal_map.begin(); it2 != internal_map.end(); ++it){
                cout << it2->first << ":" << it2->second;
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
                    cout<< "working"<< endl;
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
    
    /*    vector <string> checked(){
            vector <string> Files=StoryOne::Files();
            for(int i=0;i<Files.size();++i){
                if(!((Files[i][Files[i].size()-1] == 'h' && Files[i][Files[i].size()-2] == '.' ) || (Files[i][Files[i].size()-1] == 'p' && Files[i][Files[i].size()-2] == 'p' && Files[i][Files[i].size()-3] == 'c' && Files[i][Files[i].size()-4] == '.') )){
                    Files.erase(Files.begin()+i);
                    --i;
                }
            }
            return Files;
        }
    */
    //na pojedynczych plikach wywoluje analize cyklometrycznej zlozonosci danego pliku oraz funkcji w niej zawartych wynik to mapa funkcja - zlozonosc
    /*
    static map<string, int> cyclomatic(vector<string> Files){
        ifstream analyze;
        for(int i=0;i<Files.size();++i){
            analyze.open(Files[i]);
            mapElement point = FunctionComplexicity(analyze);
        }
    }
    */
    //do rozbudowania o wykluczanie zakomentowanych obszarow na razie liczy ify w plikach cpp i h tez kozak ale no... jeszcze trzeba funckje ogarnac xd HF <3
    /*
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
    */
    

};
