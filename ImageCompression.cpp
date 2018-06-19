#include<bits/stdc++.h>
#include<vector>
#include<iterator>
#include<array>
#include<string>
#include<algorithm>
#include<limits>
using namespace std;
vector<vector<vector<int>>>v;
int image(int x1,int x2,int y1, int y2,int width,int percentage,int i)
{
    float area=width*width;
    if(width==2)
    {
        int z=(v[i][x1][y1]+v[i][x2][y1]+v[i][x1][y2]+v[i][x2][y2]);
        if((z*100)/area>=percentage)
            v[i][x1][y1]=v[i][x2][y1]=v[i][x1][y2]=v[i][x2][y2]=1;
        else if((z*100)/area<=(100-percentage))
            v[i][x1][y1]=v[i][x2][y1]=v[i][x1][y2]=v[i][x2][y2]=0;
        return z;
    }
    else
    {
        int colordensity=((image(x1+width/2,x2,y1,y2-width/2,width/2,percentage,i))+(image(x1,x2-width/2,y1,y2-width/2,width/2,percentage,i))+(image(x1,x2-width/2,y1+width/2,y2,width/2,percentage,i))+(image(x1+width/2,x2,y1+width/2,y2,width/2,percentage,i)));
        if(((colordensity*100)/area)>=percentage)
        {
            for(int j=x1;j<=x2;j++)
            {
                for(int k=y1;k<=y2;k++)
                    {
                        v[i][j][k]=1;
                    }
            }

        }
        else if(((colordensity*100)/area)<=(100-percentage))
        {
            for(int j=x1;j<=x2;j++)
            {
                for(int k=y1;k<=y2;k++)
                    v[i][j][k]=0;
            }
        }
        return colordensity;
    }
}
int main()
{
    int width,percentage,i=0;
    int x;
    string s;
    vector<int> y;
    vector<vector<int>> z;
    while(1)
    {
        cin>>width;
        if(width==0)
            break;
        cin>>percentage;
        v.push_back(z);
        for(int j=0;j<width;j++)
        {
            v[i].push_back(y);
            cin>>s;
            for(int k=0;k<width;k++)
            {
                if(s[k]=='0')
                    x=0;
                else if(s[k]=='1')
                    x=1;
                v[i][j].push_back(x);
            }
        }
        image(0,width-1,0,width-1,width,percentage,i);
        i++;
    }
    for(i=0;i<v.size();i++)
    {
        cout<<"Image "<<i+1<<":\n";
        for(int j=0;j<v[i].size();j++)
        {
            for(int k=0;k<v[i].size();k++)
                cout<<v[i][j][k];
            cout<<"\n";
        }
    }
}
