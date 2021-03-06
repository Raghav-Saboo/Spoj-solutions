#include <iostream>
#include <bits/stdc++.h>
using namespace std;
struct Bigint {
    string a;
    int sign;
 
    Bigint() {}
    Bigint( string b ) { (*this) = b; }
    int size() { return a.size(); }
    Bigint inverseSign() { sign *= -1; return (*this); }
    Bigint normalize( int newSign ) {
        sign = newSign;
        for( int i = a.size() - 1; i > 0 && a[i] == '0'; i-- ) a.erase(a.begin() + i);
        if( a.size() == 1 && a[0] == '0' ) sign = 1;
        return (*this);
    }
    void operator = ( string b ) {
        a = b[0] == '-' ? b.substr(1) : b;
        reverse( a.begin(), a.end() );
        this->normalize( b[0] == '-' ? -1 : 1 );
    }
    bool operator < ( const Bigint &b ) const {
        if( a.size() != b.a.size() ) return a.size() < b.a.size();
        for( int i = a.size() - 1; i >= 0; i-- ) if( a[i] != b.a[i] ) return a[i] < b.a[i];
        return false;
    }
    Bigint operator + ( Bigint b ) {
        if( sign != b.sign ) return (*this) - b.inverseSign();
        Bigint c;
        for( int i = 0, carry = 0; i < (int)a.size() || i < (int)b.size() || carry; i++ ) {
            carry += (i < (int)a.size() ? a[i] - 48 : 0) + (i < (int)b.a.size() ? b.a[i] - 48 : 0);
            c.a += (carry % 10 + 48);
            carry /= 10;
        }
        return c.normalize(sign);
    }
    Bigint operator - ( Bigint b ) {
        if( sign != b.sign ) return (*this) + b.inverseSign();
        if( (*this) < b ) return (b - (*this)).inverseSign();
        Bigint c;
        for( int i = 0, borrow = 0; i < (int)a.size(); i++ ) {
            borrow = a[i] - borrow - (i < b.size() ? b.a[i] : 48);
            c.a += borrow >= 0 ? borrow + 48 : borrow + 58;
            borrow = borrow >= 0 ? 0 : 1;
        }
        return c.normalize(sign);
    }
    Bigint operator * ( Bigint b ) {
        Bigint c("0");
        for( int i = 0, k = a[i]; i < (int)a.size(); i++, k = a[i] ) {
            while(k-- - 48) c = c + b;
            b.a.insert(b.a.begin(), '0');
        }
        return c.normalize(sign * b.sign);
    }
    Bigint operator / ( Bigint b ) {
        if( b.size() == 1 && b.a[0] == '0' ) b.a[0] /= ( b.a[0] - 48 ) ;
        Bigint c("0"), d;
        for( int j = 0; j < (int)a.size(); j++ ) d.a += "0";
        int dSign = sign * b.sign; b.sign = 1;
        for( int i = a.size() - 1; i >= 0; i-- ) {
            c.a.insert( c.a.begin(), '0');
            c = c + a.substr( i, 1 );
            while( !( c < b ) ) c = c - b, d.a[i]++;
        }
        return d.normalize(dSign);
    }
    Bigint operator % ( Bigint b ) {
        if( b.size() == 1 && b.a[0] == '0' ) b.a[0] /= ( b.a[0] - 48 ) ;
        Bigint c("0");
        int cSign = sign * b.sign; b.sign = 1;
        for( int i = a.size() - 1; i >= 0; i-- ) {
            c.a.insert( c.a.begin(), '0');
            c = c + a.substr( i, 1 );
            while( !( c < b ) ) c = c - b;
        }
        return c.normalize(cSign);
    }
    void print() {
        if( sign == -1 ) putchar('-');
        for( int i = a.size() - 1; i >= 0; i-- ) printf("%c",a[i]);
    }
};
Bigint dp[10][10005];
void rec(long long int n)
{
	long long int a[4]={1,3,5,7};
	long long int i,j,x;
	for(i=0;i<10;i++)
	{
	    for(j=0;j<=n;j++)
	    {
	        dp[i][j]="";
	    }
	}
	dp[1][1]="1";
	dp[3][1]="1";
	dp[5][1]="1";
	dp[7][1]="1";
	for(i=2;i<=n;i++)
	{
		for(x=0;x<4;x++)
		{
			if(a[x]==1)
			{
				dp[1][i]=dp[1][i]+dp[3][i-1];
			}
			else if(a[x]==3)
			{
				dp[3][i]=dp[3][i]+dp[1][i-1]+dp[7][i-1];
			}
			else if(a[x]==5)
			{
				dp[5][i]=dp[5][i]+dp[3][i-1]+dp[7][i-1];
			}
			else
			{
				dp[7][i]=dp[7][i]+dp[5][i-1];
			}
		}
	}
}
int main() {
	// your code goes here
	rec(10000);
	long long int i,t,n,x;
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld",&n);
		long long int a[4]={1,3,5,7};
    	Bigint ans;
    	ans = "0";
    	for(i=0;i<4;i++)
    	{
    		ans=ans+dp[a[i]][n];
    	}
    	ans.print();
    	printf("\n");
	}
	return 0;
} 
