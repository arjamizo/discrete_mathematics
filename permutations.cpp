#include<cstdio>
#include<iostream>
#include<cmath>
#include<cassert>

#define N 1000
struct Permutations {
    int content[N];
    int n;
    Permutations(int s, int e) {
        assert(s<e);
        n=e-s;
        assert(n<N);
        for(int i=s; i<e; ++i)
            content[i-s]=i;
    }
    /***
    * increments permutations by 1.
    ***/
    int next() {
        return n-->0;
    }
    friend std::ostream &operator<<(std::ostream &cout, const Permutations &perm) {
        for(int i=0; i<perm.n; ++i)
            cout<<perm.content[i]<<" ";
        cout<<std::endl;
        return cout;
    }
} perm(1,5);

int main(int argc, char *argv[]) {
    do
    std::cout<<perm;
    while (perm.next());
}
