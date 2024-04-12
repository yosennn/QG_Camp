#include <stdio.h>
#include <stdlib.h>
#define LONG1 sizeof(struct SingleListNode)
#define LONG2 sizeof(struct DoubleListNode)

struct SingleListNode//单链表结点的定义
{
    int num;
    struct SingleListNode *next;
}SingleListNode;

struct DoubleListNode//双链表结点的定义
{
    struct DoubleListNode *pre;
    int num;
    struct DoubleListNode *next;
}DoubleListNode;



void menu(void);
void fenge(int num,char ch);

void SingleListADT(void);
struct SingleListNode *SingleListCreate(void);
void SingleListPrint(struct SingleListNode *head);
void SingleListAdd(struct SingleListNode *head);
void SingleListFree(struct SingleListNode *head);
void SingleListDelete(struct SingleListNode *head);
void SingleListExchange(struct SingleListNode *head);
struct SingleListNode *SingleListMid(struct SingleListNode *head);

void DoubleListADT(void);
struct DoubleListNode *DoubleListCreate(void);
void DoubleListPrint(struct DoubleListNode *head);
void DoubleListAdd(struct DoubleListNode *head);
void DoubleListFree(struct DoubleListNode *head);
void DoubleListDelete(struct DoubleListNode *head);



int main()
{
    printf("QG训练营大组第一次作业\n"
        "作者：王宥程   组别：前端\n"
        "完成情况：\n"
        "单、双链表ADT（必做）\n");

    menu();

    system("pause");
    return 0;
}

void menu()
{
    while (1)
    {
        fenge(40,'=');
        printf("1   单链表ADT & 选做功能1+2\n"
            "2  双链表ADT\n"
            "other  退出"
            "请输入一个数字进行选择\n");
        int num=0;
        scanf("%d",&num);
        getchar();

        switch (num)
        {
            case 1:
                SingleListADT();
                break;

            case 2:
                DoubleListADT();
                break;
            
            default:
                return;
                break;
        }
    }
    return;
}

//打印分割线的函数
void fenge(int num,char ch)
{
    for(int i=1;i<=num;i++)
        printf("%c",ch);
    printf("\n");
    return;
}

//进行单链表ADT操作的菜单
void SingleListADT(void)
{
    fenge(40,'=');
    struct SingleListNode *head=SingleListCreate();
    printf("单向链表已创建（为方便起见已赋初值），内容为\n");
    SingleListPrint(head);

    while(1)
    {
        printf("\n"
            "1   查看链表\n"
            "2  增加\n"
            "3  删除\n"
            "4  奇偶节点交换\n"
            "5  该链表寻找中点\n"
            "other  回到上一级\n"
            "请输入一个数字\n");
            int k=0;
            struct SingleListNode *pMid;//查找中点时要用到的指针
            scanf("%d",&k);
            getchar();
            printf("\n");
            
            switch (k)
            {
                case 1:
                    SingleListPrint(head);
                    break;
                case 2:
                    SingleListAdd(head);
                    break;
                case 3:
                    SingleListDelete(head);
                    break;
                case 4:
                    SingleListExchange(head);
                    break;
                case 5:
                    pMid=SingleListMid(head);
                    if(pMid==NULL)
                        printf("节点数为偶数，没有中点\n");
                    else
                        printf("中点为 %d\n",pMid->num);
                    break;

                default:
                SingleListFree(head);
                    return;
            }
    }
    return;
}

//创建单链表并赋初值（头结点为空）
struct SingleListNode *SingleListCreate(void)
{
    struct SingleListNode *head,*p1,*p2;
    head=malloc(LONG1);
    head->num=0;
    p2=head;

    p1=malloc(LONG1);
    p1->num=1;
    p2->next=p1;

    p1=malloc(LONG1);
    p1->num=2;
    p2=p2->next,p2->next=p1;

    p1=malloc(LONG1);
    p1->num=3;
    p2=p2->next,p2->next=p1;

    p1=malloc(LONG1);
    p1->num=123;
    p2=p2->next,p2->next=p1;

    p1=malloc(LONG1);
    p1->num=321;
    p2=p2->next,p2->next=p1;

    p1->next=NULL;
    return head;
}

//打印单向链表
void SingleListPrint(struct SingleListNode *head)
{
    head=head->next;//跳过头节点
    printf("\n链表为："
        "NULL");
    while(head!=NULL)
    {
        printf("->%d",head->num);
        head=head->next;
    }
    printf("\n\n");
    return;
}

//释放单链表占用内存
void SingleListFree(struct SingleListNode *head)
{
    struct SingleListNode *p1=head,*p2=p1->next;

    while(1)
    {
        free(p1);
        if(p2!=NULL)
            break;
        p1=p2,p2=p2->next;//p1,p2后移
    }

    return;
}

//向单链表中增添数据（尾插法）
void SingleListAdd(struct SingleListNode *p)
{
    printf("请输入你要新增的数字：");
    int n;
    scanf("%d",&n); getchar();//吸收回车

    for(;p->next!=NULL;p=p->next);//遍历到链表末尾
    p->next=malloc(LONG1);
    p=p->next;
    p->num=n,p->next=NULL;

    return;
}

//删除单链表中的某个节点
void SingleListDelete(struct SingleListNode *head)
{
    printf("请输入你要删除的数字：");
    int n;
    scanf("%d",&n);
    getchar();

    struct SingleListNode *p1=head,*p2=p1->next;

    for(;p2!=NULL;)
    {
        if(p2->num==n)
        {
            p1->next=p2->next;
            free(p2);
            p2=p1->next;
            continue;
        }
        p1=p2,p2=p2->next;
    }

    return;
}

//选做功能——奇偶节点交换
void SingleListExchange(struct SingleListNode *head)
{
    int n;
    struct SingleListNode *p=head->next;
    for(;p!=NULL&&p->next!=NULL;p=p->next->next)
    {
        n=p->num;
        p->num=p->next->num;
        p->next->num=n;
    }
    return;
}


//进行双链表ADT操作的菜单
void DoubleListADT(void)
{
    fenge(40,'=');
    struct DoubleListNode *head=DoubleListCreate();//创建链表
    printf("双向链表已创建（为方便起见已赋初值），内容为\n");
    DoubleListPrint(head);

    while(1)
    {
        printf("1   查看链表\n"
            "2   增加\n"
            "3  删除\n"
            "other  回到上一级\n"
            "请输入一个数字\n");
            int k=0;
            scanf("%d",&k);
            getchar();
            
            switch (k)
            {
                case 1:
                    DoubleListPrint(head);
                    break;
                case 2:
                    DoubleListAdd(head);
                    break;
                case 3:
                    DoubleListDelete(head);
                    break;

                default:
                    DoubleListFree(head);
                    return;
            }
    }
    return;
}

//创建双链表（头尾节点均为空）
struct DoubleListNode *DoubleListCreate(void)
{
    struct DoubleListNode *head,*p1,*p2;
    head=malloc(LONG2);
    head->pre=NULL;
    p1=head;

    p2=malloc(LONG2);
    p2->num=1;
    p2->pre=p1,p1->next=p2,p1=p2;//前后相连

    p2=malloc(LONG2);
    p2->num=22;
    p2->pre=p1,p1->next=p2,p1=p2;//前后相连

    p2=malloc(LONG2);
    p2->num=333;
    p2->pre=p1,p1->next=p2,p1=p2;//前后相连

    p2=malloc(LONG2);
    p2->pre=p1,p1->next=p2,p1=p2;
    p2->next=NULL;
    return head;
}

//打印双向链表
void DoubleListPrint(struct DoubleListNode *head)
{
    head=head->next;//跳过头节点
    printf("\n链表为：\n"
        "NULL");
    while(head->next!=NULL)
    {
        printf("->%d",head->num);
        head=head->next;
    }
    printf("->NULL\n\n");
    return;
}

//在双向链表中增加节点（尾插法）
void DoubleListAdd(struct DoubleListNode *head)
{
    printf("请输入要新增的节点内容：\n");
    int n;
    scanf("%d",&n);
    getchar();

    struct DoubleListNode *p1,*p2=head;
    while ((p2=p2->next)->next!=NULL);//使 p2 指向尾节点
    p1=p2->pre;

    p2->pre=malloc(LONG2),p2->pre->next=p2;
    p1->next=p2->pre,p1->next->pre=p1;//新增节点的连接
    p1->next->num=n;
    
    return;
}

//解除链表占用
void DoubleListFree(struct DoubleListNode *head)
{
    struct DoubleListNode *p=head->next;

    while(p->next!=NULL)
    {
        free(p->pre);
        p=p->next;
    }
    free(p);

    return;
}

//删除双链表中的某个节点
void DoubleListDelete(struct DoubleListNode *head)
{
    printf("请输入你要删除的数字：");
    int n;
    scanf("%d",&n);
    getchar();

    struct DoubleListNode *p=head;
    for(;p->next->next!=NULL;)
    {
        if(p->next->num==n)
        {
            p->next=p->next->next;
            free(p->next->pre);
            p->next->pre=p;
            continue;
        }
        p=p->next;
    }

    return;
}

//查找单链表的中点，若成功，则返回指向中点的链表，否则就返回空指针
struct SingleListNode *SingleListMid(struct SingleListNode *head)
{
    struct SingleListNode *p1=head->next,*p2=p1;//跳过头节点
    for(;p2->next!=NULL&&p2->next->next!=NULL
        ;p1=p1->next,p2=p2->next->next) ;//p1走一步，p2走两步
    if(p2->next==NULL)
        return p1;
    else
        return NULL;
}