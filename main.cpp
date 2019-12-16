#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std; 

const int Digit_Per_Num = 4;
//digits to be stored into an int(accept range:(1-4));
class BigInt{
	public:
		int num[1000]; // both int and longlong are valid
		int n;
		int neg;// is it a negative number
		BigInt(string);
		BigInt operator -(){
			this->neg ^= 1;
			return *this;
		}
		
};

BigInt operator + (BigInt &a, BigInt &b);
BigInt operator - (BigInt &a, BigInt &b);
BigInt operator * (BigInt &a, BigInt &b);
BigInt operator / (BigInt &a, BigInt &b);
bool operator > (BigInt &a, BigInt &b);
bool operator >= (BigInt &a, BigInt &b);
bool operator < (BigInt &a, BigInt &b);
bool operator <= (BigInt &a, BigInt &b);
bool operator == (BigInt &a, BigInt &b);
bool operator != (BigInt &a, BigInt &b);
BigInt operator << (BigInt &a, int b);
bool absolute_cmp(BigInt &a, BigInt &b);

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
}

ostream & operator << (ostream &os, BigInt a){
	if(a.neg)
		os << "-";
	else os << " "; 
	// os << a.neg? "-":" ";
	// negative operator
	
	os << a.num[a.n];
	// the first one digit has no leading zero
	
	for(int i = a.n-1; i+1; i--)
		os << setfill('0') << setw(Digit_Per_Num) << a.num[i];
		// add leading zero(s)
	os << ""; // I don't know why this must be put here;
}

BigInt operator + (BigInt &a, BigInt &b){
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
		BI.num[i] = a.num[i] + b.num[i] + ci;
		ci = BI.num[i] / mod;

		if(ci)//carry
			flag = true;
		BI.num[i] %= mod;
		BI.n = i++;
	}
	return BI;
}

BigInt operator - (BigInt &a, BigInt &b){
	BigInt BI("0");
	if(a.neg == b.neg){
		if(a.neg == 0){
			if(absolute_cmp(a, b))
				return -(b-a);
		}else{
			if(absolute_cmp(a, b))
				return (b-a);
		}
	}else{
		b = -b;
		return a + b;
	}
		
	const int mod = pow(10, Digit_Per_Num);
	int i = 0, ci = 0;
	while(a.n >= i || b.n >= i){
		BI.num[i] = a.num[i] - b.num[i] + ci;
		
		if(BI.num[i] < 0){
			BI.num[i] += mod;
			ci = -1;
		}
		
		BI.n = i++;
	}
	
	// to cut of leading zero(s)
	i = BI.n;
	while(i){
		if(BI.num[i--] == 0)
			BI.n--;
		else break;
	}
	
	return BI;
}

BigInt operator * (BigInt &a, BigInt &b){
	BigInt BI("0");
	if(a.neg != b.neg)
		BI.neg = 1;
	
	if(absolute_cmp(b, a))
		return b * a;
	
	
	for(int i = 0; i <= a.n; i++){
		BigInt t("0");
		t.num[0] = a.num[i];
		
		
		
		
		t = t << i;
		BI = BI + t;
	}
	
	return BI;
}

bool operator < (BigInt &a, BigInt &b){
	if(a.neg != b.neg)
		return b.neg == true;
	
	if(a.neg == false){
		return absolute_cmp(a, b);
	}else
		return !absolute_cmp(a, b);
}

bool operator > (BigInt &a, BigInt &b){
	return !(a<b) && a!=b;
}

bool operator == (BigInt &a, BigInt &b){
	return a.neg==b.neg && !absolute_cmp(a,b) && !absolute_cmp(b,a);
}

bool operator != (BigInt &a, BigInt &b){
	return !(a==b);
}

bool operator <= (BigInt &a, BigInt &b){
	return !(a>b);
}

bool operator >= (BigInt &a, BigInt &b){
	return !(a<b);
}

BigInt operator << (BigInt &a, int b){
	if(b == 0)
		return a;
		
	BigInt BI("0");
	BI.neg = a.neg;
	for(int i = 0; i <= a.n; i++)
		BI.num[i+b] = a.num[i];
	for(int i = 0; i <= b-1; i++)
		BI.num[i] = 0;
		
	BI.n = a.n + b;
	return BI;		
}


// to judge if |a| < |b|
bool absolute_cmp(BigInt &a, BigInt &b){
	if(a.n != b.n)
		return a.n < b.n;
	for(int i = a.n; i+1; i--)
		if(a.num[i] != b.num[i])
			return a.num[i] < b.num[i];
	return false;
}

int main(){
	string s;
	
	cout << "please input a:";
	cin >> s;
	BigInt a(s);
	cout << "please input b:";
	cin >> s;
	BigInt b(s);
	cout << "you just input:" << endl;
	cout << "a =     " << a << endl;
	cout << "b =     " << b << endl;

	cout << "a + b = " << a + b << endl;
	cout << "a - b = " << a - b << endl;
	//cout << "a * b = " << a * b << endl;
	//cout << "a / b = " << a / b << endl;
} 