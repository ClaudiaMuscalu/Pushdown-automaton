#include <iostream>
#include<fstream>
#include<string.h>
using namespace std;

void citire(int a[100][100], char b[][10][10][10], int &nr_stari, int &stare_i, int &stare_f, char cuvant[ ])
{
    ifstream fin("Citire.in");
    fin>>nr_stari;
    fin>>stare_i;
    fin>>stare_f;
    int k,i,j,st1,st2,s;
    char simb,vf,lit[10];

    for(i=0;i<nr_stari;i++)
    {
        for(j=0;j<nr_stari;j++)
            a[i][j]=0;
    }

    fin>>k;

    for(i=0;i<k;i++)
    {
        fin>>st1>>st2;
        fin>>a[st1][st2];
    }

    fin>>s;
    for(i=0;i<s;i++)
    {   fin>>st1>>st2;
        for(int j=0;j<a[st1][st2];j++)
        {
            fin>>simb;
            fin>>vf;
            fin>>lit;

            b[st1][st2][j][0]=simb;
            b[st1][st2][j][1]='|';
            b[st1][st2][j][2]=vf;
            b[st1][st2][j][3]='|';
            b[st1][st2][j][4]='\0';
            strcat(b[st1][st2][j],lit);
        }
    }
    fin>>cuvant;
}

void push_st(char stiva[], int &varf, char x)
{
    stiva[++varf]=x;
}

void pop_st(char stiva[],int &varf)
{
    stiva[varf]='\0';
    varf--;
}

int verificare( int a[100][100], char b[ ][10][10][10], int nr_stari, int stare_i, int stare_f, char cuvant[ ], char stiva[ ], int &vf)
{
    if(cuvant[0]=='\0'&&stare_i==stare_f&&stiva[0]=='\0')
        return 1;

    int i,j;
    unsigned int k;
    for(i=0;i<nr_stari;i++)
    {
        if(a[stare_i][i]!=0)
        {
            for(j=0;j<a[stare_i][i];j++)
            {   if((cuvant[0]==b[stare_i][i][j][0]||b[stare_i][i][j][0]=='#')&&stiva[vf]==b[stare_i][i][j][2])
                {
                    if(b[stare_i][i][j][0]!='#')
                        strcpy(cuvant,cuvant+1);

                    for(k=4;k<strlen(b[stare_i][i][j])-1;k++)
                        push_st(stiva,vf,b[stare_i][i][j][k]);

                    if(b[stare_i][i][j][4]=='#')
                        pop_st(stiva,vf);

                    return verificare(a,b,nr_stari,i,stare_f,cuvant,stiva,vf);
                }
            }
        }
    }
    return 0;
}

void afisare(int a[100][100], char b[][10][10][10], int nr_stari, int stare_i, int stare_f, char cuvant[])
{
    int i,j,k;
    cout<<nr_stari<<endl;
    cout<<stare_i<<endl;
    cout<<stare_f<<endl;
    for(i=0;i<nr_stari;i++)
    {   for(j=0;j<nr_stari;j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }

    for(i=0;i<nr_stari;i++)
    {
        for(j=0;j<nr_stari;j++)
        {
            if(a[i][j]!=0)
            {   cout<<i<<" "<<j<<endl;
                for(k=0;k<a[i][j];k++)
                    cout<<b[i][j][k]<<endl;
            }
        }
    }

}
int main()
{   int a[100][100], nr_stari, stare_i, stare_f;
    char b[20][10][10][10],cuvant[100], stiva[100];
    int vf=0;
    stiva[vf]='Z';
    stiva[vf+1]='\0';
    citire(a,b,nr_stari,stare_i,stare_f,cuvant);

    afisare(a,b,nr_stari,stare_i,stare_f,cuvant);
    if(verificare(a,b,nr_stari,stare_i,stare_f,cuvant,stiva,vf)==1)
        cout<<"cuvant acceptat";
    else
        cout<<"cuvant neacceptat";
    return 0;
}
