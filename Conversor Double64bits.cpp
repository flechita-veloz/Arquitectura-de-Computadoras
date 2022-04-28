#include<iostream>
#include<string>
#include<cmath>
#include<bitset>

using namespace std;

string signBit(double n){
	string str="0";
	if(n<0){
		str="1";
	}
	return str;
}

string significand(double n){
	string str1="", str2="";
	int64_t partInt=int64_t(n), exp=0;
	double partDouble=n-int64_t(n);
	while(partInt>1){
		exp++;
		string bit= to_string(partInt%2);
	 	str1=bit+str1;
	 	partInt/=2;
	}
	for(int i=0; i<52-exp; i++){
		partDouble*=2;
	 	string bit= to_string(int64_t(partDouble));
		str2=str2+bit;
	 	partDouble-=int64_t(partDouble);
	}
	return str1+str2;
}

string biasedExponent(double n){
	int64_t exp=0, partInt= int64_t(n);
	while(partInt>1){
		exp++;
		partInt/=2;
	}
	int64_t num= exp+int64_t(pow(2,10))-1;
	string str="";
	for(int i=0; i<11; i++){
		string bit= to_string(num%2);
		str= bit+str;
		num/=2;
	}
	return str;
}

void printFlatingPoint(double n){
	string sgn= signBit(n);
	string exp= biasedExponent(abs(n));
	string sgf= significand(abs(n));
	cout<<sgn+" "+exp+" "+sgf<<endl;
}

void printDoubleToRAM(void *object, size_t size){
    unsigned char *bytes = static_cast<unsigned char *>(object);
    
    size_t tam;
	
	int binary[8][8];
    for(tam = 0; tam < size; tam++){
        for(int n = 0; n < 8; n++){
            binary[int(tam)][7-n] = (bytes[size -1 - tam] >> n) & 1;
        }
    }
    
    for(int i=0; i<8; i++){
    	for(int j=0; j<8; j++){
    		if((i==0&&j==1)||(i==1&&j==4)){
    			cout<<" ";
			}
    		cout<<binary[i][j];
		}
	}
	cout<<"\n";
}

int main(){
	double n;
	cout<<"Ingrese un numero double: ";
	cin>>n;
	cout<<".:.Convertiendo numero a punto flotante.:.\n";
	printDoublePoint(n);
	cout<<".:.Visualizando patron de bits en la memoria RAM.:.\n";
	printDoubleToRAM(&n, 8);
	return 0;
}
