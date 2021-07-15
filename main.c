/* 
	Aluno: Cassio Pereira de Lima
	Matricula: 20180035995
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "matrix.h"

int main(void){
	int dados[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
	struct matrix matrix_c = create_matrix(dados, 3, 3);
	struct matrix matrix_zero = zeros_matrix(5, 4);
	struct matrix matrix_random = random_matrix(4, 3, 1, 10);
	struct matrix id_matrix = i_matrix(3);
	printf("--------------------------------------\n");
	printf("matrix: \n");
	print_matrix(matrix_c);
	printf("--------------------------------------\n");
	printf("zeros matrix: \n");
	print_matrix(matrix_zero);
	printf("--------------------------------------\n");
	printf("Matrix randomica: \n");
	print_matrix(matrix_random);
	printf("--------------------------------------\n");
	printf("Matrix identidade: \n");
	print_matrix(id_matrix);
	printf("--------------------------------------\n");
	
	printf("Elemento [0:2]: %d\n", get_element(id_matrix, 0, 2));
	printf("Trocando o valor do elemento [0:2] por 5: \n");
	put_element(id_matrix, 0, 2, 5);
	print_matrix(id_matrix);
	printf("--------------------------------------\n");

	printf("Transposta da matrix random: \n");
	print_matrix(transpose(matrix_random));
	printf("--------------------------------------\n");
	printf("reshape zeros matrix: \n");
	print_matrix(reshape(matrix_zero, 10, 2));
	printf("--------------------------------------\n");
	printf("flatten Matrix indentidade: \n");
	print_matrix(flatten(id_matrix));
	printf("--------------------------------------\n");
	printf("slice Matrix\n");
	print_matrix(slice(matrix_c, 0, 2, 1, 3));
	printf("--------------------------------------\n");
	
	printf("Soma matrix identidade: [%d]\n", sum(id_matrix));
	printf("--------------------------------------\n");
	printf("Media matrix: [%f]\n", mean(matrix_c));
	printf("--------------------------------------\n");
	printf("Min matrix random: [%d]\n", min(matrix_random));
	printf("--------------------------------------\n");
	printf("Max matrix random: [%d]\n", max(matrix_random));
	printf("--------------------------------------\n");
	
	printf("Adiçao matrix identidade e matrix: \n");
	print_matrix(add(id_matrix, matrix_c));
	printf("--------------------------------------\n");
	printf("subtração matrix identidade e matrix: \n");
	print_matrix(sub(matrix_c, id_matrix));
	printf("--------------------------------------\n");
	printf("Divisao da matrix identidade e matrix: \n");
	print_matrix(division(id_matrix, matrix_c));
	printf("--------------------------------------\n");
	printf("multiplicação elementos identidade e matrix: \n");
	print_matrix(mul(id_matrix, matrix_c));
	printf("--------------------------------------\n");
	printf("Multiplicação da matrix identidade e matrix: \n");
	print_matrix(matmul(id_matrix, matrix_c));
	printf("--------------------------------------\n");

	return 0;
}
