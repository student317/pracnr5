
/*Nauczyli mnie mnóstwa mądrości,
Logarytmów, wzorów i formułek,
Z kwadracików, trójkącików i kółek
Nauczali mnie nieskończoności.*/
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

class wzorce{
public: bool X[3][3];

    public: wzorce()
    {
    string a[3];
    cin >>a[0];
    cin >>a[1];
    cin >>a[2];

    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {if(a[i][j]=='.')X[i][j]=0;
                    else X[i][j]=1;
        }
    }
    bool FUN1(wzorce Y)
    {
        for(int i=0;i<2;i++)
        for(int j=0;j<3;j++)
        if(X[i+1][j]!=Y.X[i][j])return 0;
        return 1;
    }
     bool FUN2(wzorce Y)
    {
        for(int j=0;j<3;j++)
        if(X[2][j]!=Y.X[0][j])return 0;
        return 1;
    }
};

bool operator==(wzorce const& a,wzorce const& b)
    {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(a.X[i][j]!=b.X[i][j])return 0;
    return 1;
    }

class wzory{
public: bool X[5][3];

int tonum()
{
int A=0;
for(int j=0;j<3;j++)
for(int i=0;i<5;i++)
{A=A*2;
A=A+X[i][j];
}
return A;
}

bool pczm; //- to z //+ to 1
    public: wzory(wzorce a,wzorce b,int l)
    {   pczm=1;
    for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                X[i][j]=a.X[i][j];
        for(int j=0;j<3;j++)
                {X[3][j]=b.X[2][j];
                X[4][j]=l%2;
                l=l/2;
                }
    }

     public: wzory(int l,wzorce a,wzorce b)
    {pczm=1;
     for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            X[i+1][j]=a.X[i][j];
     for(int j=0;j<3;j++)
        {X[4][j]=b.X[2][j];
        X[0][j]=l%2;
        l=l/2;
        }
    }

    public: wzory(wzorce a,wzorce b)
    {pczm=1;
     for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            X[i][j]=a.X[i][j];
     for(int j=0;j<3;j++)
        {X[3][j]=b.X[1][j];
        X[4][j]=b.X[2][j];

        }
    }

 public: wzory(wzorce a,int l)
    {pczm=0;
     for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            X[i][j]=a.X[i][j];

    for(int i=3;i<5;i++)
        for(int j=0;j<3;j++)
            {X[i][j]=l%2;
            l=l/2;}
    }

     public: wzory(int l,wzorce a)
    {pczm=0;
     for(int i=2;i<5;i++)
        for(int j=0;j<3;j++)
            X[i][j]=a.X[i-2][j];

    for(int i=0;i<2;i++)
        for(int j=0;j<3;j++)
           {X[i][j]=l%2;
            l=l/2;}
    }

    public: wzory(int l,wzorce a,int m)
    {
     for(int i=1;i<4;i++){
        for(int j=0;j<3;j++)
            X[i][j]=a.X[i-1][j];
}
        for(int j=0;j<3;j++)
           { X[0][j]=l%2;
            l=l/2;
            X[4][j]=m%2;
            m=m/2;
            }
    }

     bool FUN2(wzory Y)
    {
        for(int i=0;i<5;i++)
        if(X[i][2]!=Y.X[i][0])return 0;
        return 1;
    }

     bool FUN1(wzory Y)
    {
        for(int i=0;i<5;i++)
        for(int j=0;j<2;j++)
        if(X[i][j+1]!=Y.X[i][j])return 0;
        return 1;
    }

};

int Mypow(int a, int b, int m)
{
int i;
long long A = 1;
long long x = a%m;
for (i=1; i<=b; i<<=1)
{
x =x%m;
    if ((b&i) != 0)
    {
    A = A* x;
    A =A% m;
    }
x =x* x;
}

return A;
}



bool operator==(wzory const& a,wzory const& b)
    {
    for(int i=0;i<5;i++)
        for(int j=0;j<3;j++)
            if(a.X[i][j]!=b.X[i][j])return 0;
    return 1;
    }



int main()
{
int n,p,m;
cin >>n;
cin >>p;
cin >>m;
wzorce *X[p];
for(int i=0;i<p;i++) // wczytać wzorce          max///10 000///obrotów
    {X[i]=new wzorce();
     for(int j=0;j<i;j++)
        if(*(X[j])==*(X[i]))
            {p--;//zmniejsz tabele
            delete X[i];//usun duplikat
            i--;//jeszcze raz rozwaz to miejsce w tabeli
            j=i;//zakoncz pentętle szukajaca duplikaty
            }
}

vector<wzory*> B;


for(int i=0;i<p;i++)
    for(int j=0;j<p;j++)        ///180 000 obrotów
    {
     if(X[i]->FUN1(*(X[j]))){
                             for(int k=0;k<8;k++)   {wzory*a=new wzory(*(X[i]),*(X[j]),k);
                                                    B.push_back(a);
                                                    }
                            }
     if(X[j]->FUN1(*(X[i]))){
                              for(int k=0;k<8;k++)  {wzory*a=new wzory(k,*(X[j]),*(X[i]));
                                                    B.push_back(a);
                                                    }
                            }
     if(X[i]->FUN2(*(X[j]))){
                             wzory*a=new wzory(*(X[i]),*(X[j]));
                             {B.push_back(a);}
                            }
     if(X[j]->FUN2(*(X[i]))){
                             wzory*a=new wzory(*(X[j]),*(X[i]));
                             {B.push_back(a);}
                            }
    }
for(int i=0;i<p;i++)
  for(int k=0;k<64;k++)      /// 640 000 obrotów
   {wzory*a=new wzory(*(X[i]),k);
    wzory*b=new wzory(k,*(X[i]));
    wzory*c=new wzory(k%8,*(X[i]),k/8);
    B.push_back(a);
    B.push_back(b);
    B.push_back(c);
    }

 int  wynik[3][32768];
for(int i=0;i<32768;i++)
    wynik[2][i]=0;

int q=B.size();
for(int i=0;i<q;i++)
    wynik[2][B[i]->tonum()]=1;



long long int temp =0;
for(int j=0;j<1024;j++)
{
     temp=0;
     for(int i =0; i<32;i++)
        {temp=(temp+wynik[2][j+1024*i])%m;}

for(int k=0;k<32;k++)
{
    if(wynik[2][j*32+k])wynik[0][j*32+k]=Mypow(2,5,m);
        else wynik[0][j*32+k]=temp;
}
}

int cos=Mypow(2,5,m);
for(int i=4;i<n;i++) ///163 840 000 obrotów
{
cos=(cos*Mypow(2,5,m))%m;

        temp =0;

        for(int j=0;j<1024;j++)
        {
        temp=0;
            for(int l =0; l<32;l++)
            {temp=(temp+wynik[i%2][j+1024*l])%m;}

                for(int k=0;k<32;k++)
                {
                if(wynik[2][j*32+k])wynik[(i+1)%2][j*32+k]=cos;
                else wynik[(i+1)%2][j*32+k]=temp;
                }
        }



}
long long int  W=0;

if(n==3){
for(int i=0;i<32768;i++)
W=(W+wynik[2][i])%m;
}
else{
for(int i=0;i<32768;i++)
W=(W+wynik[n%2][i])%m;

}
cout << ((Mypow(2,5*n,m)-W)%m+m)%m << endl;

    return 0;
}

