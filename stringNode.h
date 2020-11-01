#pragma once
#include "header.h"


void Add(stringNode * & H, std::string x){
    stringNode *p = new stringNode;
    p->val=x;
    p->next=H;
    H=p;
}


void Show(stringNode * H){
    cout<<"H->";
    stringNode *p=H;
    while(p!=NULL){
        cout<<p->val<<"->";
        p=p->next;
    }
    cout<<"NULL"<<endl;
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


bool FindCharInString(string a, char b){

    for(int i = 0;i<a.size();i++){
        if(a[i]==b){
            return true;
        }
    }
    return false;
}
