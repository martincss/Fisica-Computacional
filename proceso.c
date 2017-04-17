#include <stdio.h>
#include <time.h>

#define N 10
#define p 0.5

int clase(int N, int a[]);

int main()
{
	int a[N*N];
	int i;
	float r;
	
	srand(time(NULL));
	for (i=0; i<N*N; i++){
		r = rand()%100;
		r = r/100; 
		
		if (r<=p){
			a[i] = 1;
				}
		else{
			 a[i] = 0;
			  }
		}
	printf("\n");
	
	for (i=0; i<N*N; i++){
		if ((i)%N == 0){
			printf("\n %3i", a[i]);
		}
		else{
			printf("%3i",a[i]);
			}
		}
	printf("\n");
	printf("\n");					
}

int clase(int N, int a[])
{
	int clase[N*N/2];
	int i, j, s1, s2;
	int clase_nueva = 2;

	for (i=0; i<N*N/2; i++){ // inicializa vector de clases

		clase[i] = 0

	}

	// Recorre la red y etiqueta clusters	

	for (i=0; i<N; i++){

		for (j=0; j<N; j++){

			if (a[i*N+j]==1){ 

				if (i==0 && j==0){ //primer elemento de la red

					a[i+N+j] = clase_nueva;
					clase[clase_nueva] = clase_nueva;
					clase_nueva++;
				}

				else if (i==0){// primera fila, solo vecinos a la izquierda

					if (a[i*N+j-1]==0){
						a[i*N+j] = clase_nueva;
						clase[clase_nueva] = clase_nueva;
						clase_nueva++;
					}

					else if (a[i*N+j-1]!=0){
						s1 = a[i*N+j-1];
						while (clase[s1]<0){
							s1 = -clase[s1];
						}
						// clase[s1] = s1 (ya esta de mas?)
						a[i*N+j] = s1;
					}
				}

				else if (j==0){ //primera columna

					if (a[(i-1)*N+j]==0){
						a[i*N+j] = clase_nueva;
						clase[clase_nueva] = clase_nueva;
						clase_nueva++;
					}

					else if (a[i*N+j-N]!=0){
						s1 = a[i*N+j-N];
						while (clase[s1]<0){
							s1 = -clase[s1];
						}
						// clase[s1] = s1 (ya esta de mas?)
						a[i*N+j] = s1;

				else{
					
					
				}		
				}

		}		

	}
	
	
}



