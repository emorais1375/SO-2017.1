/*
 ============================================================================
 Nome        : alg01.c
 Autor       : Eduardo da Encarnação Morais
 Descrição   : Exclusão Mútua com espera ocupada - Solução de Peterson
 Disciplina  : Sistemas Operacionais
 Professor   : Ricardo Rios
 Período     : 2017.1
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FALSE 0
#define TRUE 1
#define N 2						/* numero do processo */

int turn;						/* De quem é a vez? */
int interested[N];				/* Todos os valores inicialmente em 0 */
FILE *file;

void ler_arquivo(){
	file = fopen("texto.txt", "r");	
	if(file == NULL){
		printf("Aquivo não pode ser aberto\n");
		exit (0);
	}	
	fscanf(file, "%i %i %i", &interested[0], &interested[1], &turn);
	fclose(file);
	printf("%i %i %i\n", interested[0], interested[1], turn);
}

void salvar_arquivo(){
	file = fopen("texto.txt", "w");	
	fprintf(file,"%i %i %i", interested[0], interested[1], turn);
	fclose(file);
	printf("%i %i %i\n", interested[0], interested[1], turn);
}

void enter_region(int process)	/* processo 0 ou 1 */
{	
	int other = 1 - process;	/* número do outro processo */
	
	ler_arquivo();	
	
	interested[process] = TRUE;
	turn = process;
	
	salvar_arquivo();
	
	while(turn == process && interested[other] == TRUE);	
}

void leave_region(int process){
	interested[process] = FALSE;
	FILE *file;
	salvar_arquivo();
}

int main(void){
	pid_t pid;
	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}
	if(pid == 0){
		printf("Process 0\n");
		enter_region(0);
		leave_region(0);
		printf("Process 0 finalizado.\n");		
	}
	else{
		printf("Process 1\n");		
		enter_region(1);
		leave_region(1);
		printf("Process 1 finalizado.\n");	
	}
	return EXIT_SUCCESS;
}
