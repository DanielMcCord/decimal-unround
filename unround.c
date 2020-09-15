#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int find_fraction( const char * numstr, const   int nstart, const int dstart, int * numerator );
void print_usage();

int main(int argc, char * argv[]) {
    if (argc == 1) {
        print_usage(argv[0]);
        exit(0);
    }

    int solved = 0;
    int * numerators = malloc( argc * sizeof(int *) ); // The first index is never used.

    for(int i=1; i<argc; i++) numerators[i]=0;

    int d=1;

    for(int i=1; i<argc; i++){
        int d_prev=d;
        d=find_fraction(argv[i],numerators[i],d,&numerators[i]);
        if((d==d_prev)||(i==1)) continue;
        else i=1;
    }

    printf("Solved:\n");
    for(int i=1; i<argc; i++) {
        printf("%d/%d =\t%lf ~=\t%s\n",numerators[i],d,(double)numerators[i]/d,argv[i]);
    }

    free(numerators);
}

// Finds the smallest numerator and denominator at least as large as nstart and dstart, respectively,
// that form a fraction that, when rounded to the same precision, matches the decimal value given by numstr.
// Returns the denominator, and stores the numerator in numerator.
int find_fraction( const char * numstr, const int nstart, const int dstart, int * numerator ){
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
    int solved = 0;

    while(!solved) {
        guess = (double) n / d;
        //printf("Target:\t%s\nTrying: %d/%d =\t%lf\n",numstr,n,d,guess);

        if(guess < value-max_err) n++;
        else if(guess > value+max_err) d++;
        else solved = 1;
    }

    *numerator = n;
    return d;
}

void print_usage(char * name) {
    printf("usage: %s <values>\n", name);
}