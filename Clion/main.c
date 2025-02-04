#include "data.h" // Stores the filter weights
#include "stdio.h"

int main(void)
{
    //Both Student Numbers
    double AL[9] = {2,0,2,0,0,9,3,3,4};
    double FC[9] = {2,0,2,0, 3,2,1,1,7};

    // padded signal with 28 zeros
    double AL_sig[900+28] = { 0.0 };
    double FC_sig[900+28] = { 0.0 };

    // calculate mean of student numbers
    double AL_mu = 0;
    double FC_mu = 0;

    for(int i = 0; i<9; i++){
        AL_mu  += AL[i];
        FC_mu  += FC[i];
    }

    AL_mu /= 9;
    FC_mu /= 9;

    // signal minus mean so signal is zero mean
    for(int i = 0; i<900; i++){
            AL_sig[i] = AL[i%9] - AL_mu;
            FC_sig[i] = FC[i%9] - FC_mu;
    }

    // length of filtered signal is signal length + filter length -1
    double filtered_AL[928];
    double filtered_FC[928];


// Convolve sigs
    for(int n = 0; n<928; n++){
        filtered_FC[n] = 0;
        filtered_AL[n] = 0;
        for(int v = 0; (v<=n)&&(v<29); v++){
            filtered_FC[n] += FC_sig[n-v] * filter_b[v];
            filtered_AL[n] += AL_sig[n-v] * filter_a[v];
        }
    }

    // Write to file
    FILE *filePtr;
    filePtr = fopen("filter_FC.txt","w");

    for(int i =0; i < 928; i++){
        fprintf(filePtr,"%lf\n",filtered_FC[i]);
    }
    fclose(filePtr);

    filePtr = fopen("filter_AL.txt","w");

    for(int i =0; i < 928; i++){
        fprintf(filePtr,"%lf\n",filtered_AL[i]);
    }
    fclose(filePtr);
    return 0;

}