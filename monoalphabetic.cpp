#include <iostream>
#include <bits/stdc++.h>
using namespace std;
string readPlainText()
{
	ifstream fin;
	string ptext;
	fin.open("plaintext.txt");
	fin >> ptext;
	fin.close();
	return ptext;
}
string encrypt(string plaintext,string key,string uniquetext)
{
	int len=uniquetext.length();
	char arr[len][2];
	for(int i=0;i<len;i++)
	{
		arr[i][0]=uniquetext[i];
		arr[i][1]=key[i];
	}
	string ciphertext;
	for(int i=0;i<plaintext.length();i++)
	{
		for(int j=0;j<len;j++)
		{
			if(plaintext[i]==arr[j][0])
			{
				ciphertext=ciphertext+arr[j][1];
			}
		}
	}
	return ciphertext;
}
void showfrequency(string plaintext,string ciphertext)
{
	float arr[26]={0.0};
	int len=plaintext.length();
		for(int i=0;i<plaintext.length();i++)
		arr[plaintext[i]-'a']++;
	cout<<"frequency\tplaintext\tciphertext"<<endl<<"------------------------------------------------"<<endl;
	for(int i=0;i<plaintext.length();i++)
	{
		cout<<arr[plaintext[i]-'a']/len<<"\t\t"<<plaintext[i]<<"\t\t"<<ciphertext[i]<<endl;
	}
}
string fnunique(string plaintext)
{
	int len=plaintext.length(),flag;
	string uniquetext="";
	for(int i=0;i<len;i++)
	{
		flag=0;
		for(int j=0;j<uniquetext.length();j++)
		{
			if(plaintext[i]==uniquetext[j])
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
			uniquetext=uniquetext+plaintext[i];
	}
	return uniquetext;
}
string genkey(string uniquetext)
{
	srand(time(NULL));
	int sum=1,n=0;
	for(int i=1;i<=uniquetext.length();i++)
		sum=sum*i;
	int num=rand()%sum;
	string key;
	sort(uniquetext.begin(),uniquetext.end());
	do
	{
		if(n==num)
		{
			key=uniquetext;
		}
		n++;
	}while(next_permutation(uniquetext.begin(),uniquetext.end()));
	return key;

}

int main()
{
	string plaintext="hello";
	plaintext=readPlainText();
	//cout<<"enter the plaintext"<<endl;
	//cin>>plaintext;
	cout<<plaintext<<endl;
	string uniquetext,key;
	uniquetext=fnunique(plaintext);
	cout<<uniquetext<<endl;
	key=genkey(uniquetext);
	cout<<key<<endl;
	string ciphertext=encrypt(plaintext,key,uniquetext);
	showfrequency(plaintext,ciphertext);
}