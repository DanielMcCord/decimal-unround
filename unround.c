#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Finds the lowest denominator fraction that rounds to the given decimal value.

int main(int argc, char * argv[]) {
    char * numstr = argv[1];
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
    int super_verbose = 0;

    if(super_verbose||(argc>=3)&&(strcmp(argv[2],"--verbose")==0)) {
        printf("\ndecimal places: %d\n",dec_places);
        printf("original value:\t%.*lf\n",dec_places,value);
        printf("max error:\t%lf\n\n",max_err);
    }

    int extra_verbose = 0;
    if (super_verbose||(argc>=4)&&(strcmp(argv[3],"--extra")==0)) {
        extra_verbose = 1;
    }

    int n = 0;
    int d = 1;
    double guess;

    for(int solved=0; !solved;) {
        guess = (double) n / d;
        if(extra_verbose==1) {
            printf("Trying: %d/%d =\t%lf\n",n,d,guess);
        }

        if(guess > value+max_err) d++;
        else if (guess < value-max_err) n++;
        else solved = 1;
    }

    printf("\nSolved: %d/%d =\t%lf\n",n,d,guess);
}