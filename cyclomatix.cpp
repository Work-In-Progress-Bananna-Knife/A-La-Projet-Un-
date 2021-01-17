#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "class.h"

using namespace std;

class StoryEight : public StoryOne{
    private:
    
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
