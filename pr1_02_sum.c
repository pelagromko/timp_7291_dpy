#include <stdio.h>

int main()
{
    double x, y, S;
    if ((scanf("%lf",&x)==1)&&(scanf("%lf",&y)==1))
    {
        S = x + y;
        printf("%lf\n",S);
    }
    else
    {
        printf("Error! Check the entered values\n");
    }
    return 0;
}