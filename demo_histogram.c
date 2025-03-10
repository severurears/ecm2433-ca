/* To test histogram function */

#include <stdio.h>
#include <math.h>

void histogram(int *x, double *y, int n, int width);

int main(){
        int x[] = {0, 1, 2, 3, 4, 5};
        double H[] = {12.5, 6.4, 10, 7.6, 8, 13};
        histogram(x, H, 6, 30);
        return 0;
}
