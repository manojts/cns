#include <bits/stdc++.h>
using namespace std;
void generatematrix(string key,char mat[5][5])
{
	int flag[26] = {0};
    int x = 0, y = 0;
    /* Add all characters present in the key */
    for(int i=0; i<key.length(); i++)
    {
        if(key[i] == ' ') continue;
        if(key[i] == 'j') key[i] = 'i'; // i and j are filled at same position
        if(flag[key[i]-'a'] == 0)
    	{
            mat[x][y++] = key[i];
            flag[key[i]-'a'] = 1;
        }
        if(y==5) x++, y=0;
    }
    /* Add remaining characters */
    for(char ch = 'a'; ch <= 'z'; ch++)
    {
        if(ch == 'j') continue;
        if(flag[ch - 'a'] == 0)
        {
            mat[x][y++] = ch;
            flag[ch - 'a'] = 1 ;
        }
        if(y==5) x++, y=0;
    }
}
string formatMessage(string msg)
{
    for(int i=0; i<msg.length(); i++)
    {
        if(msg[i] == ' ')  msg.erase(i, 1); // remove spaces
        if(msg[i] == 'j')  msg[i] = 'i';
    }
    for(int i=1; i<msg.length(); i+=2)
    {
        if(msg[i-1] == msg[i])  msg.insert(i, "x");
    }    
    if(msg.length()%2 != 0)  msg += "x";
    return msg;
}
int getRow(char c,char mat[5][5])
{
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            if(c == mat[i][j])
            {
                //position p = {i, j};
                return i;
            }
}
int getColumn(char c,char mat[5][5])
{
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            if(c == mat[i][j])
            {
                //position p = {i, j};
                return j;
            }
}

string encrypt(string message,char mat[5][5])
{
    string ctext;
    for(int i=0; i<message.length(); i+=2)    // i is incremented by 2 inorder to group by two two characters
    {
        int x1 = getRow(message[i],mat);
        int y1 = getColumn(message[i],mat);
        int x2 = getRow(message[i+1],mat);
		int y2 = getColumn(message[i+1],mat);
        if( x1 == x2 )
        {
            ctext+=mat[x1][(y1+1)%5];
            ctext+=mat[x2][(y2+1)%5];    
        }
        else if( y1 == y2 )
        {
            ctext+=mat[(x1+1)%5][y1];
            ctext+=mat[(x2+1)%5][y2];
        }
        else
        {
            ctext+=mat[x1][y2];
            ctext+=mat[x2][y1];
        }
    }
    return ctext;
}
string Decrypt(string message,char mat[5][5])
{
    string msg;
    for(int i=0; i<message.length(); i+=2)
    {
        int x1 = getRow(message[i],mat);
        int y1 = getColumn(message[i],mat);
        int x2 = getRow(message[i+1],mat);
		int y2 = getColumn(message[i+1],mat);
        if( x1 == x2 )
        {
            msg+=mat[x1][ --y1<0 ? 4: y1 ];
            msg+=mat[x2][ --y2<0 ? 4: y2 ];
        }
        else if( y1 == y2 )
        {
            msg+= mat[ --x1<0 ? 4: x1 ][y1];
            msg+= mat[ --x2<0 ? 4: x2 ][y2];
        }
        else
        {
            msg+=mat[ x1 ][ y2 ];
            msg+= mat[ x2 ][ y1 ];
        }
    }
    return msg;
}
int main()
{
	string plaintext="balloon";
	string key="monarchy";
	char matrix[5][5];
	generatematrix(key,matrix);
	 for(int k=0;k<5;k++)
    {
        for(int j=0;j<5;j++)
        {
            cout << matrix[k][j] << "  ";
        }
        cout << endl;
    }
    cout << "Actual Message \t\t: " << plaintext << endl;
    string fmsg = formatMessage(plaintext);
    cout << "Formatted Message \t: " << fmsg << endl;
    string ciphertext = encrypt(fmsg,matrix);
    cout << "Encrypted Message \t: " << ciphertext << endl;
	string decryptmsg = Decrypt(ciphertext,matrix);
	cout<< "Decrypted Message \t: " << decryptmsg << endl;
}