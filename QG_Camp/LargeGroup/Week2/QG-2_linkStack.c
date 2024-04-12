#include <stdio.h>
#include <stdlib.h>
#define LONG sizeof(stackNode)

//定义栈的节点
typedef struct stackNode
{
    int data;
    struct stackNode *next;
} stackNode;

typedef struct LinkStack
{
    stackNode *head;//栈的头部
    int num;//栈的结点个数
}LinkStack;

void menu(void);
LinkStack *stackCreate(void);
void stackAdd(LinkStack *pStack,int num);
void stackPrint(LinkStack *pStack);
void stackDelete(LinkStack *pStack);
void stackFree(LinkStack *pStack);



int main()
{
    menu();
    system("pause");
}

void menu(void)
{
    LinkStack *pStack=stackCreate();
    printf("栈已创建并赋初值\n");

    int k;
    while (1)
    {
        for(int i=0;i<30;i++)//打印分割线
            printf("=");
        printf("\n");


        printf("1   显示栈的内容\n"
            "2  增加元素（入栈）\n"
            "3  删除顶端元素（出栈）\n"
            "other  退出\n"
            "请输入你要执行的操作\n");
        scanf("%d",&k);
        getchar();

        int num;
        switch (k)
        {
        case 1:
            stackPrint(pStack);
            break;
        case 2:
            printf("请输入你要增加的数字");
            scanf("%d",&num);
            getchar();
            stackAdd(pStack,num);
            break;
        case 3:
            stackDelete(pStack);
            break;
        default:
            stackFree(pStack);
            printf("退出,栈的内存已释放\n");
            return;
            break;
        }
    }
    
    return;
}

LinkStack *stackCreate(void)
{
    LinkStack *pStack=malloc(sizeof(LinkStack));
    pStack->num=0,
    pStack->head=malloc(LONG);

    pStack->head->data=1,
    pStack->head->next=NULL,
    pStack->num++;

    stackAdd(pStack,2);
    stackAdd(pStack,3);

    return pStack;
}

//入栈，向栈顶添加元素
void stackAdd(LinkStack *pStack,int num)
{
    stackNode *p=malloc(LONG);
    p->data=num;
    p->next=pStack->head;

    pStack->head=p;
    pStack->num++;

    return;
}

//显示栈的内容
void stackPrint(LinkStack *pStack)
{
    if(pStack->head == NULL){
        printf("栈已空，请再次打开程序或增加栈的结点\n");
        system("pause");
        return;
    }
    stackNode *p=pStack->head;
    printf("\n栈的内容（head->bottom）\n");
    for(;p!=NULL;p=p->next)
        printf("%d->",p->data);
    
    printf("NULL\n");
    return;
}

//出栈：删掉栈顶的那个节点
void stackDelete(LinkStack *pStack)
{
    if(pStack->head == NULL){
        printf("栈已空，请再次打开程序或增加栈的结点\n");
        system("pause");
        return;
    }
    stackNode *p=pStack->head;
    pStack->head=pStack->head->next,
    pStack->num--;
    free(p);

    printf("出栈完成,内存已释放\n");
    return;
}

//释放栈的内存
void stackFree(LinkStack *pStack)
{
    if(pStack->head == NULL)
    {
        printf("栈已为空，不需要释放了\n输入任意键以退出程序\n");
        system("pause");
        exit(0);
    }
    stackNode *p=pStack->head,*pFree;
    for(pFree=p,p=p->next;p!=NULL;pFree=p,p=p->next)
        free(pFree);
    free(pFree);
    free(pStack);
    return;
}