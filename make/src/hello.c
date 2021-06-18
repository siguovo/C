#include "head.h"

int main()
{
    int x = 14;
    int y = 7;
    printf("%d + %d = %d\n" ,x , y ,add1(x,y));
    printf("%d - %d = %d\n" ,x , y ,sub1(x,y));
    printf("%d x %d = %d\n" ,x , y ,mul1(x,y));
    printf("%d / %d = %d\n" ,x , y ,div1(x,y));
    return 0;
}
