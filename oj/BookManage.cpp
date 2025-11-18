#include <iostream>
#include<stdio.h>
#include<string>
using namespace std;

bool *books = new bool[10000001];

int findBook(int id) {
    return books[id];
}
int borrowBook(int id) {
    if (books[id]) {
        books[id]=0;
        return 1;
    }
    return 0;
}

int returnBook(int id) {
    if (books[id]) {
        return 0;
    }
    books[id]=1;
    return 1;
}

int main() {
    string result;
    int book=0,m,i,op,id;
    char c;
    while (true) {
        c = getchar();
        if (c>='0' && c<='9') {
            book = book*10+c-'0';
        }
        else if (c==' ') {
            books[book]=1;
            book=0;
        }
        else if (c=='\n'|| c=='\r') {
            break;
        }
    }
    scanf("%d",&m);
    for (int i=0;i<m;i++) {
        scanf("%d%d",&op,&id);
        switch (op) {
            case 1:result+=to_string(findBook(id));break;
            case 2:result+=to_string(borrowBook(id));break;
            case 3:result+=to_string(returnBook(id));break;
        }
    }
    cout<<result<<endl;
}