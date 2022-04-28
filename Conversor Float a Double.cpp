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
	for(int i=0; i<52-exp; i++){
		if(i>22){
			str2+="0";
		}
		else{
			partFloat*=2;
		 	string bit= to_string(int(partFloat));
			str2=str2+bit;
		 	partFloat-=int(partFloat);
		}
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
	for(int i=0; i<11; i++){
		if(i==10){
			str="1"+str;
		}
		else if(i>6){
			str="0"+str;
		}
		else{
			string bit= to_string(num%2);
			str= bit+str;
			num/=2;
		}
	}
	return str;
}

PrintFloatConvertedToDouble(double m){
	string sgn= signBit(m);
	string exp= biasedExponent(abs(m));
	string sgf= significand(abs(m));
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
	float n;
	cout<<"Ingrese un numero float: ";
	cin>>n;
	cout<<".:.Mostrando patron de bits float.:.\n";
	printFloatToRAM(&n, 4);
	cout<<"\n.:.Convirtiendo numero a double.:.\n\n";
	double m= n;
	cout<<".:.Mostrando patron de bits de double con nuestro programa.:.\n";
	PrintFloatConvertedToDouble(m);
	cout<<".:.Mostrando patron de bits de double en la memoria RAM.:.\n";
	printDoubleToRAM(&m, 8);
	return 0;
}
