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
    int freq;
    Node(int afreq=0,char ac='\0',Node* aleft=NULL,Node* aright=NULL,Node* aparent=NULL) {
        left=aleft;
        right=aright;
        parent=aparent;
        freq=afreq;
        c=ac;
    }
} Node,*pNode;
struct cmp {
    bool operator()(pNode node1, pNode node2) {
        return node1->freq > node2->freq;
    }
};

typedef struct Ans {
    char c;
    string code;
} Ans;
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
void Print(pNode root,string str) {
    if(root==NULL) {
        return ;
    }
    if(root->left) {
        str+='0';
        Print(root->left,str);
    }
    if(root->left==NULL&&root->right==NULL) {
        cout<<root->c<<"‘s code: "<<str<<endl;
        Ans one;
        one.c=root->c;
        one.code=str;
        ans.push_back(one);
    }
    str.erase(str.end()-1);
    if(root->right) {
        str+='1';
        Print(root->right,str);
    }

}
int charFreq[300];
int main() {
    freopen("in.txt","r",stdin);
    string str;
    string article;
    char art;
    int n=0;
    while(~scanf("%c",&art)) {
        article+=art;
        if(charFreq[art]==0)
            n++;
        charFreq[art]++;
    }
    for(int i=0; i<300; i++) {
        int freq;
        char s[10];
        if(charFreq[i]==0)continue;
        freq=charFreq[i];
        s[0]=i;
        pNode now=new Node(freq,s[0]);
//printf("freq:%d\n",now->freq);
        q.push(now);
    }
    pNode root=Huffman(n);
    Print(root,str);
    fstream ofile("out.txt");
    for(int i=0; i<n; i++) {
        string c;
        c+=ans[i].c;
        c+="'s code:";
        c+=ans[i].code;
        c+='\n';
        ofile<<c;
    }
    ofile.close();
    fstream code("code.txt");
    for(int i=0; i<article.length(); i++) {
        for(int j=0; j<ans.size(); j++) {
            if(ans[j].c==article[i]) {
                code<<ans[j].code;
            }
        }
    }
    code.close();
    fstream table("table.txt");
    for(int i=0; i<n; i++) {
        string c;
        c+=ans[i].c;
        c+=ans[i].code;
        c+=' ';
        table<<c;
    }
    table.close();
    return 0;
}
