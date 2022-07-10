#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NRMIC 0.0000001

double abso(double x){
    return (x < 0) ? -x : x;
}

double logrec(double n, double delta, double left, double right){
    double mid = left/2 + right/2;
    if(abso(pow(2,mid) - n) <= delta){
        //printf("%lf --- %lf\n", abso(pow(2,mid)-n), delta);
        return mid;
    }
    else{
        if(pow(2,mid) > n)
            return logrec(n, delta, left, mid-NRMIC);
        else
            return logrec(n, delta, mid+NRMIC, right);
    }
}

int main(void){
    int ok = 0;
    double n = 127;
    double delta = 0.00000001;
    if(n < 1){
        ok = 1;
        n = pow(n,-1);
    }
    double rez = logrec(n, delta, 0, n);
    if(ok == 1)
        rez *= -1;
    printf("logrec = %lf\nlog2(din c) = %lf\n", rez, log2(n));
}