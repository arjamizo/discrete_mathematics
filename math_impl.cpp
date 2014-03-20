#include <iostream>
#include <functional>
#include <iomanip>
#include <sstream>
#include <cmath> //NaN

using namespace std;

struct Unary : unary_function<float, float> {
    virtual const char* getName()=0;
    virtual float operator()(float f)=0;
};

struct FloorHalf : public Unary {
    const char* getName() {
        return "Zaokr w dol: rzutowanie na inta";
    }
    float operator() (float f) {
        return (int)(f);
    }
};
struct FloorSubstracting : public Unary {
    const char* getName() {
        return "Zaokr. w dol poprzez odejmowanie/dodawnie, az abs(x)<1";
    }
    float operator() (float f) {
        float a=f;
        if (f>0)
            while (f>=1.0f) f-=1.0f;
        else if (f<0)
            while (f<=-1.0f) f+=1.0f;
        cout<<a<<"-"<<f<<"="<<(a-f)<<endl;
        return a-f;
    }
};
struct CeilHalf : public Unary {
    const char* getName() {
        return "Zaokr w gora: dodanie .5 i rzutowanie na int";
    }
    float operator() (float f) {
        return (int)(f+(f>=0?.5f:.0f));
    }
};

struct MentisMinusInt : public Unary {
    const char* getName() {
        return "Mantysa: odjecie liczby rzutowanej na int";
    }
    float operator() (float f) {
        return f-(int)f;
    }
};

struct MentisMinus1 : public Unary {
    const char* getName() {
        return "Mantysa: odejmowanie tak dlugo jak trzeba";
    }
    float operator() (float f) {
        if(f>0) while(f>=1.0f) f-=1.0f;
        else if(f<0) while(f<=-1.0f) f+=1.0f;
        return f;
    }
};

struct ModXYCppLike : public binary_function<float,float,float> {
    //implementacja jak w jezyku cpp
    float operator() (float x, const float y) {
        if (x>0)
            while (x>=y) x-=y;
        else if (x<0)
            while (x<=-y) x+=y;
        return x;
    }
} modxycpplike;

struct ModXYPythonLike : public binary_function<float,float,float> {
    //implementacja jak w jezyku python - mozliwe do sprawdzenia np. w google
    float operator() (float x, const float y) {
        if (x>0)
            while (x>=y) x-=y;
        else if (x<0)
            while (x<0) x+=y;
        return x;
    }
} modxypythonlike;

struct MyModXPython: public Unary {
    mutable int y;
    const char* getName() {
        stringstream ss;
        ss<<"Modulo "<<y<<": odejmowanie/dod. tyle ile trzeba, reszta zawsze >0, jak w Pythonie";
        return ss.str().c_str();
    }
    float operator() (float f) {
        if(f!=(int)f) return NAN;
        return modxypythonlike((int)f,(int)y);
    }
    MyModXPython *setY(int y) {
        this->y=y;
        return this;
    }
};
struct MyModXCPP: public Unary {
    mutable int y;
    const char* getName() {
        stringstream ss;
        ss<<"Modulo "<<y<<": odejmowanie/dod. tyle ile trzeba, reszta czasami <0, jak w c++";
        return ss.str().c_str();
    }
    float operator() (float f) {
        if(f!=(int)f) return NAN;
        return modxycpplike((int)f,(int)y);
    }
    MyModXCPP *setY(int y) {
        this->y=y;
        return this;
    }
};

struct CPPModX: public Unary {
    mutable int y;
    const char* getName() {
        stringstream ss;
        ss<<"Modulo "<<y<<": implementacja jezyka c++";
        return ss.str().c_str();
    }
    float operator() (float f) {
        if(f!=(int)f) return NAN;
        return ((int)f)%((int)y);
    }
    CPPModX *setY(int y) {
        this->y=y;
        return this;
    }
};




int main()
{
    float input[]={-.25f, .1f, .33f, 45.0f, 99.0f, -99.0f, -12.0f, -1.6f, -1.45f};
    int inlen=8;
    int oplen=100;
    Unary *operations[100]={
          new FloorHalf()
        , new FloorSubstracting()
        , new CeilHalf()
        , new MentisMinusInt()
        , new MentisMinus1()
        , (new CPPModX)->setY(8)
        , (new MyModXCPP)->setY(8)
        , (new MyModXPython)->setY(8)
        , (new CPPModX)->setY(3)
        , (new MyModXCPP)->setY(3)
        , (new MyModXPython)->setY(3)
        , (new CPPModX)->setY(2)
        , (new MyModXCPP)->setY(2)
        , (new MyModXPython)->setY(2)
        , 0
    };
    //cout<<"elo "<<FloorHalf().operator()(4.0f)<<endl;
    stringstream cout;
    for(int i=-1; i<oplen; ++i) {
        for(int j=0; j<=inlen; ++j) {
            cout<<fixed<<setprecision(2)<<setw(7);
            if(i>=0 && j<inlen) {
                //wypisywanie wynikow
                cout<<(*operations[i]).operator()(input[j]);
            } else if (j==inlen && i>=0) {
                //ostatnia kolumna to etykiety algorytmow
                cout<<operations[i]->getName();
            } else if (i==-1 && j<inlen) {
                //pierwszy wiersz to tylko wiersz przykladowych argumentow
                cout<<input[j];
            } else {
                cout<<"<- dane";
            }
            cout<<" ";
        }
        cout<<endl;
        if(operations[i+1]==0) break;
    }
    std::cout<<cout.str();
    std::cout << "Hello world!" << endl;
    return 0;
}