#include <bits/stdc++.h>
using  namespace  std;
#define intt long long int

/*Author: Chinmay Agarwal
 IIT Kanpur
 Implementation of RSA encryption algorithm */

vector<intt> encryptedCodes;
intt n,e,d;

bool isPrime(intt num)
{
	if(num==0 || num==1) return false;
    for(int i=2;i<num;i++)
	{
		if(num%i==0) return  false; 
	}
	return true; 
}

intt modExp(intt base, intt exp, intt mod)
{
	if(exp==0) return 1;
    intt aa=modExp(base,exp/2,mod);
    
    if(exp%2)return ((aa*aa)%mod*base)%mod;
    else return (aa*aa)%mod;
}

intt getD(intt e,intt phi)
{
	for (int res=1; res<phi; res++)
       if ((e*res) % phi == 1)
          return res;	

    return 0;
}

void generateKey()
{
    intt p=0,q=0,f=0;

    // two primes p and q are generated..
	while (!isPrime(p))
	p = (rand())+4096;
	
	while(!isPrime(q))
	q = (rand()%65534)+2;
	
	
	n  = p*q; 
	f = (p-1)*(q-1);
	
	while (__gcd(e , f) != 1)
	e = (rand()%61440) +4096;

    e%=f;

	d = getD(e,f); // basically modulo inverse ie. --> a d such that (e*d)%f==1 
    // also condition of ModInverse is also satisfied ... -> e and f are coprime..
}

void encrypt(string toEncrypt, intt n, intt e)
{
    // every 3 characters in toEncrypt string is encrypted to a new intt code..
    // stored in encryptedCodes vector

    intt inputlength = 0;
    int cnt = 0;
    intt m=0,M=0;
    cout<<"The Encrypted codes ::"<<'\n';
    for(auto c: toEncrypt){
        
        if (cnt % 3 == 0)
        {
            m=c;
            cnt++;
        }
        else if (cnt % 3 == 1)
        {
            m += (1<<8)*c; 
            cnt++;
        }
        else
        {
            m += (1<<16)*c;
            cnt++;
        }
        
        
        if (cnt % 3 == 0)
        {
            if (cnt!= 0)
            {
                M = modExp(m,e,n);
                encryptedCodes.push_back(M);
                cout<<M<<'\n';
            }
        } 
    }

    if (cnt%3)
    {
        M = modExp(m,e,n);
        encryptedCodes.push_back(M);
        cout<<M<<'\n';
    }
    
}

string decrypt(intt n, intt d)
{
    intt m=0,M=0;
    string decryptedString;
    for(auto code:encryptedCodes)
    {
        
        M = code ;
        m = modExp(M,d,n);
        //cout << m << '\n';
        char t1 = 0,t2=0,t3=0;
        if (m > (1<<8))
        t2 = m / (1<<8);
        if (m > (1<<16))
        t3 = m / (1<<16);
        t1 = (m-t1*(1<<16)-t2*(1<<8));
        decryptedString+=t1;
        decryptedString+=t2;
        decryptedString+=t3;
    }
    return decryptedString;
}

int  main() 
{
    
    string inputString;
    getline(cin,inputString);
   
    generateKey();
    cout<<"Public Key {n,e} :: "<<n<<" "<<e<<'\n';
    cout<<"Private Key {d} :: "<<d<<'\n';

    encrypt(inputString,n,e);
    string decryptedString = decrypt(n,d);
    
    

    cout<<"The decrypted message is :: ";
    cout<<decryptedString<<'\n';
    
    
return 0;
}
