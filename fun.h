#include "InFileIncludes.h"
#include "header.h"

using namespace std;

#pragma region stringNode class
class stringNode{

    public:
    stringNode* next;
    std::string val;
};
#pragma endregion

#pragma region Add()
void Add(stringNode * & H, std::string x){
    stringNode *p = new stringNode;
    p->val=x;
    p->next=H;
    H=p;
}
#pragma endregion 

#pragma region Show()
void Show(stringNode * H){
    cout<<"H->";
    stringNode *p=H;
    while(p!=NULL){
        cout<<p->val<<"->";
        p=p->next;
    }
    cout<<"NULL"<<endl;
}

#pragma endregion


void IsSourceFile(stringNode * H, vector<string>  NotSystem){
    stringNode *p=H;
    while(p!=NULL){

        if((p->val[p->val.size()-1]=='h' && p->val[p->val.size()-2]=='.')||(p->val[p->val.size()-1]=='p'&&p->val[p->val.size()-2]=='p'&&p->val[p->val.size()-3]=='c'&&p->val[p->val.size()-4]=='.'))
        Connections(p->val,NotSystem);
        p=p->next;
    }
}
