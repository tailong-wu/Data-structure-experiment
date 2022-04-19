
// 输入一个命令，命令可能是以下的字符串： 
//Insert List Find Chang Delete Quit Exit 输入Quit或Exit命令后，程序结束。 
// 最后一个命令一定是Quit或Exit。
// 输出相应的字符串， 具体如下
//  Insert 在单独一行中输出"Insert:"
// List 在单独一行中输出"List:"
// Find 在单独一行中输出"Find:" 
// Change 在单独一行中输出"Change:"
// Delete 在单独一行中输出"Delete:" 
// Quit或者Exit 在单独一行中输出"Good bye!"后结束程序。

#include <bits/stdc++.h>
using namespace std;
int main()
{
    char order[10];
    while(1)
    {
        scanf("%s",&order);
        switch(order[0]){
        case 'I':
            printf("Insert:\n");
            break;
        case 'L':
            printf("List:\n");
            break;
        case 'C':
            printf("Change:\n");
            break;
            
        case 'F':
            printf("Find:\n");
            break;
        case 'D':
            printf("Delete:\n");
            break;
        case 'Q':
        case 'E':
            printf("Good bye!\n");
            exit(0);
        }
    }
    return 0;
}







