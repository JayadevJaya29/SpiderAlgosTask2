#include<vector>
#include<bits/stdc++.h>
#include<algorithm>
#include<cstring>
#include<iterator>
#include<limits>
#include<cctype>
using namespace std;
struct trie
{
	bool isend;
	int repeat;
	struct trie *children[27];
};
struct disp
{
    string s;
    int rep;
};
struct trie * getTrie()
{
	struct trie *t=new trie;
	t->isend=false;
	t->repeat=0;
	for(int i=0;i<27;i++)
        t->children[i]=NULL;
	return t;
}
void insert(struct trie *root,string s)
{
	struct trie *t=root;
	for(int i=0;i<s.length();i++)
    {
        int index;
        if(isspace(s[i]))
            index=26;
        else
            index=s[i]-'a';
        if(!t->children[index])
          t->children[index]=getTrie();
        t=t->children[index];
    }
    t->isend=true;
    t->repeat=t->repeat+1;
}
int isleaf(struct trie *t)
{
    if(t->isend)
        return 1;
    else
        return 0;
}
int isdeletable(struct trie *t)
{
    for(int i=0;i<27;i++)
    {
        if(t->children[i])
            return 0;
    }
    return 1;
}
int deletenode(struct trie *t,string s,int level,int length)
{
    if(t)
    {
        if(level==length && isleaf(t))
        {
                t->isend=false;
                if(isdeletable(t))
                    return 1;
                else
                    return 0;
        }
        else
        {
            int index;
            if(isspace(s[level]))
                index=26;
            else
                index=s[level]-'a';
            if(deletenode(t->children[index],s,level+1,length))
            {
                delete(t->children[index]);
                t->children[index]=NULL;
                if((!isleaf(t))&&isdeletable(t))
                    return 1;
                else
                    return 0;
            }
        }
    }
    return 0;
}
void deletetrie(struct trie *root,string s)
{
    struct trie *t=root;
    int l=s.length();
    if(l)
        deletenode(t,s,0,l);
}
disp addtodisp(string s,int r)
{
   disp d;
   d.rep=r;
   d.s=s;
   return d;
}
bool sorting(disp d1,disp d2)
{
    return(d1.rep>d2.rep);
}
void autocomplete(struct trie *t,string s,vector<disp> &v1)
{
    if(t->isend)
    {
       v1.push_back(addtodisp(s,t->repeat));
    }
    if(isdeletable(t))
        return;
    for(int i=0;i<27;i++)
    {
        if(t->children[i])
        {
            char x;
            if(i==26)
                x=' ';
            else
                x=i+'a';
            s.push_back(x);
            autocomplete(t->children[i],s,v1);
            s.pop_back();
        }
    }
}
int query(struct trie *t,string s)
{
    int level=0;
    int l=s.length();
    int a=5;
    vector <disp> v1;
    for(int i=0;i<l;i++)
    {
        int index;
        if(isspace(s[i]))
            index=26;
        else
            index=s[i]-'a';
        if(!t->children[index])
            return 0;
        t=t->children[index];
    }
    autocomplete(t,s,v1);
    sort(v1.begin(),v1.end(),sorting);
    if(v1.size()<a)
        a=v1.size();
    for(int i=0;i<a;i++)
        cout<<v1[i].s<<"\n";
    cout<<"\n";
}
bool searchtrie(struct trie *root,string s)
{
    struct trie *t=root;
    for(int i=0;i<s.length();i++)
    {
        int index;
        if(isspace(s[i]))
            index=26;
        else
            index=s[i]-'a';
        if(!t->children[index])
            return 0;
        t=t->children[index];
    }
    return (t!=NULL&&isleaf(t));
}
void revert(struct trie *root, vector<disp> &m,int z)
{
    int index=m.size()-1;
    for(int i=0;i<z;i++)
    {
        if(m[index].rep==1)
            deletetrie(root,m[index].s);
        else
            insert(root,m[index].s);
        m.pop_back();
        index--;
    }
}
int main()
{
	vector<string> v;
	vector<disp> m;
	int n,q;
	string x,y;
	struct trie *root=getTrie();
	cout<<"Enter n, searches, q, queries \n";
	cin>>n;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	for(int i=0;i<n;i++)
    {
        if(getline(cin,x))
            insert(root,x);
    }
    cin>>q;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for(int i=0;i<q;i++)
    {
        getline(cin,y);
        v.push_back(y);
    }
    for(int i=0;i<q;i++)
    {
        if((v[i][0]=='a')&&(v[i][1]=='d')&&(v[i][2]=='d')&&(v[i][3]==' '))
        {
            v[i].erase(v[i].begin()+0,v[i].begin()+4);
            m.push_back(addtodisp(v[i],1));
            insert(root,v[i]);
        }
        else if((v[i][0]=='r')&&(v[i][1]=='e')&&(v[i][2]=='m')&&(v[i][3]=='o')&&(v[i][4]=='v')&&(v[i][5]=='e')&&(v[i][6]==' '))
        {
            v[i].erase(v[i].begin()+0,v[i].begin()+7);
            if(searchtrie(root,v[i]))
            {
                m.push_back(addtodisp(v[i],0));
                deletetrie(root,v[i]);
            }
        }
        else if((v[i][0]=='q')&&(v[i][1]=='u')&&(v[i][2]=='e')&&(v[i][3]=='r')&&(v[i][4]=='y')&&(v[i][5]==' '))
        {
            v[i].erase(v[i].begin()+0,v[i].begin()+6);
            query(root,v[i]);
        }
        else if((v[i][0]=='r')&&(v[i][1]=='e')&&(v[i][2]=='v')&&(v[i][3]=='e')&&(v[i][4]=='r')&&(v[i][5]=='t')&&(v[i][6]==' '))
        {
           if(isdigit(v[i][7]))
            {
                char *z=&v[i][7];
                int w=atoi(z);
                if(m.size()>=w)
                    revert(root,m,w);
            }
        }
    }
}
