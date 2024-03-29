#include <bits/stdc++.h>
using namespace std;

int expPermute[] = {
	32, 1 , 2 , 3 , 4 , 5 ,
	4 , 5 , 6 , 7 , 8 , 9 ,
	8 , 9 , 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1 };

string expansionPermute(string input)
{
	string res = "";
	for(int i=0; i<48; i++)
	{
		res += input[expPermute[i]-1];
	}
	return res;
}

string XOR(string input1, string input2)
{
	string res = "";
	for(int i=0; i<input1.length(); i++)
	{
		res += (input1[i] == input2[i]) ? "0" : "1";
	}
	return res;
}
string hexToBin(string hexa)
{
    std :: map <char,string> h2b;
    h2b['0'] = "0000";
    h2b['1'] = "0001";
    h2b['2'] = "0010";
    h2b['3'] = "0011";
    h2b['4'] = "0100";
    h2b['5'] = "0101";
    h2b['6'] = "0110";
    h2b['7'] = "0111";
    h2b['8'] = "1000";
    h2b['9'] = "1001";
    h2b['A'] = "1010";
    h2b['B'] = "1011";
    h2b['C'] = "1100";
    h2b['D'] = "1101";
    h2b['E'] = "1110";
    h2b['F'] = "1111";

    string binary = "";

    for(int i=0;i<hexa.size();i++)
    {
        binary += h2b[hexa[i]];
    }
    return binary;
}
int main()
{
	int i; // round i
	//unsigned long long hexInput;
	string hexInput;
	string Ki; // ith round key
	ifstream fin;

	cout << "\nEnter Round number (i) : ";
	cin >> i;

	cout << "Enter 64-bit (i-1)th round output in hex: " ;
	//cin >> hex >> hexInput;
		//getline(cin,hexInput);
		cin>>hexInput;
		cout<<hexInput<<endl;
	//string input = bitset<64>(hexInput).to_string();
	string input=hexToBin(hexInput);
	cout<<input<<endl;
	fin.open("keygen.txt");
	for(int j=1; j<=i; j++)
	{
		fin >> Ki;
	}

	if(Ki.length() == 0)
	{
		cout << "\nkeygen.txt not found !!! \n" << endl;
		exit(1);
	}

	// To insert key manually uncomment this
	// unsigned long long hexKey;
	//cout << "Enter 48 bit key for ith round: " ;
	//cin >> hex >> hexKey;
	//Ki = bitset<48>(hexKey).to_string();

	cout << "\n64-bit Binary Input = " << input << endl ;
	cout << "key for ith round (Ki) = " << Ki << endl ;

	string Ri_1 = input.substr(32,32); // 32 bit Right half of input R[i-1]
	cout << "\nRight half of 64-bit input, Ri_1 = " << Ri_1 << endl;

	string R48 = expansionPermute(Ri_1);
	cout << "Ri_1 after expansion permutation = " << R48 << endl;

	string sBoxInput = XOR(R48, Ki);
	cout << "\nInput to s-box : " << sBoxInput << endl << endl;
}