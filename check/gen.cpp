#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<string>
using namespace std;

int main(){
	srand(time(NULL));
	
	int n=1000;
	while(n--){
		string in = ".in";
		char t[100];
		itoa(n,t,10);
		
		in = t + in;
		freopen(in.c_str(),"w",stdout);
		int a = rand()-16000;
		int b = rand()-16000;
		printf("%d %d", a , b);
		
		
		string out(".out");
		itoa(n,t,10);
		out = t + out;
		freopen(out.c_str(),"w",stdout);
		printf("%d", a+b);
	}
	
	
} 
