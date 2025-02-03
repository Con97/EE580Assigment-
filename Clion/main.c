#include "data.h"
#include "math.h"
#include "stdio.h"

int main(void)
{
    double AL[9] = {2,0,2,0,0,9,3,3,4};
    double FC[9] = {2,0,2,0, 3,2,1,1,7};

    int len_filters = 29-1;
    double AL_sig[900+28*2] = { 0.0 };
    double FC_sig[900+28*2] = { 0.0 };

    double AL_mu = 0;
    double FC_mu = 0;

    for(int i = 0; i<9; i++){
        AL_mu  += AL[i];
        FC_mu  += FC[i];
    }

    AL_mu /= 9;
    FC_mu /= 9;

    for(int i = len_filters; i<900; i++){
            AL_sig[i] = AL[i%9] - AL_mu;
            FC_sig[i] = FC[i%9] - FC_mu;
    }

    int len_output = 900+29-1;
    double filtered_AL[len_output];
    double filtered_FC[len_output];

//    for (int i = 0; i <100; i++){
//        printf("%f\n",FC_sig[i]);
//    }


    for(int n = 0; n<len_output; n++){
        for(int v = 29; v>-1; v--){
            filtered_FC[n] = FC_sig[n] * filter_b[n-v];
        }
        printf("x[%d] = %f\n", n,filtered_FC[n]);
    }



    return 0;
}