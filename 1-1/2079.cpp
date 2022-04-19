 
 //  学生信息包括学号、姓名、性别、语文、数学、英语。
// 插入学生信息：
//   Insert id name sex x y z 其中的参数分别为学号、姓名、性别、三门课的成绩，成绩为浮点数。
// 输出所有学生信息：
//   List
// 按照插入的顺序输出所有学生的信息，每行一位学生的信息。每行的格式如下：
//  id name sex x y z
// 数据之间有一个空格分隔，成绩保留1位小数。
// 查找学生信息：
//   Find id
// 查找学号为id的学生信息。
// 退出程序：
//   Quit或者Exit
#include <bits/stdc++.h>
using namespace std;
typedef struct Student {
    char id[20];
    char sex;
    char name[20];
    double score[3];
    double sum;
    struct Student *next;
}Student;

void inputSingle(Student *s)
{
    scanf("%s %s %c",s->id,s->name,&s->sex);
    for (int j = 0 ;j<3;j++){
        scanf("%lf",&s->score[j]);
    }
}

void outputSingle(Student *s){
    printf("%s %s %c",s->id,s->name,s->sex);
    for (int j = 0 ;j<3;j++){
        printf(" %.1lf",s->score[j]);
    }
    printf("\n");
}


Student *createList(){
    Student *L;
    L = (Student*)malloc(sizeof(Student));
    L->next = NULL;
    return L;
}
 
void insertTail(Student *L,Student *s){
    Student *pre ,*p;
    pre = L;
    p = L->next;
    while (p!=NULL){
        pre = p;
        p = p->next;
    }
    s->next = pre->next;
    pre->next= s;
}


void List(Student *L,Student *s){
    s = L->next;
    while (s!= NULL){
        outputSingle(s);
        s = s->next;
    }
}


void Find(Student *L){
    char id[10];
    int flag = 0;
    scanf("%s",id);
    Student *p;
    p = L->next;
    while (p!= NULL){
        if(strcmp(p->id ,id)== 0 ){
            flag = 1;
            break;
        }
        p = p->next;
    }
    if (flag == 0) printf("Failed\n");
    else outputSingle(p);
}

int main()
{
    char order[10];
    Student *L,*s;
    L = createList();
    while (1)
    {
        scanf("%s",order);
        switch(order[0])
        {
            case 'I':
                printf("Insert:\n");
                s = (Student*)malloc(sizeof(Student));
                inputSingle(s);
                outputSingle(s);
                insertTail(L,s);
                break;
            case 'L':
                printf("List:\n");
                List(L,s);
                break;
            case 'F':
                printf("Find:\n");
                Find(L);
                break;
            case 'Q':
            case 'E':
                printf("Good bye!\n");
                exit(0);
        }
    }
    return 0;
}







