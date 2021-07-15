/* 
	Aluno: Cassio Pereira de Lima
	Matricula: 20180035995
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "matrix.h"

	/* Função para criação de matrizes */

struct matrix create_matrix(int *data, int n_rows, int n_cols){
	
	struct matrix dados;

	dados.data = data;
	dados.n_rows = n_rows;
	dados.n_cols = n_cols;
	dados.stride_rows = n_cols;
	dados.stride_cols = 1;
	dados.offset = 0;

	return dados;
}


struct matrix zeros_matrix(int n_rows, int n_cols) {
	int dimension = n_rows*n_cols, i = 0;
	int *z = malloc(dimension * sizeof(int));

	while(i < dimension){
		z[i] = 0;
		i++;
	}

	struct matrix a_matrix = create_matrix(z, n_rows, n_cols);
	return a_matrix;
}	


struct matrix random_matrix(int n_rows, int n_cols, int b, int e) {
	int dimension = n_rows * n_cols, q = 0;
	int *r = malloc(dimension * sizeof(int));

	srand(time(NULL));
	q = e - b + 1;

	for (int i = 0; i<dimension; i++) {
		r[i] = (rand() % q) + b;
	}

	struct matrix a_matrix = create_matrix(r, n_rows, n_cols);
	return a_matrix;
}


struct matrix i_matrix(int n) {
	int dimension = n * n;
	struct matrix a_matrix = zeros_matrix(n, n);

	for (int j=a_matrix.offset; j<dimension; j = j + ( n + 1 )) {
		a_matrix.data[j] = 1;
	}

	return a_matrix;
}

	/*	Acessando Elementos */

int get_element(struct matrix a_matrix, int ri, int ci) {
	int val = (ci * a_matrix.stride_cols) + (ri * a_matrix.stride_rows);

	return a_matrix.data[val];
}


void put_element(struct matrix a_matrix, int ri, int ci, int elem){
	int val = (ci * a_matrix.stride_cols) + (ri * a_matrix.stride_rows);

	a_matrix.data[val] = elem;
}

 
void print_matrix(struct matrix a_matrix){

	int i, j;

	for (i = 0; i < a_matrix.n_rows; i++){
		for (j = 0; j < a_matrix.n_cols; j++){
			
			printf(" %d ", a_matrix.data[(i*a_matrix.stride_rows + j*a_matrix.stride_cols) + a_matrix.offset]);
			
		}
		putchar('\n');
	}

}

	/* Manipulando dimensões*/

struct matrix transpose(struct matrix a_matrix){
	int transpose_n_cols, transpose_n_rows, transpose_stride_rows, transpose_stride_cols;

	transpose_n_cols = a_matrix.n_cols;
	transpose_n_rows = a_matrix.n_rows;
	transpose_stride_rows = a_matrix.stride_rows;
	transpose_stride_cols = a_matrix.stride_cols;

	a_matrix.n_cols = transpose_n_rows;
	a_matrix.n_rows = transpose_n_cols;
	a_matrix.stride_rows = transpose_stride_cols;
	a_matrix.stride_cols = transpose_stride_rows;

	return a_matrix;
}

struct matrix reshape(struct matrix a_matrix, int new_n_rows, int new_n_cols){

	int i;

	int q = 0; 

	for (i = 0; i< a_matrix.n_rows*a_matrix.n_cols ; i++){
		q++;
	}

	if (q == new_n_rows * new_n_cols) {
		a_matrix.n_rows = new_n_rows;
		a_matrix.n_cols = new_n_cols;
		a_matrix.stride_rows = new_n_cols;
	} else{
		printf("Não foi possível fazer o reshape. Tente com uma quantidade de elem validos.\n");
		exit(1);
	}

	return a_matrix;
}	

struct matrix flatten(struct matrix a_matrix) {
	a_matrix.n_cols = a_matrix.n_cols * a_matrix.n_rows;
	a_matrix.stride_rows = a_matrix.n_cols;  
	a_matrix.n_rows = 1;

	return a_matrix;
}

struct matrix slice(struct matrix a_matrix, int rs, int re, int cs, int ce){
	a_matrix.n_rows = re-rs;  
	a_matrix.n_cols = ce-cs;
	a_matrix.offset = (rs * a_matrix.stride_rows) + (cs * a_matrix.stride_cols);

	return a_matrix;
}

	/*	Função de agregação */

int sum(struct matrix a_matrix) {
	int s = 0, dimension;
	int i;
	dimension = a_matrix.n_cols * a_matrix.n_rows;
	for (i = 0; i < dimension; i++) {
		s = s + a_matrix.data[i];
	}

	return s;
}

float mean(struct matrix a_matrix) {
	float s = 0, dimension;
	int i = 0;
	dimension = a_matrix.n_cols * a_matrix.n_rows;
	
	while(i < dimension){

		s = s + a_matrix.data[i];
		i++;
	}
	return s/i;
}

int min(struct matrix a_matrix){
	int dimension, m = INT_MAX;
	int i = 0;
	dimension = a_matrix.n_cols * a_matrix.n_rows;

	while(i < dimension){
		if (m > a_matrix.data[i]){
			m = a_matrix.data[i];
		}
		i++;
	}
	return m;
}

int max(struct matrix a_matrix) {
	int dimension, max = 0;
	int i = 0;
	dimension = a_matrix.n_cols*a_matrix.n_rows;

	while(i < dimension){
		if (max < a_matrix.data[i]) {
			max = a_matrix.data[i];
		}
		i++;
	}

	return max;
}

	/*	Funções de operações aritimeticas*/

struct matrix add(struct matrix a_matrix, struct matrix b_matrix) {
	int da, db, i = 0;

	da = a_matrix.n_cols*a_matrix.n_rows;
	db = b_matrix.n_cols*b_matrix.n_rows;

	if (da != db) {
		printf("Não foi possível fazer a soma. tente com um valor valido.\n");
		exit(1);
	}

	int *a = malloc(da * sizeof(int));
	for (i=0; i<da; i++){
		a[i] = a_matrix.data[i] + b_matrix.data[i];
	}

	struct matrix ad_matrix = create_matrix(a, a_matrix.n_rows, a_matrix.n_cols);
	return ad_matrix;
}

struct matrix sub(struct matrix a_matrix, struct matrix b_matrix) {
	int da, db;
	int i;
	da = (a_matrix.n_cols*a_matrix.n_rows);
	db = (b_matrix.n_cols*b_matrix.n_rows);
	if (da != db){
		printf("Não foi possível fazer a subtração. tente com um valor valido.\n");
		exit(1);
	}

	int *s = malloc(da * sizeof(int));

	for (i=0; i < da; i++) {
		s[i] = a_matrix.data[i] - b_matrix.data[i];
	}

	struct matrix s_matrix = create_matrix(s, a_matrix.n_rows, a_matrix.n_cols);
	return s_matrix;
}

struct matrix division(struct matrix a_matrix, struct matrix b_matrix) {
	int da, db;
	int i;
	da = a_matrix.n_cols * a_matrix.n_rows;
	db = b_matrix.n_cols * b_matrix.n_rows;
	if (da != db) {
		printf("Não foi possível fazer a divisão. tente com uma quantidade de elementos válida.\n");
		exit(1);
	}

	int *d = malloc(da * sizeof(int));

	for (i = 0; i < da; i++) {
		if (b_matrix.data[i] == 0){
			printf("Impossível realizar a divisão por 0. Insira uma quantidade de elementos válida.\n");
			exit(1);
		}

		d[i] = a_matrix.data[i] / b_matrix.data[i];
	}

	struct matrix d_matrix = create_matrix(d, a_matrix.n_rows, a_matrix.n_cols);
	return d_matrix;
}

struct matrix mul(struct matrix a_matrix, struct matrix b_matrix) {
	int da, db;
	int i;

	da = (a_matrix.n_cols*a_matrix.n_rows);
	db = (b_matrix.n_cols*b_matrix.n_rows);

	if (da != db) {
		printf("Não foi possível fazer a multiplicação. Tente com uma quantidade de elementos válida.\n");
		exit(1);
	}

	int *m = malloc(da * sizeof(int));

	for (i = 0; i < da; i++) {
		m[i] = a_matrix.data[i] * b_matrix.data[i];

	}

	struct matrix m_matrix = create_matrix(m, a_matrix.n_rows, a_matrix.n_cols);
	return m_matrix;
}


struct matrix matmul(struct matrix a_matrix, struct matrix b_matrix){

	int i, j;
	if(a_matrix.n_cols != b_matrix.n_rows){
		printf("Não foi possível realizar a multiplicação. Tente com uma quantidade de elementos válida.\n");
		exit(1);
	}

	int dimension = a_matrix.n_rows*b_matrix.n_cols;
	int *mat = malloc(dimension * sizeof(int));

	for (i = 0; i < dimension; i++){
		mat[i]= 0;
	}
	int p = 0;
	int q = 0;

	for (i = 0; i < dimension; i++){
		int n = 0;
		for (j = 0; j < a_matrix.n_cols; j++) {
			q = j;
			q += a_matrix.stride_rows * (i / b_matrix.stride_rows);
			if(i % b_matrix.stride_rows == 0){
				p = 0;
			}
			mat[i] += a_matrix.data[q] * b_matrix.data[n+p];
			n = n + b_matrix.stride_rows;
		}
		p++;
	}

	struct matrix mat_matrix = create_matrix(mat, a_matrix.n_rows, b_matrix.n_cols);
	return mat_matrix;

}
