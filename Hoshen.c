#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define n 10
#define p 0.5

void init_red(int N, int red[]);
void print_red(int N, int red[]);
void clases(int N, int red[]);
// bool percola(int N, int red[]);

int main()
{
	int red[n*n];
	// no hace falta devolver el puntero ya que la funcion no lo cambia
	init_red(n, red);
	print_red(n, red);
	// idem
	clases(n,red);
	print_red(n, red);

	// percola(n, red);

	return 0;
}


void init_red(int N, int red[]){
	int i;
	float r;

	srand(time(NULL));
	for (i=0; i<N*N; i++){
		r = rand()%100;
		r = r/100;

		if (r<=p){
			red[i] = 1;
				}
		else{
			 red[i] = 0;
			  }
		}
  // ojo! este return devuelve el puntero de el puntero de a ( red[] == *a )
	// saque el return
}

void print_red(int N, int red[]){
	int i;

	printf("\n");

	for (i = 0 ; i < N*N ; i++){
		if ((i)%N == 0){
			printf("\n %3i", red[i]);
		}
		else{
			printf("%3i",red[i]);
			}
		}
	printf("\n");
	printf("\n");
}

int clase_de_posicion(int clases[], int posicion) {
	while (clases[posicion]<0){
		posicion = -clases[posicion];
	}

	return posicion;
}

int generar_clase_nueva(int red[], int clases[], int elemento_actual, int clase_nueva) {
	red[elemento_actual] = clase_nueva;
	clases[clase_nueva] = clase_nueva;
	return ++clase_nueva;
}

// hasta aca es lo mismo que el archivo percolacion.c
////////////////////////////////////////////////////////////////////////////////
void clases(int N, int red[])
{
	int clases[N*N/2]; // la maxima cantidad de clasess se da para el caso "tablero de ajedrez"
	int i, j;
	int clase_nueva = 2;
	for (i=0; i<N*N/2; i++){ // inicializa vector de clasess
		clases[i] = 0;
	}

	// Recorre la red y etiqueta clusters
	for (i=0; i<N; i++){ // recorre filas
		for (j=0; j<N; j++){ // recorre columnas
			int elemento_actual = i*N+j;
			int elemento_de_arriba = elemento_actual-N;
			int elemento_de_la_izquierda = elemento_actual-1;

			if (red[elemento_actual]==1){ // si el elemento seleccionado esta ocupado
				if (i==0 && j==0){ //primer elemento de la red
					clase_nueva = generar_clase_nueva(red, clases, elemento_actual, clase_nueva);
				}

				else if (j==0){// primera columna, solo vecinos arriba
					if (red[elemento_de_arriba]==0){
						clase_nueva = generar_clase_nueva(red, clases, elemento_actual, clase_nueva);
					}
					else if (red[elemento_de_arriba]!=0){
						red[elemento_actual] = clase_de_posicion(clases, red[elemento_de_arriba]);;
					}
				}

				else if (i==0){ //primera fila
					if (red[elemento_de_la_izquierda]==0){
						clase_nueva = generar_clase_nueva(red, clases, elemento_actual, clase_nueva);
					}

					else if (red[elemento_de_la_izquierda]!=0){
						red[elemento_actual] = clase_de_posicion(clases, red[elemento_de_la_izquierda]);
					}
				}

				else { //bulk de la red
					if (red[elemento_de_arriba]==0 && red[elemento_de_la_izquierda]==0){ // caso trivial, vecinos nulos
						clase_nueva = generar_clase_nueva(red, clases, elemento_actual, clase_nueva);
					}

					else if (red[elemento_de_arriba]!=0 && red[elemento_de_la_izquierda]==0){ // caso simple, vecino a la izquierda
						red[elemento_actual] = clase_de_posicion(clases, red[elemento_de_arriba]);
					}

					else if (red[elemento_de_arriba]==0 && red[elemento_de_la_izquierda]!=0){ //caso simple, vecino arriba
						red[elemento_actual] = clase_de_posicion(clases, red[elemento_de_la_izquierda]);
					}

					else if (red[elemento_de_arriba]!=0 && red[elemento_de_la_izquierda]!=0 && red[elemento_de_arriba]==red[elemento_de_la_izquierda]){
						red[elemento_actual] = clase_de_posicion(clases, red[elemento_de_arriba]);
					}

					else if (red[elemento_de_arriba]!=0 && red[elemento_de_la_izquierda]!=0 && red[elemento_de_arriba]!=red[elemento_de_la_izquierda]){ //caso complicado, conficto de etiquetas
						int clase_de_arriba = clase_de_posicion(clases, red[elemento_de_arriba]);
						// Aca estaba haciendo mal la cuenta del elemento de la izquierda
						int clase_de_izquierda = clase_de_posicion(clases, red[elemento_de_la_izquierda]);

						if (clase_de_arriba<clase_de_izquierda){
							red[elemento_actual] = clase_de_arriba;
							clases[clase_de_izquierda] = -clase_de_arriba;
						}

						else if (clase_de_izquierda<clase_de_arriba){
							red[elemento_actual] = clase_de_izquierda;
							clases[clase_de_arriba] = -clase_de_izquierda;
						}
					}
				}
			}
		}
	}

	// re-etiquetado corrige etiquetas falsas
	for (i = 0 ; i < N*N ; i++) {
		red[i] = clase_de_posicion(clases, red[i]);
	}
}

// bool percola(int N, int red[]) {
// 	int prinera_fila[N] = red[0];
// 	int ultima_fila[N] = red[N*(N - 1)];
//
// 	return true;
// }
