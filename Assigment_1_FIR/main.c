
/**
 * main.c
 */
#include "data.h"
#include "stdio.h"

int i, n, v;

//Both Student Numbers
float AL[9] = { 2.0, 0.0, 2.0, 0.0, 0.0 ,9.0 ,3.0 ,3.0 ,4.0 };
float FC[9] = { 2.0, 0.0, 2.0, 0.0, 3.0, 2.0, 1.0, 1.0, 7.0 };

// padded signal with 28 zeros
float AL_sig[928] = { 0.0 };
float FC_sig[928] = { 0.0 };

float AL_sig_mu[900+28] = { 0.0 };
float FC_sig_mu[900+28] = { 0.0 };

// calculate mean of student numbers
float AL_mu = 0.0;
float FC_mu = 0.0;

// length of filtered signal is signal length + filter length -1
float filtered_AL[928];
float filtered_FC[928];

// Write to file
FILE *filePtr;


void main()
{


    for(i = 0; i<9; i++){
        AL_mu  += AL[i];
        FC_mu  += FC[i];
    }

    AL_mu /= 9.0;
    FC_mu /= 9.0;

    // signal minus mean so signal is zero mean
    for(i = 0; i<900; i++){
            AL_sig_mu[i] = AL[i%9] - AL_mu;
            FC_sig_mu[i] = FC[i%9] - FC_mu;

            AL_sig[i] = AL[i%9];
            FC_sig[i] = FC[i%9];
    }

    for(i = 900; i<928; i++){
            AL_sig_mu[i] = 0;
            FC_sig_mu[i] = 0;
            AL_sig[i] = 0;
            FC_sig[i] = 0;
    }



//Convolve sigs
    for(n = 0; n<928; n++){
        filtered_FC[n] = 0;
        filtered_AL[n] = 0;
        for(v = 0; (v<=n)&&(v<29); v++){
            filtered_FC[n] += FC_sig_mu[n-v] * filter_b[v];
            filtered_AL[n] += AL_sig_mu[n-v] * filter_a[v];
        }
    }
//
//    // Write to file
//
    filePtr = fopen("filter_FC.txt","w");

    for(i =0; i < 928; i++){
        fprintf(filePtr,"%lf\n",filtered_FC[i]);
    }
    fclose(filePtr);
//
    filePtr = fopen("filter_AL.txt","w");

    for(i =0; i < 928; i++){
        fprintf(filePtr,"%lf\n",filtered_AL[i]);
    }
    fclose(filePtr);

    return ;

}
