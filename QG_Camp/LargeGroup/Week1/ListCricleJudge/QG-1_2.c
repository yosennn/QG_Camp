#include <stdio.h>
#include <stdlib.h>
#define LONG sizeof(struct SingleListNode)

//结点定义
struct SingleListNode
{
    int num;
    struct SingleListNode *next;
};

struct SingleListNode *SingleListUnCricle(void);
struct SingleListNode *SingleListCricle(void);
void SingleListPrint(struct SingleListNode *head);
int SingleListJudge(struct SingleListNode *head);



int main()
{
    int k;
    struct SingleListNode *(*func)(void);//函数指针

    printf("创建一个单链表\n"
        "1  创建普通链表\n"
        "2  创建环形链表\n"
        "other  就地退出程序\n");
    scanf("%d",&k);
    getchar();

    if(k==1)//为函数指针赋值
        func=SingleListUnCricle;
    else if(k==2)
        func=SingleListCricle;
    else
        return 0;

    struct SingleListNode *head = func();//创建链表
    SingleListPrint(head);

    int n=SingleListJudge(head);//进行判断
    if(n==1)
        printf("该链表成环\n");
    else if(n==0)
        printf("该链表不成环\n");
    else
        printf("恭喜解锁bug\n");

    system("pause");
    return 0;
}

//创建一个普通的单链表
struct SingleListNode *SingleListUnCricle(void)
{
    struct SingleListNode *head,*p1;
    p1=malloc(LONG);
    p1->num=1;
    head=p1;

    p1->next=malloc(LONG);
    p1=p1->next,p1->num=2;

    p1->next=malloc(LONG);
    p1=p1->next,p1->num=3;

    p1->next=malloc(LONG);
    p1=p1->next,p1->num=4;

    p1->next=malloc(LONG);
    p1=p1->next,p1->num=5;
    p1->next=NULL;//收尾

    return head;
}

//创建一个成环的单向链表
struct SingleListNode *SingleListCricle(void)
{
    struct SingleListNode *head,*p1;
    p1=malloc(LONG);
    p1->num=1;
    head=p1;

    p1->next=malloc(LONG);
    p1=p1->next,p1->num=2;

    p1->next=malloc(LONG);
    p1=p1->next,p1->num=3;

    p1->next=malloc(LONG);
    p1=p1->next,p1->num=4;

    p1->next=malloc(LONG);
    p1=p1->next,p1->num=5;
    p1->next=head;//收尾
    return head;
}

//判断链表是否成环，成环返回1，否则返回0
int SingleListJudge(struct SingleListNode *head)
{
    struct SingleListNode *p1=head,*p2=head;
    for(;p2!=NULL&&p1!=p2
        ;p1=p1->next,p2=p2->next->next);//p1走一步，p2走两步

    //我有个想法，可以只设置一个指针 p 遍历链表，然后循环判断它是否等于head

    if(p1=p2)
        return 1;
    else
        return 0;
}

//测试函数
void SingleListPrint(struct SingleListNode *head)
{
    printf("head");
    struct SingleListNode *p=head;
    for(int k=0;p!=NULL;p=p->next,k=1)
    {
        printf("->%d",p->num);
        if(k==1&&p==head)
            break;
    }
    printf("\n");
    return;
}