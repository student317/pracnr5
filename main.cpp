#include <iostream>

using namespace std;

class treeavlA
{
public:

int high;

int id;
int id2;
char typ;
double y;
double x;

double yend;
double xend;


treeavlA *lewo;
treeavlA *prawo;


void draw(int offs)
{
   if(prawo!=NULL)prawo->draw(offs+1);
for (int i=0;i<offs;i++)cout <<"   ";
cout << x ;
cout << " " ;
cout << y ;
cout << " " ;
cout << id;
cout << " " ;
cout << typ ;
cout << " " ;
cout << xend;
cout << " " ;
cout << yend <<endl;
 if(lewo!=NULL)lewo->draw(offs+1);
}



treeavlA()//puste drzewo
{typ='e';
}

treeavlA(double x1,double y1,int id1,int id2,char typ1,double x2,double y2)//leaf
{
x=x1;
y=y1;
xend=x2;
yend=y2;
typ=typ1;
id=id1;
id2=id2;

high=1;
lewo=NULL;
prawo=NULL;
}


void Lrotation()
{double  temp =x;
x=lewo->x;
lewo->x=temp;

temp =y;
y=lewo->y;
lewo->y=temp;

temp =xend;
xend=lewo->xend;
lewo->xend=temp;

temp =yend;
yend=lewo->yend;
lewo->yend=temp;

char temp2 =typ;
typ=lewo->typ;
lewo->typ=temp2;

int temp3=id;
id=lewo->id;
lewo->id=temp3;

 temp3=id2;
id2=lewo->id2;
lewo->id2=temp3;


treeavlA *pom= prawo;
prawo= lewo;
lewo=prawo->lewo;
prawo->lewo=prawo->prawo;
prawo->prawo=pom;

prawo->high=max(prawo->lewo==NULL?0:prawo->lewo->high,prawo->prawo==NULL?0:prawo->prawo->high) +1;


high=max(lewo==NULL?0:lewo->high,prawo==NULL?0:prawo->high) +1;

}

void Rrotation()
{

double  temp =x;
x=prawo->x;
prawo->x=temp;

temp =yend;
yend=prawo->yend;
prawo->yend=temp;

 temp =xend;
xend=prawo->xend;
prawo->xend=temp;

temp =y;
y=prawo->y;
prawo->y=temp;

char temp2 =typ;
typ=prawo->typ;
prawo->typ=temp2;

int temp3=id;
id=prawo->id;
prawo->id=temp3;

temp3=id2;
id2=prawo->id2;
prawo->id2=temp3;


treeavlA *pom= lewo;
lewo= prawo;
prawo=lewo->prawo;
lewo->prawo=lewo->lewo;
lewo->lewo=pom;


lewo->high=max(lewo->lewo==NULL?0:lewo->lewo->high,lewo->prawo==NULL?0:lewo->prawo->high) +1;



high=max(lewo==NULL?0:lewo->high,prawo==NULL?0:prawo->high) +1;

}


bool add(double x1,double y1,int id1,int id2,char typ1,double x2,double y2)
{bool stop=1;

if(typ=='e'){x=x1;y=y1;id=id1;typ=typ1;xend=x2;yend=y2; return 0;}

if(lewo==NULL)
{
  if(x>x1||(x==x1&&y>=y1)  )//wlewo
        {lewo= new treeavlA(x1,y1,id1,id2,typ1,x2,y2); high++;return 1;}
  else{
    if(prawo!=NULL)
        stop=prawo->add(x1,y1,id1,id2,typ1,x2,y2);
    else{
        prawo= new treeavlA(x1,y1,id1,id2,typ1,x2,y2); high++;

        return 1;
    }
  }
}
else{
 if(x> x1|| (x==x1&&y>=y1) ){stop=lewo->add(x1,y1,id1,id2,typ1,x2,y2);}
else {if(prawo==NULL){prawo=new treeavlA(x1,y1,id1,id2,typ1,x2,y2);}
else stop=prawo->add(x1,y1,id1,id2,typ1,x2,y2);}
}

     if(stop)
        {

        high=max(lewo==NULL?0:lewo->high,prawo==NULL?0:prawo->high) +1;

        long long  int temp= (lewo==NULL?0:lewo->high)-(prawo==NULL?0:prawo->high);
        if( abs(temp)>1)
            {
                if(temp>0)  {   //l
                            if( (lewo->lewo==NULL?0:lewo->lewo->high)-(lewo->prawo==NULL?0:lewo->prawo->high)<0)lewo->Rrotation();
                            Lrotation();
                            }
                            else
                            {   //p
                            if(( (prawo->lewo==NULL?0:prawo->lewo->high)
                            -(prawo->prawo==NULL?0:prawo->prawo->high) )>0)
                            prawo->Lrotation();
                            Rrotation();
                            }

            return 0;
            }
        else
            {

            return 1;
            }
        }

return 0;
}


bool del()//pierwszy
    {
   if(lewo==NULL&&prawo==NULL){ return 1;}
     else if(lewo==NULL){x=prawo->x; y=prawo->y; id=prawo->id; id2=prawo->id2; typ=prawo->typ; xend=prawo->xend;yend=prawo->yend; delete prawo; prawo=NULL;}
    else{if(lewo->del()){delete lewo; lewo=NULL;}}


      high=max(lewo==NULL?0:lewo->high,prawo==NULL?0:prawo->high) +1;

        long long  int temp= (lewo==NULL?0:lewo->high)-(prawo==NULL?0:prawo->high);
        if( abs(temp)>1)
            {
                if(temp>0)  {   //l
                            if( (lewo->lewo==NULL?0:lewo->lewo->high)-(lewo->prawo==NULL?0:lewo->prawo->high)<0)lewo->Rrotation();
                            Lrotation();
                            }
                            else
                            {   //p
                            if(( (prawo->lewo==NULL?0:prawo->lewo->high)
                            -(prawo->prawo==NULL?0:prawo->prawo->high) )>0)
                            prawo->Lrotation();
                            Rrotation();
                            }

            }

 return 0;
    }


    treeavlA *take()//pierwszy
    {
   if(lewo==NULL&&prawo==NULL){ return this;}
     else if(lewo==NULL){return prawo->take();}
    else{return lewo->take();}
    }

};

class treeavlB
{
public:

int high;

int id;

double y;
double x;

double y2;
double x2;


treeavlB *lewo;
treeavlB *prawo;


void draw(int offs)
{
   if(prawo!=NULL)prawo->draw(offs+1);
for (int i=0;i<offs;i++)cout <<"   ";
cout << x ;
cout << " " ;
cout << y ;
cout << " " ;
cout << id;
cout << " " ;
cout << typ ;
cout << " " ;
cout << xend;
cout << " " ;
cout << yend <<endl;
 if(lewo!=NULL)lewo->draw(offs+1);
}



treeavlB()//puste drzewo
{typ='e';
}

treeavlB(double x1,double y1,int id1,int id2,char typ1,double x2,double y2)//leaf
{
x=x1;
y=y1;
xend=x2;
yend=y2;
typ=typ1;
id=id1;
id2=id2;

high=1;
lewo=NULL;
prawo=NULL;
}


void Lrotation()
{double  temp =x;
x=lewo->x;
lewo->x=temp;

temp =y;
y=lewo->y;
lewo->y=temp;

temp =xend;
xend=lewo->xend;
lewo->xend=temp;

temp =yend;
yend=lewo->yend;
lewo->yend=temp;

char temp2 =typ;
typ=lewo->typ;
lewo->typ=temp2;

int temp3=id;
id=lewo->id;
lewo->id=temp3;

 temp3=id2;
id2=lewo->id2;
lewo->id2=temp3;


treeavlB *pom= prawo;
prawo= lewo;
lewo=prawo->lewo;
prawo->lewo=prawo->prawo;
prawo->prawo=pom;

prawo->high=max(prawo->lewo==NULL?0:prawo->lewo->high,prawo->prawo==NULL?0:prawo->prawo->high) +1;


high=max(lewo==NULL?0:lewo->high,prawo==NULL?0:prawo->high) +1;

}

void Rrotation()
{

double  temp =x;
x=prawo->x;
prawo->x=temp;

temp =yend;
yend=prawo->yend;
prawo->yend=temp;

 temp =xend;
xend=prawo->xend;
prawo->xend=temp;

temp =y;
y=prawo->y;
prawo->y=temp;

char temp2 =typ;
typ=prawo->typ;
prawo->typ=temp2;

int temp3=id;
id=prawo->id;
prawo->id=temp3;

temp3=id2;
id2=prawo->id2;
prawo->id2=temp3;


treeavlB *pom= lewo;
lewo= prawo;
prawo=lewo->prawo;
lewo->prawo=lewo->lewo;
lewo->lewo=pom;


lewo->high=max(lewo->lewo==NULL?0:lewo->lewo->high,lewo->prawo==NULL?0:lewo->prawo->high) +1;



high=max(lewo==NULL?0:lewo->high,prawo==NULL?0:prawo->high) +1;

}


bool add(double x1,double y1,int id1,int id2,char typ1,double x2,double y2)
{bool stop=1;

if(typ=='e'){x=x1;y=y1;id=id1;typ=typ1;xend=x2;yend=y2; return 0;}

if(lewo==NULL)
{
  if(x>x1||(x==x1&&y>=y1)  )//wlewo
        {lewo= new treeavlB(x1,y1,id1,id2,typ1,x2,y2); high++;return 1;}
  else{
    if(prawo!=NULL)
        stop=prawo->add(x1,y1,id1,id2,typ1,x2,y2);
    else{
        prawo= new treeavlB(x1,y1,id1,id2,typ1,x2,y2); high++;

        return 1;
    }
  }
}
else{
 if(x> x1|| (x==x1&&y>=y1) ){stop=lewo->add(x1,y1,id1,id2,typ1,x2,y2);}
else {if(prawo==NULL){prawo=new treeavlB(x1,y1,id1,id2,typ1,x2,y2);}
else stop=prawo->add(x1,y1,id1,id2,typ1,x2,y2);}
}

     if(stop)
        {

        high=max(lewo==NULL?0:lewo->high,prawo==NULL?0:prawo->high) +1;

        long long  int temp= (lewo==NULL?0:lewo->high)-(prawo==NULL?0:prawo->high);
        if( abs(temp)>1)
            {
                if(temp>0)  {   //l
                            if( (lewo->lewo==NULL?0:lewo->lewo->high)-(lewo->prawo==NULL?0:lewo->prawo->high)<0)lewo->Rrotation();
                            Lrotation();
                            }
                            else
                            {   //p
                            if(( (prawo->lewo==NULL?0:prawo->lewo->high)
                            -(prawo->prawo==NULL?0:prawo->prawo->high) )>0)
                            prawo->Lrotation();
                            Rrotation();
                            }

            return 0;
            }
        else
            {

            return 1;
            }
        }

return 0;
}


bool del()//pierwszy
    {
   if(lewo==NULL&&prawo==NULL){ return 1;}
     else if(lewo==NULL){x=prawo->x; y=prawo->y; id=prawo->id; id2=prawo->id2; typ=prawo->typ; xend=prawo->xend;yend=prawo->yend; delete prawo; prawo=NULL;}
    else{if(lewo->del()){delete lewo; lewo=NULL;}}


      high=max(lewo==NULL?0:lewo->high,prawo==NULL?0:prawo->high) +1;

        long long  int temp= (lewo==NULL?0:lewo->high)-(prawo==NULL?0:prawo->high);
        if( abs(temp)>1)
            {
                if(temp>0)  {   //l
                            if( (lewo->lewo==NULL?0:lewo->lewo->high)-(lewo->prawo==NULL?0:lewo->prawo->high)<0)lewo->Rrotation();
                            Lrotation();
                            }
                            else
                            {   //p
                            if(( (prawo->lewo==NULL?0:prawo->lewo->high)
                            -(prawo->prawo==NULL?0:prawo->prawo->high) )>0)
                            prawo->Lrotation();
                            Rrotation();
                            }

            }

 return 0;
    }


    treeavlB *take()//pierwszy
    {
   if(lewo==NULL&&prawo==NULL){ return this;}
     else if(lewo==NULL){return prawo->take();}
    else{return lewo->take();}
    }





};



//bool add(double x1,double y1,int id1,int id2,char typ1,double x2,double y2)
int main()
{
int n;
cin >> n;
treeavlA *A=new treeavlA();
double x1,y1,x2,y2;
for(int i=0 ;i<n;i++)
{cin >> x1;
cin >> y1;
cin >> x2;
cin >> y2;
if(x1<x2||(x1==x2&&y1<y2)){int xp=x1;x1=x2;x2=xp;
                        int yp=y1;y1=y2;y2=yp;}
A->add(x1,y1,i,0,'p',x2,y2);
A->add(x2,y2,i,0,'k',x1,y1);
}
A->draw(0);
A->del();
A->draw(0);
A->del();
A->draw(0);
A->del();
A->draw(0);
A->del();
A->draw(0);
A->del();
A->draw(0);
cout << (double)3.00<<endl;

    return 0;
}




/*

#include <iostream>

#include <cstdlib>
#include <fstream>
using namespace std;

long long int ostatnio=0;

class treeavl
{
public:
long long int sum;
int val;
int high;
int sizes;

treeavl *lewo;
treeavl *prawo;

bool testx()
{
if(lewo!=NULL)lewo->testx();
if(prawo!=NULL)prawo->testx();
if(sum!=(lewo==NULL?0:lewo->sum)+(prawo==NULL?0:prawo->sum)+val)
{
 cout << "log testu:" <<endl;
 cout << val ;
cout << " " ;
cout << high ;
cout << " " ;
cout << sizes;
cout << " " ;
cout << sum <<endl;
return 1;
}


return 0;
}




{
cout << 87 << " "<<1<<" sumadobrazla:"<< sumaa(1,87) <<" "<<(suma(87) - suma(1- 1)) <<endl;


cout << 88 << " "<<1<<" sumadobrazla:"<< sumaa(1,88) <<" "<<(suma(88) - suma(1- 1)) <<endl; test2();}
draw(0);
}

void test2()
{cout << "test2" <<endl;
for(int i=1;i<91;i++)
   {cout << sumaa(i,i)<<" ";}
cout << "end2" <<endl;
}

void draw(int offs)
{

   if(prawo!=NULL)prawo->draw(offs+1);
for (int i=0;i<offs;i++)cout <<"   ";
cout << val ;
cout << " " ;
cout << high ;
cout << " " ;
cout << sizes;
cout << " " ;
cout << sum <<endl;

 if(lewo!=NULL)lewo->draw(offs+1);
}


treeavl()//puste drzewo
{sizes=0;
}

treeavl(long long int x)//leaf
{
sum=x;
val=x;
high=1;
sizes=1;
lewo=NULL;
prawo=NULL;
}


void Lrotation()
{long long  int temp =val;
val=lewo->val;
lewo->val=temp;

treeavl *pom= prawo;
prawo= lewo;
lewo=prawo->lewo;
prawo->lewo=prawo->prawo;
prawo->prawo=pom;

prawo->sum=(prawo->lewo==NULL?0:prawo->lewo->sum)+(prawo->prawo==NULL?0:prawo->prawo->sum)+prawo->val;
prawo->high=max(prawo->lewo==NULL?0:prawo->lewo->high,prawo->prawo==NULL?0:prawo->prawo->high) +1;
prawo->sizes=(prawo->lewo==NULL?0:prawo->lewo->sizes) + (prawo->prawo==NULL?0:prawo->prawo->sizes) +1;

sum=(lewo==NULL?0:lewo->sum)+(prawo==NULL?0:prawo->sum)+val;
high=max(lewo==NULL?0:lewo->high,prawo==NULL?0:prawo->high) +1;
sizes=(lewo==NULL?0:lewo->sizes) + (prawo==NULL?0:prawo->sizes) +1;
}

void Rrotation()
{
long long  int temp =val;
val=prawo->val;
prawo->val=temp;

treeavl *pom= lewo;
lewo= prawo;
prawo=lewo->prawo;
lewo->prawo=lewo->lewo;
lewo->lewo=pom;

lewo->sum =(lewo->lewo==NULL?0:lewo->lewo->sum)+(lewo->prawo==NULL?0:lewo->prawo->sum)+lewo->val;
lewo->high=max(lewo->lewo==NULL?0:lewo->lewo->high,lewo->prawo==NULL?0:lewo->prawo->high) +1;
lewo->sizes=(lewo->lewo==NULL?0:lewo->lewo->sizes) + (lewo->prawo==NULL?0:lewo->prawo->sizes) +1;

sum=(lewo==NULL?0:lewo->sum)+(prawo==NULL?0:prawo->sum)+val;
high=max(lewo==NULL?0:lewo->high,prawo==NULL?0:prawo->high) +1;
sizes=(lewo==NULL?0:lewo->sizes) + (prawo==NULL?0:prawo->sizes) +1;
}


bool add(long long  int p,long long  int x)
{bool stop=1;

if(lewo==NULL)
{
  if( p==0){lewo= new treeavl(x); high++;sizes++;
                        sum=(lewo==NULL?0:lewo->sum)+(prawo==NULL?0:prawo->sum)+val;
                        return 1;}
  else{
  if(prawo!=NULL)stop=prawo->add(p-1,x);
  else{prawo= new treeavl(x); high++;sizes++;
                                    sum=(lewo==NULL?0:lewo->sum)+(prawo==NULL?0:prawo->sum)+val;
                                    return 1;}
  }
}
else{

sizes++;

 if(p<= lewo->sizes){stop=lewo->add(p,x);}
else {if(prawo==NULL){prawo=new treeavl(x);} else stop=prawo->add((p-(lewo->sizes)-1 ),x);}
}
     if(stop)
        {
        sum=(lewo==NULL?0:lewo->sum)+(prawo==NULL?0:prawo->sum)+val;
        high=max(lewo==NULL?0:lewo->high,prawo==NULL?0:prawo->high) +1;
        sizes=(lewo==NULL?0:lewo->sizes)+(prawo==NULL?0:prawo->sizes)+1;
        long long  int temp= (lewo==NULL?0:lewo->high)-(prawo==NULL?0:prawo->high);
        if( abs(temp)>1)
            {
                if(temp>0)  {   //l
                            if( (lewo->lewo==NULL?0:lewo->lewo->high)-(lewo->prawo==NULL?0:lewo->prawo->high)<0)lewo->Rrotation();
                            Lrotation();
                            }
                            else
                            {   //p
                            if(( (prawo->lewo==NULL?0:prawo->lewo->high)
                            -(prawo->prawo==NULL?0:prawo->prawo->high) )>0)
                            prawo->Lrotation();
                            Rrotation();
                            }
                              sum=(lewo==NULL?0:lewo->sum)+(prawo==NULL?0:prawo->sum)+val;
            return 0;
            }
        else
            {
              sum=(lewo==NULL?0:lewo->sum)+(prawo==NULL?0:prawo->sum)+val;
            return 1;
            }
        }
sum=(lewo==NULL?0:lewo->sum)+(prawo==NULL?0:prawo->sum)+val;
return 0;
}


bool del(long long int p)
    { sizes--;
    if(p-(lewo==NULL?0:lewo->sizes)==1)   {if(lewo==NULL&&prawo==NULL){  sum=(lewo==NULL?0:lewo->sum)+(prawo==NULL?0:prawo->sum)+val; return 1;}
                                             else if(lewo==NULL){val=prawo->val;
                                                                 high=prawo->high;
                                                                 sizes= prawo->sizes;
                                                                delete prawo;
                                                                prawo=NULL;
                                                                }
                                             else if(prawo==NULL){val=lewo->val;
                                                                 high=lewo->high;
                                                                 sizes= lewo->sizes;
                                                                delete lewo;
                                                                lewo=NULL;
                                                                }
                                            else{
                                                        bool oh=(lewo->prawo==NULL&&lewo->lewo==NULL);
                                                   val=lewo->najwiekszy(); //znajdz najwiekszego z lewej i go usun
                                                     if(oh)lewo=NULL;
                                                }
                                            }
     else if(p<= (lewo==NULL?0:lewo->sizes))
     {if(lewo->del(p)){delete lewo;lewo=NULL;}
     }
    else { if(prawo->del((p-(lewo==NULL?0:lewo->sizes)-1 ))  ){delete prawo; prawo=NULL;}}

        sum=(lewo==NULL?0:lewo->sum)+(prawo==NULL?0:prawo->sum)+val;
      high=max(lewo==NULL?0:lewo->high,prawo==NULL?0:prawo->high) +1;
      sizes=(lewo==NULL?0:lewo->sizes)+(prawo==NULL?0:prawo->sizes)+1;
        long long  int temp= (lewo==NULL?0:lewo->high)-(prawo==NULL?0:prawo->high);
        if( abs(temp)>1)
            {
                if(temp>0)  {   //l
                            if( (lewo->lewo==NULL?0:lewo->lewo->high)-(lewo->prawo==NULL?0:lewo->prawo->high)<0)lewo->Rrotation();
                            Lrotation();
                            }
                            else
                            {   //p
                            if(( (prawo->lewo==NULL?0:prawo->lewo->high)
                            -(prawo->prawo==NULL?0:prawo->prawo->high) )>0)
                            prawo->Lrotation();
                            Rrotation();
                            }

            }

  sum=(lewo==NULL?0:lewo->sum)+(prawo==NULL?0:prawo->sum)+val;
 return 0;
    }

   long long  int najwiekszy()
    {long long int ret;
    sizes--;
    bool oh=0;
     if(prawo!=NULL)if(prawo->prawo==NULL&&prawo->lewo==NULL)oh=1;
    if(prawo==NULL) {if(lewo!=NULL){ ret=val;
                                    val=lewo->val;
                                    high=lewo->high;
                                    sizes= lewo->sizes;
                                    delete lewo;
                                    lewo=NULL;
                                      sum=(lewo==NULL?0:lewo->sum)+(prawo==NULL?0:prawo->sum)+val;
                                    return ret;
                                    }else
                                    {
                                     ret=val;

                                    return ret;
                                    }

                    }else { ret=prawo->najwiekszy();}

         if(oh){delete prawo;prawo=NULL;}
        high=max(lewo==NULL?0:lewo->high,prawo==NULL?0:prawo->high) +1;
        sizes=(lewo==NULL?0:lewo->sizes)+(prawo==NULL?0:prawo->sizes)+1;
         sum=(lewo==NULL?0:lewo->sum)+(prawo==NULL?0:prawo->sum)+val;
        long long int temp= (lewo==NULL?0:lewo->high)-(prawo==NULL?0:prawo->high);
        if( abs(temp)>1)
            {
                if(temp>0)  {   //l
                            if( (lewo->lewo==NULL?0:lewo->lewo->high)-(lewo->prawo==NULL?0:lewo->prawo->high)<0)lewo->Rrotation();
                            Lrotation();
                            }
                            else
                            {   //p
                            if(( (prawo->lewo==NULL?0:prawo->lewo->high)
                            -(prawo->prawo==NULL?0:prawo->prawo->high) )>0)
                            prawo->Lrotation();
                            Rrotation();
                            }

            }

    sum=(lewo==NULL?0:lewo->sum)+(prawo==NULL?0:prawo->sum)+val;
    return ret;
    }


    long long int suma( int p)
    { if(p==0){return 0;}
     int x=(lewo==NULL?0:lewo->sizes);
    if(x<p)return (lewo==NULL?0:lewo->sum) + val + (prawo==NULL?0:prawo->suma(p-x-1) );
    else
    if(x >p)return (lewo==NULL?0:lewo->suma(p) );
    else
    return (lewo==NULL?0:lewo->sum);

    }


     long long int sumaa(int p,int p2)
    {
    int x=(lewo==NULL?0:lewo->sizes)+1;
    if(x<p)return (prawo==NULL?0:prawo->sumaa(p-x,p2-x) );
    else
    if(x >p2)return (lewo==NULL?0:lewo->sumaa(p,p2) );
    else
    return val +  (prawo==NULL?0:prawo->sumaa(p-x,p2-x) ) + (lewo==NULL?0:lewo->sumaa(p,p2) );

    }


};


int main()
{
bool sss=0;
//fstream plik;
//plik.open( "txt4.txt", std::ios::in | std::ios::out );
long long  int p,x,p2;
char operation;
long long  int n;
treeavl *lista=new treeavl();
cin>> n;
for(int i=0;i<n;i++)
{
cin >> operation;
switch(operation)   {
                    case 'I':
                    {
                 cin >> p;//pozycja

                  cin >> x;//val
                    if (lista->sizes==0){lista=new treeavl(x);}else
                   lista->add(p,x);
                   //lista->sum=(lista->lewo==NULL?0:lista->lewo->sum)+(lista->prawo==NULL?0:lista->prawo->sum)+lista->val;
                    // if(!sss){sss=lista->testx();cout << p << " "<<i<<endl;   }
                     //if(i==362)lista->draw(1);

                    }
                    break;
                    case 'D':
                    {
             cin >> p;

                   if(lista->del(p))lista->sizes=0;

                    //lista->test();
                     }
                    break;
                    case 'S':
                    {
                        cin>> p;
                   cin >> p2;
                          long long int odp =(lista->suma(p2) - lista->suma(p- 1));
                          //long long int odp = lista->sumaa(p,p2);
                          //cout << lista->sumaa(p,p2);
                          //cout << "  ";
                            cout << odp <<endl;

                            // lista->test();

                    }
                    break;
                     case 'd':
                    {
                        lista->test();
                          cout << " " <<endl;
                        //lista->draw(0);
                    }
                    break;

                    }
}




    return 0;
}


*/
