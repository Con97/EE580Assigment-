#include "data.h"
#include "math.h"
#include "stdio.h"

int main(void)
{
    float AL[9] = {2,0,2,0,0,9,3,3,4};
    float FC[9] = {2,0,2,0, 3,2,1,1,7};

    float AL_sig[900];
    float FC_sig[900];

    float AL_mu = 0;
    float FC_mu = 0;

    for(int i = 0; i<9; i++){
        AL_mu  += AL[i];
        FC_mu  += FC[i];
    }

    AL_mu /= 9;
    FC_mu /= 9;

    for(int i = 0; i<900; i++){
            AL_sig[i] = AL[i%9] - AL_mu;
            FC_sig[i] = FC[i%9] - FC_mu;
    }

    float filtered_AL[928];
    float filtered_FC[928];


//    for(int n = 0; n<900; n++){
//        for(int v=28 ; v>-1 ; v--){
//            filtered_AL[n] += filter_a[v] * AL_sig[n];
//
//
//        }
//        printf("%.6f ", filtered_AL[n]);
//    }

    for(int n = 0; n<100; n++){
        for(int v=28 ; v>-1 ; v--){
//            filtered_AL[n] += filter_a[v] * AL_sig[n];
            printf("filter_a[%d] * AL_sig[%d]", v,n);

        }
        printf("\n\n");
//        printf("%.6f ", filtered_AL[n]);
    }

    return 0;
}