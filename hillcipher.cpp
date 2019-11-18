#include <bits/stdc++.h>
using namespace std ; 
int mod26(int x)
{
	return x >= 0 ? (x%26) : 26-(abs(x)%26) ;
}
void multiplyMatrices(int a[1000][3] , int a_rows , int a_cols ,  int b[3][3] , int b_rows , int b_cols , int res[1000][3])
{
	for(int i=0 ; i < a_rows ; i++)
	{
		for(int j=0 ; j < b_cols ; j++)
		{
			for(int k=0 ; k < b_rows ; k++)
			{
				res[i][j] += a[i][k]*b[k][j] ;
			}
			res[i][j] = mod26(res[i][j]) ;
		}
	}
}

string encrypt(string pt, int n,int key[3][3])
{
	int Pmat[1000][3] = {0} ; // plaintext
	int Cmat[1000][3] = {0} ; // cipher text
	int ptIter = 0  ;

	while(pt.length()%n != 0)
	{
		pt += "x" ;  // pad extra x
	}
	int row = (pt.length())/n; // number of rows in P

	for(int i=0; i<row ; i++)
	{
		for(int j=0; j<n; j++)
		{
			Pmat[i][j] = pt[ptIter++]-'a' ;
		}
	}

	// multiplyMatrices(mat_a , row_a , col_a , mat_b, row_b, col_b , mat_result)
	multiplyMatrices(Pmat, row , n , key , n , n , Cmat) ;

	string ct = "" ;
	for(int i=0 ; i<row ; i++)
	{
		for(int j=0 ; j<n ;j++)
		{
			ct += (Cmat[i][j] + 'a');
		}
	}
	return ct ;
}
int findDet(int m[3][3] , int n)
{
	int det;
	if(n == 2)
	{
		det = m[0][0] * m[1][1] - m[0][1]*m[1][0] ;
	}
	else if (n == 3)
	{
		det = m[0][0]*(m[1][1]*m[2][2] - m[1][2]*m[2][1])  - m[0][1]*(m[1][0]*m[2][2] - m[2][0]*m[1][2] ) + m[0][2]*(m[1][0]*m[2][1] - m[1][1]*m[2][0]);
	}
	else det = 0 ; // invalid input
	return mod26(det);
}

int findDetInverse(int R , int D = 26) // R is the remainder or determinant
{
	int i = 0 ;
	int p[100] = {0,1};
	int q[100] = {0} ; // quotient

	while(R!=0)
	{
		q[i] = D/R ;
		int oldD = D ;
		D = R ;
		R = oldD%R ;
		if(i>1)
		{
			p[i] = mod26(p[i-2] - p[i-1]*q[i-2]) ;
		}
		i++ ;
	}
	if (i == 1) return p[i]=1;
	else return p[i] = mod26(p[i-2] - p[i-1]*q[i-2]) ;
}
void findInverse(int m[3][3] , int n , int m_inverse[3][3] )
{
	int adj[3][3] = {0};

	int det = findDet(m , n); // findDet(matrix , order_of_matrix)
	int detInverse = findDetInverse(det);

	if(n==2)
	{
		adj[0][0] = m[1][1];
		adj[1][1] = m[0][0];
		adj[0][1] = -m[0][1];
		adj[1][0] = -m[1][0];
	}
	else if(n==3)
	{
		int temp[5][5] = {0} ;
		// fill the 5x5 matrix
		for(int i=0; i<5; i++)
		{
			for(int j=0; j<5; j++)
			{
				temp[i][j] = m[i%3][j%3] ;
			}
		}
		/* except first row and column, multiply elements along rows and place them along columns */
		for(int i=1; i<=3 ; i++)
		{
			for(int j=1; j<=3 ; j++)
			{
				adj[j-1][i-1] = temp[i][j]*temp[i+1][j+1] - temp[i][j+1]*temp[i+1][j];
			}
		}
	}

	for(int i=0; i<n ; i++)
	{
		for(int j=0; j<n ; j++)
		{
			m_inverse[i][j] = mod26(adj[i][j] * detInverse) ;
		}
	}
}
string decrypt(string ct, int n,int key[3][3])
{
	int Pmat[1000][3] = {0} ; // plaintext
	int Cmat[1000][3] = {0} ; // cipher text
	int ctIter = 0 ;

	int row = ct.length()/n; // number of rows in C

	for(int i=0; i<row ; i++)
	{
		for(int j=0; j<n; j++)
		{
			Cmat[i][j] = ct[ctIter++]-'a' ;
		}
	}

	int k_inverse[3][3] = {0};
	/* findInverse(matrix , order_of_matrix , result_matrix) */
	findInverse(key, n , k_inverse);

	/* multiplyMatrices(mat_a , row_a , col_a , mat_b, row_b, col_b , mat_result) */
	multiplyMatrices(Cmat, row , n , k_inverse , n , n , Pmat) ;

	string pt = "" ;
	for(int i = 0 ; i<row ; i++)
	{
		for(int j=0 ; j<n ; j++)
		{
			pt += (Pmat[i][j] + 'a');
		}
	}
	return pt ;
}
int main(void)
{
	string plaintext ;
	int n ,key[3][3];

	cout << "Enter the text to be encrypted    : " ;
	cin >> plaintext;

	cout << "Enter number of rows in keymatrix : ";
	cin >> n ;

	cout<<"Enter key matrix: " <<endl;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cin >> key[i][j];
		}
	}

	cout << "\nOriginal text  : " << plaintext << endl;

	string ct = encrypt(plaintext, n,key) ;
	cout << "Encrypted text : " << ct << endl;

	string dt = decrypt(ct, n,key);
	cout << "Decrypted text : " << dt << endl;
}
