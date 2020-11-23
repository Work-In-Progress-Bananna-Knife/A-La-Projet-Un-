#pragma once
#include "header.h"
//ContainDefinitions

void Add(stringNode * & H, std::string x){
    stringNode *p = new stringNode;
    p->val=x;
    p->next=H;
    H=p;
}


void AddSecond(stringNode * & H, std::string x){
    if(H){
        stringNode *p = new stringNode;
        p->val=x;
        p->next=H->next;
        H->next=p;
    }
    else
        Add(H,x);

}


void Show(stringNode * H){
    std::cout<<"H->";
    stringNode *p=H;
    while(p!=NULL){
        std::cout<<p->val<<"->";
        p=p->next;
    }
    std::cout<<"NULL"<<endl;
}


string GetX(stringNode * & H, int x){

    int a=0;
    stringNode *p = H;
    while(p!=NULL){
        if(a == x){
            return p->val;
        }
            p = p->next;
            a++;
    }
    return "ERROR";
}


bool FindCharInString( std::string a, char b){

    for(int i = 0;i<a.size();i++){
        if(a[i]==b){
            return true;
        }
    }
    return false;
}


bool CheckIfIn( std::string a, stringNode * H){

     while(H!=NULL){
     
         if(a == H->val){
             return true;
         }
        H=H->next;
    }
    return false;
}


int where( std::string word, stringNode * H){

    int a=-1;
    while(H!=NULL){
        a++;
        if(word == H->val){
            return a;
        }
        H=H->next;
    }
    return -1;
}


int howManyTimes( std::string word, stringNode * H){
    
    int a=0;
    while(H != NULL){
        if(word == H->val){
            a++;
        }
        H=H->next;
    }
    return a;
}