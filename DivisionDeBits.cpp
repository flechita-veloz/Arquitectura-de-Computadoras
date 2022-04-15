#include<iostream>
#include<bitset>
#define bit bitset<16> //Aqui se ingresa la cantidad de bits

using namespace std;

void shiftLeft(bit &A, bit &Q){
	A = A<<1;
	A[0] = A[0] + Q[A.size()-1];
	Q = Q<<1;
}

bit sumaBinaria(bit A, bit M){
	bit ans;
	bool carry = false;
	for(int i=0; i<A.size(); i++){
		ans[i] = (A[i]^M[i])^carry;
		carry = (A[i] && M[i]) || (A[i] && carry) || (M[i] && carry);
	}
	return ans;
}

bit cambioSignoComp2(bit M){
	int n = M.size()-1;
	bit unoAcarreado = 1, uno = 1;  
	while(n--){ //unoAcarreado = 11...11 n veces
		unoAcarreado = unoAcarreado << 1;
		unoAcarreado = sumaBinaria(unoAcarreado, uno);
	}
	M ^= unoAcarreado;
	M = sumaBinaria(M, uno);
	return M;
}

bit restaComp2(bit A, bit M){
	A =  sumaBinaria(A, cambioSignoComp2(M));
	return A;
}

void divide(bit D, bit d){
	bit Q = D, M = d, A=0;
	int count = 0;
	cout<<"A= "<<A<<"\tQ= "<<Q<<"\tValores iniciales\n\n";
	while(++count<=D.size()){ 
		cout<<count<<" ciclo:\n";
		shiftLeft(A, Q);
		cout<<"A= "<<A<<"\tQ= "<<Q<<"\tLeft Shift\n";
		cout<<"   "<<cambioSignoComp2(M)<<"\t";
		for(int i=0; i<D.size()+3; i++){
			cout<<" ";
		}
		cout<<"\t";
		cout<<"Sustraccion en compl-2\n   ";
		for(int i=0; i<D.size(); i++){
			cout<<"-";
		}
		cout<<"\n";
		cout<<"A= "<<restaComp2(A,M)<<"\t";
		A= restaComp2(A,M);
		bit cero = 0;
		int posFinal = D.size()-1;
		if(A[posFinal]){
			for(int i=0; i<D.size()+3; i++){
				cout<<" ";
			}	
			cout<<"\t";
			A = sumaBinaria(A,M);
			cout<<A<<" - "<<cambioSignoComp2(M)<<"\n";
			cout<<"A= "<<A<<"\t"<<"Q= "<<Q<<"\tRestaurar, 0--->Q0\n\n";
			
		}
		else{
			bit uno = 1;
			Q= sumaBinaria(Q, uno);
			cout<<"Q= "<<Q<<"\tNo restaura, 1--->Q0\n\n";
		}
	}
	cout<<"El cociente es: "<<Q<<"\n";
	cout<<"El residuo es:  "<<A<<"\n";
}

int main(){
	bit D, d;
	bit uno = 1;
	cout<<"Ingrese el dividendo: ";
	cin>>D;
	cout<<"Ingrese el divisor: ";
	cin>>d;
	cout<<"\n";
	divide(D,d);
	return 0;
}

