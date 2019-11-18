#include <iostream>
#include <cstring>
#include <map>

using namespace std;

string key;
int leftShift[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

int PC1[56] = {57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};

int PC2[56] = {14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};

string binToHex(string binary)
{
    std :: map<string,char> h2b;
    h2b["0000"] = '0';
    h2b["0001"] = '1';
    h2b["0010"] = '2';
    h2b["0011"] = '3';
    h2b["0100"] = '4';
    h2b["0101"] = '5';
    h2b["0110"] = '6';
    h2b["0111"] = '7';
    h2b["1000"] = '8';
    h2b["1001"] = '9';
    h2b["1010"] = 'A';
    h2b["1011"] = 'B';
    h2b["1100"] = 'C';
    h2b["1101"] = 'D';
    h2b["1110"] = 'E';
    h2b["1111"] = 'F';

    string hexa = "";
    for(int i=0;i<binary.size();i+=4)
    {
        string subBinary = "";
        for(int j=0;j<4;j++)
            subBinary += binary[i+j];
        hexa += h2b[subBinary];
    }
    return hexa;
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

string leftRotate(string subKey, int n)
{
    string temp = subKey;
    for(int i=0;i<n;i++)
    {
        string rotate = "";
        for(int j=1;j<temp.size();j++)
            rotate += temp[j];
        rotate += temp[0];
        temp = rotate;
    }
    return temp;
}

void encryption(string key)
{
    string PC1String = "";
    for(int i=0;i<56;i++)
    {
        PC1String += key[PC1[i]-1];
    }
    string left,right;
    left = PC1String.substr(0,28);
    right = PC1String.substr(28,28);
    //cout<<left<<"\n"<<right;
    for(int i=0;i<16;i++)
    {
        left = leftRotate(left,leftShift[i]);
        right = leftRotate(right,leftShift[i]);
        string combine = left + right;
        string subKey = "";
        for(int j=0;j<48;j++)
        {
            subKey += combine[PC2[j]-1];
        }
        //cout<<"\n"<<"Key at round "<<i+1<<" = "<<subKey;
        cout<<"\n"<<"Key at round "<<i+1<<" = \t"<<(subKey)<<"\t->\t"<<binToHex(subKey);

        //cout<<"\n"<<"Key at round "<<i+1<<" = "<<binToHex(subKey);
    }
}

int main()
{
    cout << "Enter an key in hexadecimal format" << endl;
   // cin>>key;
    //cout<<"133457799BBCDEFF1\n";
    key = "133457799BBCDEFF";
    string binary=hexToBin(key);
    cout<<"Binary value "<<binary<<endl;
    encryption(binary);
    return 0;
}


/*OUTPUT

Enter an key in hexadecimal format
133457799BBCDEFF

Key at round 1 = 1B02EFFC7976
Key at round 2 = 79AED9DFC9E5
Key at round 3 = 55FC8AC2EFD9
Key at round 4 = 72ADD6FBB71D
Key at round 5 = 7CEC07FB57AA
Key at round 6 = 63A53E5C7B2F
Key at round 7 = EC84B7F678FC
Key at round 8 = F78A3AE1BBFB
Key at round 9 = E0DBEBEFE799
Key at round 10 = B1F347BB574F
Key at round 11 = 215FD3DED3A6
Key at round 12 = 7571F5D46FED
Key at round 13 = 97C5D1FABAD9
Key at round 14 = 5F43B7F3F73B
Key at round 15 = BF918D3F3F2A
Key at round 16 = CB3D8B1E57F7

*/
