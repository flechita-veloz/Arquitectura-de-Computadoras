#include<iostream>
#include<string>
#include<cmath>
#include<bitset>

using namespace std;

string signBit(float n){
	string str="0";
	if(n<0){
		str="1";
	}
	return str;
}

string significand(float n){
	string str1="", str2="";
	int partInt=int(n), exp=0;
	float partFloat=n-int(n);
	while(partInt>1){
		exp++;
		string bit= to_string(partInt%2);
	 	str1=bit+str1;
	 	partInt/=2;
	}
	for(int i=0; i<23-exp; i++){
		partFloat*=2;
	 	string bit= to_string(int(partFloat));
		str2=str2+bit;
	 	partFloat-=int(partFloat);
	}
	return str1+str2;
}

string biasedExponent(float n){
	int exp=0, partInt= int(n);
	while(partInt>1){
		exp++;
		partInt/=2;
	}
	int num= exp+int(pow(2,7))-1;
	string str="";
	for(int i=0; i<8; i++){
		string bit= to_string(num%2);
		str= bit+str;
		num/=2;
	}
	return str;
}

void printFlatingPoint(float n){
	string sgn= signBit(n);
	string exp= biasedExponent(abs(n));
	string sgf= significand(abs(n));
	cout<<sgn+" "+exp+" "+sgf<<endl;
}

void printFloatToRAM(void *object, size_t size){
    unsigned char *bytes = static_cast<unsigned char *>(object);
    
    size_t tam;
	
	int binary[4][8];
    for(tam = 0; tam < size; tam++){
        for(int n = 0; n < 8; n++){
            binary[int(tam)][7-n] = (bytes[size -1 - tam] >> n) & 1;
        }
    }
    
    for(int i=0; i<=3; i++){
    	for(int j=0; j<8; j++){
    		if((i==0&&j==1)||(i==1&&j==1)){
    			cout<<" ";
			}
    		cout<<binary[i][j];
		}
	}
	cout<<"\n";
}

int main(){
	float n;
	cout<<"Ingrese un numero flotante: ";
	cin>>n;
	cout<<".:.Convertiendo numero a punto flotante.:.\n";
	printFlatingPoint(n);
	cout<<".:.Visualizando patron de bits en la memoria RAM.:.\n";
	printFloatToRAM(&n, 4);
	return 0;
}

