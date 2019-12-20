#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std; 

const int Digit_Per_Num = 1;
//digits to be stored into an int(accept range:(1-2));
class BigInt{
	public:
		int num[1000]; // both int and longlong are valid
		int n;
		int neg;// is it a negative number
		BigInt(){
			this->n = this->neg = this->num[0] = 0;
		}
		BigInt(string);
		BigInt operator -(){
			this->neg ^= 1;
			return *this;
		}
		
};

ostream & operator << (ostream &os, BigInt a);
BigInt operator << (BigInt a, int b);
BigInt operator >> (BigInt a, int b);
bool operator > (BigInt a, BigInt b);
bool operator >= (BigInt a, BigInt b);
bool operator < (BigInt a, BigInt b);
bool operator <= (BigInt a, BigInt b);
bool operator == (BigInt a, BigInt b);
bool operator != (BigInt a, BigInt b);
BigInt operator + (BigInt a, BigInt b);
BigInt operator - (BigInt a, BigInt b);
BigInt operator * (BigInt a, BigInt b);
BigInt operator / (BigInt a, BigInt b);
BigInt operator % (BigInt a, BigInt b);
bool absolute_cmp(BigInt a, BigInt b);
BigInt pushup(BigInt &a);
BigInt pushdown(BigInt &a);


BigInt::BigInt(string s){
	if(s.substr(0,1).c_str()[0] == '-'){
		s = s.substr(1);
		neg = 1;
	}else neg = 0;
	
	while(s.substr(0,1).c_str()[0] == '0')
		s = s.substr(1);
	// to cut off leading zero
		
	this->n = 0;
	while(1){
		if(s.size() >= Digit_Per_Num+1){
			this->num[this->n++] = atoi(s.substr(s.size() - Digit_Per_Num).c_str());
			s = s.substr(0, s.size() - Digit_Per_Num);
		}else{
			this->num[this->n] = atoi(s.c_str());
			break;
		}
	}
	
	pushup(*this);
}

ostream & operator << (ostream &os, BigInt a){
	if(a.neg)
		os << "-";
	// os << a.neg? "-":" ";
	// negative operator
	
	os << a.num[a.n];
	// the first one digit has no leading zero
	
	for(int i = a.n-1; i+1; i--)
		os << setfill('0') << setw(Digit_Per_Num) << a.num[i];
		// add leading zero(s)
	os << ""; // I don't know why this must be put here;
}

BigInt operator + (BigInt a, BigInt b){
	BigInt BI("0");
	
	// if one is below 0 and the other is above 0, then sub them
	if(a.neg != b.neg){
		b = -b;
		return a - b;
	}
	
	BI.neg = a.neg;
	const int mod = pow(10, Digit_Per_Num);
	int i = 0, flag = 0, ci = 0;
	while(a.n >= i || b.n >= i || flag){
		flag = false;
		if(a.n < i) a.num[i] = 0;
		if(b.n < i) b.num[i] = 0;
		
		BI.num[i] = a.num[i] + b.num[i] + ci;
		ci = BI.num[i] / mod;

		if(ci)//carry
			flag = true;
		BI.num[i] %= mod;
		BI.n = i++;
	}
	pushup(BI);
	return BI;
}

BigInt operator - (BigInt a, BigInt b){
	BigInt BI;
	if(a.neg == b.neg){
		if(absolute_cmp(a, b))
			return -(b-a);
	}else{
		b = -b;
		return a + b;
	}
		
		
	BI.neg = a.neg;
	const int mod = pow(10, Digit_Per_Num);
	int i = 0, ci = 0;
	while(a.n >= i || b.n >= i){
		if(a.n < i) a.num[i] = 0;
		if(b.n < i) b.num[i] = 0;
		
		BI.num[i] = a.num[i] - b.num[i] + ci;
		
		if(BI.num[i] < 0){
			BI.num[i] += mod;
			ci = -1;
		}else ci = 0;
		
		BI.n = i++;
	}
	
	// to cut off leading zero(s)
	pushdown(BI);
	pushup(BI);
	return BI;
}

BigInt operator * (BigInt a, BigInt b){
	BigInt BI("0");
	
	
	if(absolute_cmp(b, a))
		return b * a;
	
	for(int i = 0; i <= a.n; i++){
		BigInt t = b;
		t.neg = 0;
		int p = a.num[i];
		for(int j = 0; j <= b.n; j++)
			t.num[j] *= p;
		pushup(t);

		t = t << i;
		BI = BI + t;
	}
	
	BI.neg = a.neg != b.neg;
	pushup(BI);
	
	return BI;
}

BigInt operator / (BigInt a, BigInt b){
	BigInt q;
	const BigInt ZERO;
	if(b == ZERO)
		throw "Division by zero condition!";
		
	// if a < b
	if(absolute_cmp(a, b))
		return ZERO;
	
	q.neg = a.neg != b.neg;
	a.neg = b.neg = 0;
	
	int flag = 1; 
	BigInt t = b << (a.n - b.n);
	
	while(1){
		while(a >= t){
			if(flag){
				q.n = t.n - b.n;
				flag = 0;
				for(int i = 0; i <= q.n; i++)
					q.num[i] = 0;
			}
			q.num[t.n - b.n]++;
			a = a - t;
		}
		
		if((a.n == b.n && a.num[a.n] < b.num[b.n]) || a.n < b.n)
			break;
			
		t = t >> 1;
	}
	
	
	return q;
}

BigInt operator % (BigInt a, BigInt b){
	return a - (a/b)*b;
}

bool operator < (BigInt a, BigInt b){
	if(a.neg != b.neg)
		return a.neg == true;
	
	if(a.neg == false){
		return absolute_cmp(a, b);
	}else
		return !absolute_cmp(a, b);
}

bool operator > (BigInt a, BigInt b){
	return !(a<b) && a!=b;
}

bool operator == (BigInt a, BigInt b){
	return a.neg==b.neg && !absolute_cmp(a,b) && !absolute_cmp(b,a);
}

bool operator != (BigInt a, BigInt b){
	return !(a==b);
}

bool operator <= (BigInt a, BigInt b){
	return !(a>b);
}

bool operator >= (BigInt a, BigInt b){
	return !(a<b);
}

BigInt operator << (BigInt a, int b){
	if(b == 0)
		return a;
		
	BigInt BI;
	BI.neg = a.neg;
	for(int i = 0; i <= a.n; i++)
		BI.num[i+b] = a.num[i];
	for(int i = 0; i <= b-1; i++)
		BI.num[i] = 0;
		
	BI.n = a.n + b;
	return BI;		
}

BigInt operator >> (BigInt a, int b){
	if(b == 0)
		return a;
	BigInt BI("0");
	
	//result is 0
	if(b >= a.n + 1)
		return BI;
	
	BI.neg = a.neg;
	for(int i = b; i <= a.n; i++)
		BI.num[i-b] = a.num[i];
	
	BI.n = a.n - b;
	return BI;
}

// to judge if |a| < |b|
bool absolute_cmp(BigInt a, BigInt b){
	if(a.n != b.n)
		return a.n < b.n;
	for(int i = a.n; i+1; i--)
		if(a.num[i] != b.num[i])
			return a.num[i] < b.num[i];
	return false;
}

BigInt pushup(BigInt &a){
	if(a.n == 0 && a.num[0] == 0){
		a.neg = 0;
		return a;
	}
	
	int mod = pow(10, Digit_Per_Num);
	int ci = 0;
	for(int i = 0; i <= a.n; i++){
		a.num[i] += ci;
		ci = a.num[i] / mod;
		a.num[i] %= mod; 		
	}
	
	if(ci)
		a.num[++a.n] = ci;
		
	// to cut off leading zero(s)
	pushdown(a);
}

BigInt pushdown(BigInt &a){
	int i = a.n;
	while(i){
		if(a.num[i--] == 0)
			a.n--;
		else break;
	}
	
	return a;
}

BigInt pow(BigInt x, BigInt y, BigInt mod){
	BigInt base = x % mod;
	BigInt r("1");
	const BigInt ZERO("0");
	const BigInt TWO("2");
	
	while(y != ZERO){
		if(y.num[0] & 1) r = (r * base) % mod;
		base = (base * base) % mod;
		y = y / TWO;
	}
	
	return r;
}

int main(){
	string s;
	cout << "please input x, y, m which stands for x^y mod m:" << endl;
	cin >> s;
	BigInt x(s);
	
	cin >> s;
	BigInt y(s);
	
	cin >> s;
	BigInt m(s);
	
	
	cout << endl << "answer:" << pow(x, y, m); 
}
