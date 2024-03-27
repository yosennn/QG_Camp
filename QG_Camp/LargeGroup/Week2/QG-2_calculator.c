#include <stdio.h>
#include <stdlib.h>

int inputCheck(char str[101]);
int inputCheckChar(char str[101]);
int stringCheck(char *p);
int numberCheck(char *p);



int main()
{
    char str[101]={0};
    printf("此计算器只完成了输入检测部分，且没有考虑()，请忽视下面的提示中的()\n");
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

//输入检测
int inputCheck(char str[101])
{
    char *p=str;//p指向str的首元素

    inputCheckChar(str);//判断是否有非法字符

    if(*p == '-'){
        if(*(++p) == '-')//判断p的下一位字符，同时让p自加
        {
            printf("报错：前两个字符均为'-'！");
        }
    }

    if(stringCheck(p) == 1)
        return 1;
    else 
        return 0;
}

//判断一个字符数组中是否有非法字符，有则返回0，否则返回1
int inputCheckChar(char str[101])
{
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

    }
    return 1;
}

//判断字符串内是否是数字、运算符相间的结构，是则返回1，否则0
int stringCheck(char *p)
{
    if(numberCheck(p) == 1 && *(p+1) == 0)
    {//p指向最后一个数字且后一个字符为0，读到str有效字符的末尾，意味着中途没有遇到return 0的情况
        return 1;
    }
    else if(numberCheck(p) == 1)
    {
        if(numberCheck(p+1) == 1)
        {
            printf("报错：出现了两个数字连在一起的情况\n");
            return 0;//p指向数字，且p的下一个也为数字，非法的结构
        }
        else//表示p通过了测试
            return stringCheck(p+2);
    }
    else
    {
        printf("报错：出现了两个字符串连相邻的情况\n");
        return 0;
    }
}

//判断一个字符是否是数字,是则返回1，否则0
int numberCheck(char *p)
{
    if(*p>=48 && *p<=57)
        return 1;
    else
        return 0;
}