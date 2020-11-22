#pragma once
    
    //deklaracja include uizywanych w danym pliku naglowkowym

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;
    //ContainDeclarations

//czuję wstyd no ale co zrobisz no :/
int main(void);
    //region deklaracji wezla string oraz fukcji z nim zwiazanych
#pragma region Node

class stringNode{

    public:
    stringNode* next;
    std::string val;
    int val1=1;
};

void Add(stringNode * & H, std::string x);
void Show(stringNode * H);
string GetX(stringNode * & H, int x);
int CheckIfInNode(string word, stringNode * H);
bool FindCharInString(string a, char b);
bool CheckIfIn(string a, stringNode * H);
int where(string word, stringNode * H);
int howManyTimes(string word, stringNode * H);
#pragma endregion


    //region deklaracji funckji wyszukujacych polaczenia fizyczne w plikach - include 
#pragma region File dependencys

void IsSourceFile(stringNode * H, vector<string>  NotSystem);
void Contains(string Line,vector<string> Ours);
void Connections(string FileName,vector <string> NotSystem, string file);
void WriteRunBashFile(string name);

#pragma endregion


    //region deklaracji funckji szukajacych logicznych polaczen miedzy funckjami
#pragma region functions dependencys

void GetFunNode(stringNode * & H, string a);
void StoryTwo(stringNode * & H, stringNode * &fun);
void FunConnections(string FileName, stringNode * & functions);

#pragma endregion



void DrawGv(vector<stringNode*> v);
void CheckAndAddVector(vector<stringNode*> & v, string head, string connection);