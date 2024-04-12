#include <stdio.h>
#include <stdlib.h>
#define LONG1 sizeof(linkNode)
#define LONG2 sizeof(stackNode)

typedef struct linkNode
{
    int k;//k用来指示式子中的存储数据类型，1为数字，2为符号，0代表头部
    char ch;
    int num;
    struct linkNode *next;
} linkNode;

typedef struct LinkStack
{
    struct stackNode *head;
    struct stackNode *bottom;
    int level;//表示栈顶的优先级，详见函数 int level(char ch)
} LinkStack;

typedef struct stackNode
{
    char ch;
    struct stackNode *next;
} stackNode;

linkNode *transform(char str[101]);
int numberCheck(char ch);
int numberGet(char *p);
int levelGet(char ch);
void stackIn(LinkStack *stack,char ch);
void stackOut(LinkStack *stack);

int cal(linkNode *head);
int calTwo(int x,int y,char ch);



int main()
{
    char str[101];
    printf("请输入中缀表达式（暂不支持负号）\n");
    scanf("%s",str);
    getchar();

    linkNode *head=transform(str),*pNode = head->next;
    printf("转化后的后缀表达式为\n");
    for(;pNode != NULL;pNode = pNode->next)
    {
        if(pNode->k == 1)
            printf("%d ",pNode->num);
        else if(pNode->k == 2)
            printf("%c ",pNode->ch);
    }
    //free

    printf("\n运算结果是%d\n",cal(head));

    system("pause");
    return 0;
}

//把中缀表达式转后缀表达式，返回得到的链表头
linkNode *transform(char str[101])
{
    //创建链表，创建栈
    linkNode *linkHead = malloc(LONG1),*p1 = linkHead,*p2;//p2用于创建新节点
    linkHead->k = 0,linkHead->next = NULL;

    LinkStack *stack=malloc(sizeof(LinkStack));
    stack->bottom = malloc(LONG2),stack->bottom->next = NULL,stack->bottom->ch = 0;
    stack->head = stack->bottom;
    stack->level = 0;
    stackNode *p;

    for(int i = 0;str[i] != 0;i++)
    {
        // printf("第%d次循环，str[%d]=%c\n",i+1,i,str[i]);
        if(numberCheck(str[i]) == 1)//数字直接入式
        {//链表
            // printf("str[i]被识别为数字\n");
            p2 = malloc(LONG1);
            p2->k = 1,p2->num = numberGet(str+i);
            p1->next = p2,p2->next = NULL,p1 = p2;

            while(numberCheck(str[i + 1]) == 1)
                i++;//跳过这一串数字
        }
        else if(str[i] == '(')//左括号直接入栈
        {
            // printf("str[i]被识别为左括号\n");
            stackIn(stack,str[i]);
        }
        else if(str[i] == ')')//右括号循环出栈
        {
            // printf("str[i]被识别为右括号\n");
            while(stack->head->ch != '(')//出栈入式直到'('
            {
                //入式
                p2 = malloc(LONG1),p1->next = p2,p2->next = NULL;
                p2->k = 2,p2->ch = stack->head->ch;
                p1 = p2;

                stackOut(stack);//出栈
            }
            p = stack->head;
            stack->head = stack->head->next;
            stack->level = levelGet(stack->head->ch);//更新优先级
            free(p);
        }
        else//运算符做优先级判断
        {
            // printf("str[i]被识别为运算符\n");
            while(levelGet(str[i]) <= stack->level)
            {
                //入式
                p2 = malloc(LONG1),p1->next = p2,p2->next = NULL;
                p2->k = 2,p2->ch = stack->head->ch;
                p1 = p2;

                //出栈
                stackOut(stack);
            }

            stackIn(stack,str[i]);//入栈
        }
    }

    //全部出栈
    for(;stack->head != stack->bottom;)
    {
        //入式
        p2 = malloc(LONG1),p1->next = p2,p2->next = NULL;
        p2->k = 2,p2->ch = stack->head->ch;
        p1 = p2;

        //出栈
        stackOut(stack);
    }
    free(stack->bottom),free(stack);

    return linkHead;
}

int numberCheck(char ch)
{
    if(ch>='0' && ch<='9')
        return 1;
    else
        return 0;
}

//读取连在一起的一串数字
int numberGet(char *p)
{
    int num = 0;
    for(;numberCheck(*p) == 1;p++)
    {
        num = num*10 + (*p-'0');
    }
    return num;
}

//获取 + - * / ( 中任意一个，返回其优先级
int levelGet(char ch)
{
    if(ch == '+' || ch == '-')
        return 1;
    else if(ch == '*' || ch == '/')
        return 2;
    else if(ch == '(' || ch == 0)
        return 0;
    else{
        printf("你看看你把啥玩意儿——%c——塞进 int levelGet(char ch) 里来了\n"
            "保存一下输入数据准备调bug吧你\n",ch);
        system("pause");
        exit(0);
    }
}

//入栈函数
void stackIn(LinkStack *stack,char ch)
{
    //新建节点
    stackNode *p = malloc(LONG2);
    p->next = stack->head,stack->head = p;

    //添加数据
    p->ch = ch;
    stack->level = levelGet(ch);//更新栈顶优先级

    return;
}

//去掉栈顶的一个节点
void stackOut(LinkStack *stack)
{
    stackNode *p = stack->head;
    stack->head = stack->head->next;
    stack->level = levelGet(stack->head->ch);
    free(p);

    return;
}

//计算后缀表达式
int cal(linkNode *head)
{
    linkNode *pNode,*pfree;

    for(pNode = head->next;head->next->next != NULL;pNode = head->next)
    {//每次都从头开始
        for(;1;pNode=pNode->next)
        {
            if(pNode->k == 1 &&
                pNode->next->k == 1 &&
                pNode->next->next->k == 2)
            {
                //开始运算
                pNode->num = calTwo(pNode->num,pNode->next->num,pNode->next->next->ch);
                pfree = pNode->next,pNode->next = pNode->next->next->next;
                free(pfree->next),free(pfree);
                break;
            }
        }
    }

    return pNode->num;
}

//计算两数运算的结果
int calTwo(int x,int y,char ch)
{
    int ans = 0;
    switch (ch)
    {
        case '+':
            ans = x+y;
            break;

        case '-':
            ans = x-y;
            break;

        case '*':
            ans = x*y;
            break;

        case '/':
            ans = x/y;
            break;    
    
        default:
            printf("函数int calTwo(int x,int y,char ch)发生错误\n");
            system("pause");
            break;
    }
    return ans;
}
