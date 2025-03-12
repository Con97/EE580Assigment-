

int n, m;

int x[4] = { 1, 2, 3, 4 };
int b[7] = { 5, 6, 7, 8, 0, 0, 0 };
int a = 1;

int y[7];


void main()
{

//Convolve sigs
    for(n = 0; n<7; n++){
        y[n] = 0;
        for(m = 0; (m<=n)&&(m<4); m++){
            y[n] += (b[n-m] * x[m])/a;
        }
    }

    return ;

}
