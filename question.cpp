#include<bits/stdc++.h>
using namespace std;
struct var{
   int size;
   int address;
};
map<string,var> variables;
int arr[100];
bool isMalloc(string s,string &name, int &size){
//	cout<<"enter in malloc"<<endl;
	if(s.length()<11){
		return false;
	}
	string xp="";
	int i=0;
	int l= s.length();
	while(i<l && s[i]!='='){
		xp += s[i];
		i++;
	}
	if(s[i]=='='){
		i++;
	}
	if(i+7<l && s[i]=='m'&&s[i+1]=='a'&&s[i+2]=='l'&&s[i+3]=='l'&&s[i+4]=='o'&&s[i+5]=='c'&&s[i+6]=='('){
		i = i+7;
		int retval = 0;
		while(i<l && s[i]!=')'){
			retval = 10 * retval + (s[i]-'0');
			i++;
		}
		if(s[i]==')'){
			name = xp;
			size = retval;
			return  true;
		}else{
			cout<<"wrong syntax for malloc"<<endl;
		}
	}
	return false;
}

bool isFree(string s, string &name){
	int i=0;
	int l = s.length();
	string xp="";
	if(l<7){
		return false;
	}
	if(s[i]=='f'&&s[i+1]=='r'&&s[i+2]=='e'&&s[i+3]=='e'&&s[i+4]=='('){
		i = i+5;
		while(i<l && s[i]!=')'){
			xp += s[i];
			i++;
		}
		if(s[i]==')'){
			name = xp;
			return true;
		}else{
			cout<<"wrong syntax for free()"<<endl;
		}
	}
	return false;
}

int main(){
	cout<<"\n\n\n\t\t\t\t\t\t\t****My Heap*******\n\n\n\n\n";
	// this will work like a virtual heap
	// here first will be size  of free and second will be pointer to the next free
	arr[0] = 98;
	arr[1] = 2;
	// this map will take care of the newly allocated variables
	// variables.insert({});
	// .delete()
	int i=0;
	string s;
//	int totalFreeMem = 98;
	int head;
	head=0;
	arr[head]=100;
	arr[head+1] = -1;// means there is this one only block of free memory
	// arr[head+1] keeps next place where size of free mem is present
	// i have to implement a = malloc(10) or free(a)
	while(true){
		cout<<"heapVijendra$ ";
		getline(cin,s);
		int size;
		string name;
		if(s=="exit()")
		{
			break;
		}
		else if(s=="display_status")
		{
			// just display the status
			// here i have to show the status about the free list
			int headmap = 0;
			while(headmap!=-1)
			{
				if(arr[headmap]==0){
					// condition that this mem is used
					cout<<"used memory at address "<<headmap+2<<endl;
				}else{
					cout<<arr[headmap]<<" memory and next pointer is "<<arr[headmap+1]<<endl;
				}
				headmap = arr[headmap+1];
			} 
		}
		else if(s=="coalesce_memory")
		{
			// just merge the free memory
			int headmap=0;
			while(headmap!=-1)
			{
				if(arr[headmap]!=0 && arr[arr[headmap+1]]!=0)
				{
					arr[headmap] = arr[headmap] + arr[arr[headmap+1]];
					arr[headmap+1] = arr[arr[headmap+1]+1];
				}
				else
				{
					headmap = arr[headmap+1];
				}
			}
		}
		else if(isFree(s,name))
		{
			if(variables.find(name)!= variables.end())
			{
				var avr = variables[name];
				arr[avr.address-2] = avr.size+2;
				variables.erase(name);
				cout<<"variable "<<name<<" is deleted \n";
			}
			else
			{
				cout<<"variable "<<name<<" is not present"<<endl;
			}
			cout<<name<<endl;
		}else if(isMalloc(s,name,size))
		{
			var avr;
			
			if(variables.find(name)==variables.end())
			{
				// address we have to store
				int temphead = head;
					while(true && temphead!=-1)
					{
						
						if(arr[temphead]>=size+2)
						{
							avr.address = temphead+2;
							avr.size = size;
							variables.insert({name,avr});
							cout<<"inserted "<<name<<" "<<temphead+2<<endl;
							head = temphead + size + 2;
							arr[head]=arr[temphead]-(size+2);
							arr[head+1] = -1;
							arr[temphead] = 0;
							arr[temphead+1] = head;
							break;
						}
						else
						{
							temphead = arr[temphead+1];
						}
			  		}
				  if(temphead==-1)
				  {
				  	cout<<"not possible"<<endl;
				  }
			}
			else
			{
				cout<<"variable "<<name<<" is already present: "<<endl;
			}
			//cout<<name<<" "<<size<<endl;
		}
		else
		{
			cout<<"wrong input\n";
		}
	}
	return 0;
}
