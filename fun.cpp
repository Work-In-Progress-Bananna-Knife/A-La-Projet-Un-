#include "header.h"
using namespace std;
class stringNode{

    public:
    stringNode* next;
    std::string val;
};

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