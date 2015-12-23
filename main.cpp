#include <stdio.h>
#include <vector>
#include <queue>
#include <stdlib.h>
#include <iostream>
#include <stack>
#include <string>
#include <ostream>
#include<fstream>
#define SIZE 4
using namespace std;

typedef struct Node {
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    int flag;
    char c;
    double freq;
    Node(int freq=0,char cao='\0',Node* left=NULL,Node* right=NULL,Node* parent=NULL) {
        left=left;
        right=right;
        parent=parent;
        freq=freq;
        c=cao;
    }
} Node,*pNode;
struct cmp{
    bool operator()(pNode node1, pNode node2){
        return node1->freq < node2->freq;
    }
};

typedef struct Ans{
    char c;
    string code;
}Ans;
priority_queue<pNode,vector<pNode>,cmp > q;
vector<Ans> ans;
pNode Huffman(int n) {
    pNode l,r;
    for(int i=0; i<n-1; i++) {
        pNode p=new Node();
        l=q.top();
        q.pop();
        r=q.top();
        q.pop();
        p->freq=l->freq+r->freq;
        p->left=l;
        p->right=r;
        l->parent=p;
        l->flag=0;
        r->flag=1;
        r->parent=p;
        q.push(p);
    }
    return q.top();
}
void Print(pNode root,string str){
    if(root==NULL){
        return ;
    }
    if(root->left){
            str+='0';
        Print(root->left,str);
    }
    if(root->left==NULL&&root->right==NULL){
        cout<<root->c<<"‘s code: "<<str<<endl;
Ans one;
one.c=root->c;
one.code=str;
ans.push_back(one);
    }
    str.erase(str.end()-1);
    if(root->right){
        str+='1';
        Print(root->right,str);
    }

}
int main() {
    freopen("in.txt","r",stdin);
    string str;
    int n;
    char temp;
    scanf("%d",&n);
    scanf("%c",&temp);
    for(int i=0; i<n; i++) {
        int freq;
        char s[10];

        scanf("%s %d",s,&freq);
        pNode now=new Node(freq,s[0]);

        q.push(now);
    }
    pNode root=Huffman(n);
    Print(root,str);
   fstream ofile("out.txt");
    for(int i=0;i<n;i++){
            string c;
    c+=ans[i].c;
    c+="'s code:";
    c+=ans[i].code;
    c+='\n';
    ofile<<c;
    }
    ofile.close();
    return 0;
}
