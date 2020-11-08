#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// A simple utility to find the lowest common denominator for a group of rounded decimal values.

int find_fraction( const char *numstr, const int nstart, const int dstart, int *numerator );
void print_usage();

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_usage(argv[0]);
        exit(0);
    }

    const int START_INDEX = 1;
    int solved = 0;
    int *numerators = malloc( argc * sizeof(int *) ); // The first index is never used.

    for(int i=START_INDEX; i<argc; i++) numerators[i]=0;

    int d=1;

    for(int i=1; i<argc; i++){
        int d_prev=d;
        d=find_fraction(argv[i],numerators[i],d,&numerators[i]);

        // Restart the loop if d has changed, so previous numerators can be re-calculated.
        if((d!=d_prev)&&(i!=START_INDEX)) i=START_INDEX-1;
    }

    printf("Solved:\n");

    for(int i=1; i<argc; i++) {
        printf("%d/%d =\t%lf ~=\t%s\n",numerators[i],d,(double)numerators[i]/d,argv[i]);
    }

    free(numerators);
}

// Finds the smallest numerator and denominator at least as large as `nstart` and `dstart`, respectively,
// that form a fraction that, when rounded to the same precision, matches the decimal value `numstr`.
// Returns `denominator`, and stores `numerator`.
int find_fraction( const char *numstr, const int nstart, const int dstart, int *numerator ) {
    double value = strtod(numstr,0);

    // Find number of digits after the decimal point
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

// Prints a short description of how to use the utility.
void print_usage(char * name) {
    printf("usage: %s <values>\n", name);
}