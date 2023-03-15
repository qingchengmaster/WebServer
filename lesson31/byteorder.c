#include <stdio.h>
//判断字节序
int main()
{
    union{
        short value;
        char bytes[sizeof(short)];
    }test;
    test.value=0x0102;
    if(test.bytes[0]==1&&test.bytes[1]==2)
    {
        printf("大端字节序");
    }
    else
    {
        printf("小端字节序");
    }
    return 0;
}