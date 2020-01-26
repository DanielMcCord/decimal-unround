#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Finds the lowest denominator fraction that rounds to the given decimal value.
void find_fraction( const char * numstr, const int nstart, const int dstart, int * numerator, int * denominator );

void find_fraction( const char * numstr, const int nstart, const int dstart, int * numerator, int * denominator ){
    double value = strtod(numstr,0);
    int dec_places = 0;

    {
        int i;
        for(i=0;numstr[i]&&(numstr[i]!='.');i++);

        // skip decimal point and start counting after it
        for(i++;numstr[i];i++) {
            if((numstr[i]>='0')&&(numstr[i]<='9')) dec_places++;
        }
    }

    double max_err = pow(.1, dec_places + 1) * 5; // upper limit on rounding error in input

    int n = nstart;
    int d = dstart;
    double guess;

    for(int solved=0; !solved;) {
        guess = (double) n / d;

        //printf("Trying: %d/%d =\t%lf\n",n,d,guess);

        if(guess > value+max_err) d++;
        else if (guess < value-max_err) n++;
        else solved = 1;
    }
    *numerator = n;
    *denominator =  d;
}

int main(int argc, char * argv[]) {
    int n,d;
    find_fraction( argv[1], 0, 1, &n, &d );
    printf("\nSolved: %d/%d =\t%lf\n",n,d,(double)n/d);
}