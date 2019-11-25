#include <iostream>
#include<bits/stdc++.h> 
#include <algorithm>
using namespace std;
#define ll long long 

class biginteger{

public:

string multip(string n1, string n2){
	string str1, str2;
	ll len1=n1.length();
	ll len2=n2.length();
	if(len1>=len2){
		str1=n1;
		str2=n2;
	}
	else{
		str1=n2;
		str2=n1;
		ll temp=len1;
		len1=len2;
		len2=temp;
	}
	string prod1="";

	reverse(str1.begin(), str1.end());
	reverse(str2.begin(), str2.end());

	int carry=0;

	//Doing multiplication with str2's 1st num,
	// so that we have something other than null
	//... for later usage
	for(int i=0;i<len1;i++){
		int dig=str1[i]-'0';
		ll x=((dig*(str2[0]-'0'))+carry);
		prod1+=(x%10+'0');
		carry=x/10;

	}

	if(carry>0){
		prod1+=(carry+'0');
	}

	// cout<<"prod1 "<<prod1<<endl;

	if(len2==1){//if there is just that one digit to multiply with
		reverse(prod1.begin(),prod1.end());
		return prod1;
	}

	string prod;

	//i is for the smaller no. It starts from 1 as for 0th digit multiplication already done and stored in prod1
	for(ll i=1;i<len2;i++){
		int dig1=str2[i]-'0';

		carry=0;
		prod="";

		int m=0;
		while(m<i){
			prod+=(prod1[m]);
			m++;
		}

		for(ll j=0;j<len1;j++){
			int dig2=str1[j]-'0';
			// cout<<"digs "<<dig1<<" "<<dig2<<endl;

			ll x=(dig1*dig2)+carry;
			// cout<<"x "<<x;

			ll res;

			/*
			12354		45321
		   	  *45		*54
		   --------		------
			61770		07716
		  +49416		+61494 For the 4 in rhs(i.e when i+j>prod1's pos), there's no no. above to add to it
		  ---------		-------
		   555930		039555
		  ---------		-------

		  */
			if(i+j>=prod1.length()){
				res=x;
			}
			else {
				res=x+(prod1[i+j]-'0');
				// cout<<" res "<<res<<endl;

			}


			prod+=(res%10 +'0');

			carry=res/10;
		}

		if(carry>0){
			prod+=(carry+'0');
		}
		// cout<<i<<" "<<"prod "<<prod<<endl;

		prod1=prod;		
	}

	// cout<<"b4 rev prod "<<prod<<endl;
	reverse(prod.begin(),prod.end());
	// cout<<"after rev prod "<<prod<<endl;
	return prod;    

}

string addone(string str){
	reverse(str.begin(), str.end());

	// cout<<str<< endl;

	ll len=str.length();
	// cout<<"len "<<len<<endl;
	ll carry=0;
	for(int i=0;i<len;i++){

		// cout<< "str[i] "<<str[i]<<endl;
		// cout<< "- 0 "<< str[i]-'0'<<endl;

		if((str[i]-'0')<=8){

			// cout<<"vbn "<< (str[i]-'0')<<endl;
			ll x;
			if(i==0){
				x=(str[i]-'0')+1+carry;
			}
			else{
				x=(str[i]-'0')+carry;
			}
			

			// cout<<"x "<<x<<endl;
			str[i]=x+'0';

			// cout<<"a char "<<str[i]<<endl;

			carry=0;
			break;
		}
		else{
			carry=1;
			str[i]='0';
		}
	}
	if(carry>0){
		str+="1";
	}
	reverse(str.begin(), str.end());
	return str;
}

string factorial(string str){
	ll num;
	string res="1";
	string x="1";
	string::size_type sz=0;
	num = stoll(str, &sz, 10);
	for(ll i=1;i<num;i++){
		x=addone(x);

		// cout<<"res b4 "<<res<<" x "<<x<<endl; 
		res=multip(x, res);

		// cout<<"res after "<<res<<" x "<<x<<endl;
	}
	return res;
}

int compare_greater(string str1, string str2){
	// ret 0 if str1<=str2
	// ret 1 if str1>str2
	int len1, len2;
	len1=str1.length();
	len2=str2.length();
	if(len1<len2){
		return 0;
	}
	else if(len1>len2){
		return 1;
	}
	else{//str length same
		ll i;
		for(i=0;i<len1;i++){
			if(str1[i]>str2[i]){
				return 1;
			}
			else if(str1[i]<str2[i]){
				return 0;
			}
			else{
				continue;
			}
		}
		return 0;
	}
}

string subtract(string str1, string str2){

	//str1>str2
	ll len1, len2, borrow=0, result, dig1, dig2;
	string sub="";
	if(!compare_greater(str1, str2)){
		swap(str1, str2);
	}
	len1=str1.length();
	len2=str2.length();
	reverse(str1.begin(), str1.end());
	reverse(str2.begin(), str2.end());

	for(ll i=0;i<len2;i++){
		dig1=str1[i]-'0';
		dig2=str2[i]-'0';
		result=dig1-dig2-borrow;

		if(result<0){
			result+=10;
			borrow=1;
		} 
		else{
			borrow=0;
		}
		sub+=(result+'0');

	}

	//for remaining digits
	result=0;
	for(ll j=len2;j<len1;j++){
		result=(str1[j]-'0')-borrow;

		if(result<0){
			result+=10;
			borrow=1;
		}
		else{
			borrow=0;
		}
		sub+=(result+'0');
	}

	reverse(sub.begin(),sub.end());
	//remove leading zeroes from sub adn then return 
	ll x=0;
	string sub1;
	while(x<sub.length()){
		if(sub[x]=='0'){
			x++;
		}
		else{
			sub1=sub.substr(x, sub.length());
			break;
		}
	}

	return sub1;

}

int compare_equal(string str1, string str2){
	ll len1, len2;
	len1=str1.length();
	len2=str2.length();

	if(len1!=len2){
		return 0;
	}

	else{
		for(ll i=0;i<len1;i++){
			if(str1[i]!=str2[i]){
				return 0;
			}
		}
		return 1;
	}
}

string gcd(string str1, string str2){
	if(compare_equal(str1, "0")){
		return str2;
	}
	if(compare_equal(str2, "0")){
		return str1;
	}
	if(!compare_greater(str1, str2)){
		swap(str1, str2);
	}
	while(!compare_equal(str1,str2)){
		if(!compare_greater(str1, str2)){
		swap(str1, str2);
		}
		// cout<<"1:str1 "<<str1<<" str2 "<<str2<<endl;
		str1=subtract(str1, str2);
		cout<<"2: str1 "<<str1<<" str2 "<<str2<<endl;
	}

	return str2;

}
string divide(string str, ll n){
	// ll n=2;
	ll i=0;
	ll x=str[i]-'0';
	string div="";
	if(x<n){
		while(x<n){
			x=x*10+(str[++i]-'0');
			// cout<<"pehla x "<<x<<endl;
		}
	}
	for(;i<str.length();){

		div+=(x/n)+'0';
		// cout<<"div "<<div<<endl;

		
		x=(x%n)*10+(str[++i]-'0');
		// cout<<"x "<<x<<endl;
	
		
	}
	return div;

}

string divideby2(string str){
	ll n=2;
	ll i=0;
	ll x=str[i]-'0';
	string div="";
	if(x<n){
		while(x<n){
			x=x*10+(str[++i]-'0');
			// cout<<"pehla x "<<x<<endl;
		}
	}
	for(;i<str.length();){

		div+=(x/n)+'0';
		// cout<<"div "<<div<<endl;

		
		x=(x%n)*10+(str[++i]-'0');
		// cout<<"x "<<x<<endl;
	
		
	}
	return div;

}	

string fastexpo(string str, string pow){
	string ans;
	if(pow=="0"){
		return "1";
	}

	if(pow=="1"){
		return str;
	}

	if(str=="0"){
		return "0";
	}

	string inter=fastexpo(str,divideby2(pow));
	ans=multip(inter,inter);


	if((pow[pow.length()-1]-'0')%2==0){//even power
		return ans;
	}

	else{
		ans=multip(str,ans);
		return ans;
	}

}
	



};

int main(){

	ll t, k;
	cin>>t;
	biginteger bigi;
	while(t--){
		cin>>k;
		string str1, str2, sign="";

		//---------1:fast expo---------
		if(k==1){
			cin>>str1;
			cin>>str2;

			if(str1[0]=='-'){
				if((str2[str2.length()-1]-'0')%2!=0){//odd power
					sign="-";
				}
				else{
					sign="";
				}		
				str1=str1.substr(1);
			}
			cout<<(sign+bigi.fastexpo(str1,str2))<<endl;

		}

		//---------2:gcd---------
		else if(k==2){
			cin>>str1;
			cin>>str2;
			// cout<<"here"<<endl;
			if(str1[0]=='-'){
				str1 = str1.substr(1);
			} 
			if(str2[0]=='-'){
				str2 = str2.substr(1); 
			}
        	cout<<bigi.gcd(str1,str2)<<endl;
		}

		//---------3:factorial---------
		else if(k==3){
			cin>>str1;
			if(str1[0]=='-'){
				cout<<"Invalid no.; no factorial of negative nos"<<endl;
				return 0;
				// str1 = str1.substr(1);
			}
			cout<<bigi.factorial(str1)<<endl;
		}


	}
	return 0;  

}