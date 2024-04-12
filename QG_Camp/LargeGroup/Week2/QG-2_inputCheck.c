#include <stdio.h>
#include <stdlib.h>
#define LONG sizeof(stackNode)

typedef struct stackNode
{
    int k;//k用来指示栈中的存储数据类型，1为数字，2为符号，0代表尾巴
    char ch;
    int num;
    struct stackNode *next;
} stackNode;

typedef struct LinkStack
{
    struct stackNode *head;
    struct stackNode *bottom;
    int level;//表示栈顶的优先级
} LinkStack;



int inputCheck(char str[101]);
int inputCheckChar(char str[101]);
int structCheck(char *p);
int ItemizationCheck(char **p);
int numberCheck(char ch);
int structCheck2(char *p);



int main()
{
    char str[101]={0};
    printf("只有计算器输入检测部分\n");
    printf("请输入表达式\n"
        "提示：只能包括+-*/()和数字，且不得超过100个字符\n");
    scanf("%s",str);
    getchar();

    if(inputCheck(str))
        printf("是合法表达式\n");
    else
        printf("不是合法表达式，请自行检查\n");

    system("pause");
    return 0;
}

//输入检测,合法返回1，否则返回0
int inputCheck(char str[101])
{
    char *p=str;//p指向str的首元素

    if(inputCheckChar(str) == 0)
        return 0;//判断是否有非法字符

    if(*p == '-'){
        if(*(++p) == '-')//判断p的下一位字符，同时让p自加
        {
            printf("报错：前两个字符均为'-'！");
        }
    }

    //判断结构是否合法
    if(structCheck(p) == 1)
        return 1;
    else 
        return 0;
}

//判断一个字符数组中是否有非法字符，有则返回0，否则返回1
int inputCheckChar(char str[101])
{
    int num=0;
    char *p=str;
    for(;*p != 0;p++)
    {
        if((*p != '+'&& //if中的条件表示该字符不为 +-*/和数字中的一个
            *p != '-'&&
            *p != '*'&&
            *p != '/'&&
            *p != '('&&
            *p != ')')
            &&(*p<48 || *p>57))
            {
                printf("报错：出现非法字符 %c\n",*p);
                return 0;
            }
        if(*p == '(')
            num++;
        else if (*p == ')')
            num--;
    }
    if(num != 0){
        printf("左右括号的数量不相同\n");
        return 0;
    }


    return 1;
}

//递归判断表达式内是否是项、运算符相间的结构。本身判断p为数字，p的下一位为运算符，是则返回1，否则0
int structCheck(char *p)
{
    int isItemization=ItemizationCheck(&p);//判断p是否指向项
    if(isItemization && *(p+1) == 0)
    {//p指向最后一个项且后一个字符为0，读到str有效字符的末尾，意味着中途没有遇到return 0的情况
        return 1;
    }
    else if(isItemization)
    {
        return structCheck(p+2);//递归自身
    }
    else if(*p == 0)
    {
        return 1;
    }
    else
    {
        printf("报错：出现了两个运算符连相邻的情况\n");
        return 0;
    }
}

//判断字符（串）是否是“项”,是则返回1，否则0。同时使p指向该“项”的最后一位（左右括号则为右括号）
int ItemizationCheck(char **ppChar)
{
    if (numberCheck(**ppChar))//如果*ppChar指向数字，说明ppChar指向的“项”为纯数字
    {
        while(numberCheck(*(*ppChar+1)) == 1)//直到p指向最后一位
            *ppChar=*ppChar+1;
        return 1;
    }
    else if(**ppChar == '(')//如果*ppchar指向 '('，说明ppchar指向的“项”是一个被括号包起来的完整表达式
    {
        if(structCheck2(*ppChar+1) == 1)
        {
            int k=1;
            while (k != 0)//k=0说明左右括号数量相同，即p指向该项的最后一位
            {
                *ppChar=*ppChar+1;
                if (**ppChar == '(')
                {
                    k++;
                }
                else if(**ppChar == ')')
                {
                    k--;
                }
            }
            
            return 1;
        }
    }
    else
    {
        printf("恭喜你整出bug了\n"
            "此bug出现在 函数int numberCheck(char **ppChar)下\n"
            "请保留测试数据进行debug\n");
    }
}

//判断一个字符是否是数字,是则返回1，否则0。很简单，不会出bug的
int numberCheck(char ch)
{
    if(ch>=48 && ch<=57)
        return 1;
    else
        return 0;
}

//递归判断项内是否是项、运算符相间的结构。实际上是 int structCheck(char *p) 的复制
int structCheck2(char *p)
{
    int isItemization=ItemizationCheck(&p);
    if(isItemization && *(p+1) == ')')
    {//p指向最后一个项且后一个字符为 )，读到项的末尾，意味着中途没有遇到return 0的情况
        return 1;
    }
    else if(isItemization)
    {
        return structCheck2(p+2);
    }
    else if(*p == 0)
    {
            printf("恭喜你整出bug了\n"
        "此bug出现在 函数int structCheck2(char *p)下\n"
        "请保留测试数据进行debug\n");
    }
    else
    {
        printf("报错：出现了两个运算符连相邻的情况\n");
        return 0;
    }
}
