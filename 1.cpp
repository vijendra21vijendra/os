#include<bits/stdc++.h>
using namespace std;

struct mlist{
	int addr;
	int size;
	int magic;
};

struct var{
	string name;
	int addr;
	int size;
};

void init(vector<struct mlist> &freelist)
{
	struct mlist l;
	l.addr =0;
	l.size =100;
	
	freelist.push_back(l);
}

int isMalloc(string s)
{
	int i=0;
	while(i<s.length()&&s[i]!='m')
	{
		i++;
	}
	
	if(i>=s.length())
	return 0;
//	else if(i+6>=s.length())
//	return 0;
	
	if(s[i]=='m'&&s[i+1]=='a'&&s[i+2]=='l'&&s[i+3]=='l'&&s[i+4]=='o'&&s[i+5]=='c')
	{
		if(s[i+6]=='(')
		{
			int j=i+7;
			while(j<s.length()&&s[j]-'0'>=0&&s[j]-'0'<=9)
			j++;
			
			if(j>=s.length())
			return 0;
			else if(s[j]==')')
			return 1;
			else
			return 0; 
			
		}
		else 
		{
			cout<<"error in malloc syntax"<<endl;
			return 0;
		}
		return 1;
	}
	return 0;
}

int isFree(string s)
{
	if(s[0]=='f'&&s[1]=='r'&&s[2]=='e'&&s[3]=='e')
	{
		if(s[4]=='(')
		{
			int j=5;
			while(j<s.length()&&s[j]!=')')
			j++;
			
			if(j>=s.length())
			{
				cout<<"error in free syntax"<<endl;
				return 0;
			}
			else
			return 1;
		}
		else
		{
			cout<<"error in free syntax"<<endl;
			return 0;
		}
	}
}

int isCoalese(string s)
{
	if(s =="coalese_memory")
	return 1;
	
	return 0;
}

int isDisplay(string s)
{
	if(s =="display_status")
	return 1;
	
	return 0;
}

int getAddress(vector<struct mlist> &freelist,int size)
{
	int i=0;
	for(i=0;i<freelist.size();i++)
	{
		if(freelist[i].size>size)
		{
			freelist[0].size-=size+1;
			int a=freelist[0].addr;
			freelist[0].addr +=(size+1);
			return a;
		}
		else if(freelist[0].size==size)
		{
			freelist[0].size-=size;
			int a =freelist[0].addr;
			freelist.erase(freelist.begin()+i);
			return a;
		}
	}
}

bool cmp(struct mlist x,struct mlist y)
{
	return x.addr<y.addr;
}

int main()
{
	vector<struct mlist> freelist;
	init(freelist);
	
	//vector<struct var> allocVariables;
	map<string,struct var> allocVariables;
	
	string s;
	while(1)
	{
		cout<<"Shell$ ";
		cin>>s;
		
		if(s=="exit")
		break;
		else if(isMalloc(s) ==1)
		{
			string name ;
			int size=0;
			
			int j=0;
			while(j<s.length()&&s[j]!='=')
			{
				name.push_back(s[j]);
				j++;
			}
			cout<<name<<endl;
			
			while(j<s.length()&&!(s[j]-'0'<=9&&s[j]-'0'>=0))
			{
				j++;
			}
			
			while(j<s.length()&&(s[j]-'0'<=9&&s[j]-'0'>=0))
			{
				size=size*10+(s[j]-'0');
				j++;
			}
			
			struct var v;
			v.name =name;
			v.size =size+2;
			v.addr =getAddress(freelist,v.size-1);
			
			allocVariables.insert({name,v});
		}
		else if(isFree(s) ==1)
		{
			string name;
			int j=5;
			while(j<s.length()&&s[j]!=')')
			{
				name.push_back(s[j]);
				j++;
			}
			cout<<name<<endl;
			
			struct var k =allocVariables[name];
			struct mlist l;
			l.addr =k.addr;
			l.size =k.size;
			
			freelist.push_back(l);
			sort(freelist.begin(),freelist.end(),cmp);
			allocVariables.erase(name);
		}
		else if(isCoalese(s) ==1)
		{
			int flag=0;
			for(int i=0;i<freelist.size()-1;i++)
			{
				if(freelist[i].addr+freelist[i].size ==freelist[i+1].addr)
				{
					flag=1;
					freelist[i].size+=freelist[i+1].size;
					freelist.erase(freelist.begin()+i+1);
					i--;
				}
			}
			
			if(flag==0)
			cout<<"Memory not coalesced, no adjacent free memory chunks found. "<<endl;
			else if(flag==1)
			cout<<"Memory coalesced successfully."<<endl;
		}
		else if(isDisplay(s) ==1)
		{
			cout<<"Free List :"<<endl;
			cout<<"\tAddr Size : "<<endl;
			for(int i=0;i<freelist.size();i++)
			{
				cout<<"\t"<<freelist[i].addr<<" "<<freelist[i].size<<endl;
			}
			
			cout<<"\nUser Pointers :"<<endl;
			cout<<"\n";
			for(map<string,struct var>::iterator i=allocVariables.begin();i!=allocVariables.end();i++)
			{
				cout<<"\t"<<i->first<<" :"<<"Address : "<<(i->second).addr<<" :"<<"Size : "<<(i->second).size<<endl;
			}
			cout<<"\n"<<endl;
		}
		else
		{
			cout<<"\nWrong Command"<<endl;
		}
	}	
}

