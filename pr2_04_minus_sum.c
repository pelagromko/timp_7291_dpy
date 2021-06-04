#include<stdio.h>

int main()
{
    double n, x, S = 0, i = 0;
    if(scanf("%lf",&n)==1)
    {
        for(i; i<n; i++)
        {
            if(scanf("%lf",&x)==1)
            {
                S = S + (-x);
            }
            else
            {
                printf("Error! Check the entered values\n");
            }
        }
        printf("%lf\n",S);
    }
    else
    {
        printf("Error! Check the entered values\n");
    }
    return 0;
}