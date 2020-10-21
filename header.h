#pragma once

#include<iostream>


#pragma region Node
//definitions of oour functions and structures
class stringNode;
void Add(stringNode * & H, std::string x);
void Show(stringNode * H);
void IsSourceFile(stringNode * H, vector<string>  NotSystem);

#pragma endregion


void IsSourceFile(stringNode * H, vector<string>  NotSystem);

