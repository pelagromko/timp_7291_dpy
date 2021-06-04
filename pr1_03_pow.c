#include <stdio.h>
#include <math.h>

int main()
{
    double x, y, P;
    if ((scanf("%lf",&x)==1)&&(scanf("%lf",&y)==1))
    {
        P = pow(x,y);
        printf("%lf\n",P);
    }
    else
    {
        printf("Error! Check the entered values\n");
    }
    return 0;
}