#include<iostream>
#include<string>
#include<cmath>
#include<bitset>

using namespace std;

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
	cout<<".:.Mostrando patron de bits de float de la RAM.:.\n";
	printFloatToRAM(&n, 4);
	cout<<".:.Convertiendo numero a double.:.\n";
	double m= n;
	cout<<".:.Mostrando patron de bits de double de la RAM.:.\n";
	printDoubleToRAM(&m, 8);
	return 0;
}

