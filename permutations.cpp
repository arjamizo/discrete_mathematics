#include<cstdio>
#include<iostream>
#include<cmath>
#include<cassert>
#include<algorithm> //adjacent_find
#include<iterator> //reverse_iterator
#include <sstream>

using namespace std;

#define N 100
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
    static int *find_largest_index_fullfilling_ak_is_lover_than_following_element(int *b, int *e) {
        return (&*std::adjacent_find(REV(e),REV(b),std::greater<int>()))-1;
    }
    /***
    * increments permutations by 1.
    * implementation based on http://stackoverflow.com/a/11483184/781312
    ***/
    int next() {
        int *k,*l;
        k=find_largest_index_fullfilling_ak_is_lover_than_following_element(content, content+n);
                                                                    //cout<<"k="<<" "<<k[0]<<" ?"<<k<<"=?="<<(content+n)<<endl;
        if(k+2==content) return false;                              //this is last possible combination. This works only if numbers in array are unique
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
};
void helper_in_understanding_adjacent() {
    typedef std::reverse_iterator<char*> REV;
    char tab[]={5,0,1,8,4,3,7,6};
    int n=8;
    std::cout<<"some tests to adjacent_find and functional"<<std::endl;
    std::cout<<((int)*std::adjacent_find(tab,tab+n,std::greater<char>()))<<" looking for ascending elements, it means that this element is greater than next element"<<std::endl;
    std::cout<<((int)*std::adjacent_find(tab,tab+n,std::less<char>()))<<" looking for descending elements, it means this element is smaller than previous element"<<std::endl;
    std::cout<<((int)*std::adjacent_find(REV(tab+n),REV(tab),std::greater<char>()))<<" reverse looking for descending elements, after this number there is lower nubmer that this one but from reversed point of view"<<std::endl;
    std::cout<<((int)*std::adjacent_find(REV(tab+n),REV(tab),std::less<char>()))<<" reverse looking for descending elements, previous element is greater, but from reversed point of view; this finds latest k such as a[k]<a[k+1]"<<std::endl;
}
void testFinding() {
    int tab[]={5,0,1,6,4,3,7,6};
    int *ret;
    ret=Permutations::find_largest_index_fullfilling_ak_is_lover_than_following_element(tab,tab+8);
    //cout<<(ret-tab)<<endl;
    assert(ret==tab+5); //tab[5]==3, largest index k fulfilling condition a[k]<a[k+1] is 5
}

int main(int argc, char *argv[]) {
    helper_in_understanding_adjacent();
    testFinding();
    int i=0;
    cerr<<"How many numbers should be permutated?"<<endl;
    int n;
    cin>>n;
    Permutations perm(0,n);
    do {
        cout<<perm;
        i++;
    } while (perm.next());
    cout<<"there were "<<i<<" permutations"<<endl;
}
