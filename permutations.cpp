#include<cstdio>
#include<iostream>
#include<cmath>
#include<cassert>
#include<algorithm> //adjacent_find
#include<iterator> //reverse_iterator
#include <sstream>

using namespace std;

#define N 1000
struct Permutations {
    int content[N];
    int n;
    typedef std::reverse_iterator<int*> REV;
    Permutations(int s, int e) {
        assert(s<e);
        n=e-s;
        assert(n<N);
        for(int i=s; i<e; ++i)
            content[i-s]=i;
    }
    int *find_largest_index_fullfilling_ak_is_lover_than_following_element(int *b, int *e) {
        return &*std::adjacent_find(REV(e),REV(b),std::greater<int>())-1;
        //-1 because function would return pointer to number k such as k->max: a[k-1]<a[k],
        //but, according to definition, we need a[k]<a[k+1]
    }
    /***
    * increments permutations by 1.
    * implementation based on http://stackoverflow.com/a/11483184/781312
    ***/
    int next() {
        int *k,*l;
        k=find_largest_index_fullfilling_ak_is_lover_than_following_element(content, content+n);
                                                                    //cout<<"k="<<*k<<" ?"<<k<<"=?="<<(content+n)<<endl;
        if(*k==content[n-1]) return false;                          //this is last possible combination. This works only if numbers in array are unique
        l=&*std::find_if(REV(content+n),REV(content),std::bind2nd(greater<int>(),*k));
                                                                    //cout<<"l="<<*l<<" ?"<<l<<"=?="<<(content+n)<<endl;
        std::swap(*k,*l);
        std::reverse(k+1, content+n);
        return true;
    }
    friend std::ostream &operator<<(std::ostream &cout, const Permutations &perm) {
        for(int i=0; i<perm.n; ++i)
            cout<<perm.content[i]<<" ";
        cout<<std::endl;
        return cout;
    }
} perm(0,6);

int main(int argc, char *argv[]) {
    int i=0;
    do {
        cout<<perm;
        i++;
    } while (perm.next());
    cout<<"there were "<<i<<" permutations"<<endl;
}
