#include <iostream>

using namespace std;

void descomposicion (int n, int * factores, int &num_factores) {
	
	bool sigue = true;
	
   for(int p = 2; p <= n/2 && sigue; p++) {
   	
		if(n % p == 0) {
			factores[num_factores] = p;
			num_factores++;
         descomposicion (n/p, factores, num_factores);
         sigue = false;
	   }
	}
	   
   if(sigue) {
   	factores[num_factores] = n;
   	num_factores++;
   }
}

int main() {
	
	int v[100];
	int n = 0;
	
	descomposicion(360,v,n);
	
	cout << "n: " << n << endl;
	
	for(int i = 0; i < n; i++) 
		cout << v[i] << " ";
		
	cout << endl;
}
		
		
