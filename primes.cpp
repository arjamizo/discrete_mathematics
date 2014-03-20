#include<cstdio>

#include<cmath>

int eratostenes(const int N, char ret[]) {
    ret[0]=ret[1]=0;
    for(int i=2; i<N; ++i) ret[i]=1;
    for(int i=2; i<N; ++i) {
        for(int j=i*2; j<N; j+=i)
            ret[j]=0;
    }
}

#define N 2000
char ret[N];

int main(int argc, char *argv[]) {
    eratostenes(N, ret);
    int len=log10(N)+1;
    for(int i=0; i<N; ++i) {
        if(ret[i])
            printf("%*d ", len, i);
    }
    return 0;
}
