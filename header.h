#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;


#pragma region Node
class stringNode;
void Add(stringNode * & H, std::string x);
void Show(stringNode * H);
string GetX(stringNode * & H, int x);
int CheckIfInNode(string word, stringNode * H);
#pragma endregion

#pragma region File dependencys
void IsSourceFile(stringNode * H, vector<string>  NotSystem);
void Contains(string Line,vector<string> Ours);
void Connections(string FileName,vector <string> NotSystem);
#pragma endregion

#pragma region functions dependencys
void GetFunNode(stringNode * & H);


#pragma endregion
bool FindCharInString(string a, char b);
void FunConnections(string FileName, stringNode * & functions);