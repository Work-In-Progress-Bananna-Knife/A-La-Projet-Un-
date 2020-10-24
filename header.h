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
void IsSourceFile(stringNode * H, vector<string>  NotSystem);

#pragma endregion

void Contains(string Line,vector<string> Ours);
void Connections(string FileName,vector <string> NotSystem);
