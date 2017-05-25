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

void enter_region(int process)	/* processo 0 ou 1 */
{	
	int other;					/* número de outro processo */	
	other = 1 - process;
	
	FILE *file;
	file = fopen("texto.txt", "r");
	
	if(file == NULL){
		printf("Aquivo não pode ser aberto\n");
		return 0;
	}
	
	
	
	interested[process] = TRUE;
	turn = process;
	while(turn == process && interested[other] == TRUE);
}

void leave_region(int process){
	interested[process] = FALSE;
}

int main(void){
	pid_t pid;

	if((pid = fork()) < 0){
		perror("fork");
		exit(1);
	}
	if(pid == 0){
		printf("Eu sou filho\n");
		enter_region(0);
		leave_region(0);
		printf("Eu sou filho e terminei.\n");		
	}
	else{
		printf("Eu sou pai\n");		
		enter_region(1);
		leave_region(1);
		printf("Eu sou pai e terminei.\n");	
	}
	return EXIT_SUCCESS;
}
