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


#pragma endregion

#pragma region Dependencys
void IsSourceFile(stringNode * H, vector<string>  NotSystem);
void Contains(string Line,vector<string> Ours);
void Connections(string FileName,vector <string> NotSystem);
#pragma endregion