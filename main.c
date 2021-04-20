#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define MAX_MORADORES 5

typedef struct condominos{
		int cpf;
		char nome[50];
		int apartamento;
		float debito;
		int ativo;
	}Condominio;
//Array para cadastro de condôminos
Condominio k[MAX_MORADORES];

void menu(); //OK
void cadastro(); //OK
void remover(); //OK
void consultar(); //OK
void lista(); //OK
void listaDev(); //OK
void listaPag(); //OK
void atualizarDebito(); //OK

int main(){
	int b;
	//Permite acentuação
	setlocale(LC_ALL, "Portuguese");
	menu();
	
	FILE *arquivo;
	arquivo = fopen("condôminos.txt","w+");
	
	fprintf(arquivo,"\t\t\tLista de Condôminos");
	fprintf(arquivo,"\n\t\t  -------------------------------");
	
	for(b = 0; b < MAX_MORADORES; b++){
		if(k[b].ativo == 1){
			fprintf(arquivo,"\nNome: %s",k[b].nome);
			fprintf(arquivo,"\nCPF: %d",k[b].cpf);
			fprintf(arquivo,"\nApartamento: %d",k[b].apartamento);
			if(k[b].debito == 0){
				fprintf(arquivo,"\nDébito: R$%.2f ( Pagador )", k[b].debito);
			}else if(k[b].debito > 0){
				fprintf(arquivo,"\nDébito: R$%.2f ( Devedor )", k[b].debito);
			}
			fprintf(arquivo,"\n-------------------------------");	
		}
	}
	fclose(arquivo);
	return 0;
}

void menu(){
	system("cls");
	int exit;
	//Menu principal
	do{
		system("cls");
		printf("\t\t\t\t\t\tBem vindo ao menu");
		printf("\n\t----------------------------------------------------------------------------------------------------");
		printf("\n\t0 - Sair do prgama\n\t1 - Cadastrar um novo condômino\n\t2 - Consultar condômino pelo cpf\n\t3 - Atualizar o débito do condômino pelo cpf\n\t4 - Exibir os condôminos devedores\n\t5 - Exibir os condôminos quites\n\t6 - Remover algum condômino");
		printf("\n\n\tDigite o número da opção desejada: ");
		scanf("%d", &exit);
		//system("cls");
		getchar();
		switch(exit){
			case 0:	
				exit = 0;
				system("cls");
				printf("O progama encerrará agora!");
				break;
			
			case 1:
				cadastro();
				break;
			
			case 2:
				consultar();
				break;
			
			case 3:
				atualizarDebito();
				break;
			
			case 4:
				listaDev();
				break;
			
			case 5:
				listaPag();
				break;
			
			case 6:
				system("cls");
				lista();
				printf("\n");
				remover();
				break;
			
			default:
				system("cls");
				printf("Você não digitou uma opção válida!");
		}
		getchar();		
	}while(exit != 0);
}

void cadastro(){
	int i;
	int cpf;
	char nome[50];
	int apartamento;
	float debito;
	int exit = 1;
	
	do{
		system("cls");
		printf("Digite o CPF: ");
		scanf("%d", &cpf);		
		fflush(stdin);
		printf("Digite o nome: ");
		scanf("%[^\n]s", &nome);		
		printf("Digite o número do apartamento: ");
		scanf("%d", &apartamento);		
		printf("Informe a situação de débito digitando o valor, caso esteja quite digite 0: R$ ");
		scanf("%f", &debito);
		
		for(i = 0; i < MAX_MORADORES; i++){
			if(k[i].ativo == 0){
				k[i].cpf = cpf;
				k[i].apartamento = apartamento;
				k[i].debito = debito;
				strcpy(k[i].nome, nome);
				k[i].ativo = 1;
				break;
			}
		}
		system("cls");
		printf("Cadastro realizado com sucesso!");
		printf("\n------------------------------\n");
		printf("Digite 0 para retornar ao MENU ou  1 para realizar novo cadastro: ");
		scanf("%d", &exit);	
	}while(exit != 0);
}

void lista(){
	system("cls");
	int i;
	printf("Lista de condôminos");
	for(i = 0; i < MAX_MORADORES; i++){
		if(k[i].ativo == 1){
			
			printf("\n------------------------\n");
			printf("CPF: %d", k[i].cpf);
			printf("\nNome: %s", k[i].nome);
			printf("\nApartamento: %d", k[i].apartamento);
			printf("\nDébito: R$ %.2f", k[i].debito);
		}
	}
}

void listaDev(){
	system("cls");
	int i;
	printf("Lista de condôminos devedores");
	for(i = 0; i < MAX_MORADORES; i++){
		if(k[i].debito > 0){
			
			printf("\n------------------------\n");
			printf("CPF: %d", k[i].cpf);
			printf("\nNome: %s", k[i].nome);
			printf("\nApartamento: %d", k[i].apartamento);
			printf("\nDébito: R$ %.2f", k[i].debito);
		}
	}
}

void listaPag(){
	system("cls");
	int i;
	printf("Lista de condôminos pagadores");
	for(i = 0; i < MAX_MORADORES; i++){
		if((k[i].debito == 0) && (k[i].ativo == 1)){
			
			printf("\n------------------------\n");
			printf("CPF: %d", k[i].cpf);
			printf("\nNome: %s", k[i].nome);
			printf("\nApartamento: %d", k[i].apartamento);
			printf("\nDébito: R$ %.2f", k[i].debito);
		}
	}
}

void remover(){
	int i, cpf, retorno;
	do{
		printf("\n------------------------------\n");
		printf("Digite o CPF do condômino que deseja deletar: ");
		scanf("%d", &cpf);
		printf("\n\n");
		for(i = 0; i < MAX_MORADORES; i++){
			if(cpf == k[i].cpf){
				k[i].cpf = -1;
				k[i].apartamento = -1;
				k[i].debito = -1.1;
				k[i].ativo = 0;
				printf("\nDeletado com sucesso!");
			}
		}
		printf("\n------------------------------\n");
		printf("\nDigite 0 para retornar ao MENU ou 1 para continuar deletando: ");
		scanf("%d", &retorno);
	}while((retorno != 0) || (cpf == k[i].cpf));
}

void consultar(){
	int i, cpf, retorno;
	do{
		system("cls");
		printf("Digite o CPF desejado para consulta: ");
		scanf("%d", &cpf);
		printf("\n------------------------------\n");
		for(i = 0; i < MAX_MORADORES; i++){
			if(cpf == k[i].cpf){
				printf("\nNome: %s", k[i].nome);
				printf("\nCPF: %d", k[i].cpf);
				printf("\nApartamento: %d", k[i].apartamento);
				if(k[i].debito == 0){
					printf("\nSituação de débito: R$ %.2f ( Pagador )\n", k[i].debito);
				}else if(k[i].debito > 0){
					printf("\nSituação de débito: R$ %.2f ( Devedor )\n", k[i].debito);
				}
			}
		}
		printf("\n------------------------------\n");
		printf("\nDigite 0 para retornar ao Menu ou 1 para nova consulta: ");
		scanf("%d", &retorno);
	}while((retorno != 0) || (cpf == k[i].cpf));
}

void atualizarDebito(){
	int i, cpf, retorno;
	do{
		system("cls");
		printf("Digite o CPF do condômino que deseja atualizar o débito: ");
		scanf("%d", &cpf);
		printf("\n------------------------------\n");
		for(i = 0; i < MAX_MORADORES; i++){
			if(cpf == k[i].cpf){
				printf("\nCaso esteja em débito digite o valor, caso esteja quite digite 0: R$ ");
				scanf("%f", &k[i].debito);
				printf("\nAlteração realizada com sucesso!\n");
			}
		}
		printf("\n------------------------------\n");
		printf("\nDigite 0 para retornar ao MENU ou 1 para nova atualização: ");
		scanf("%d", &retorno);
	}while((retorno != 0) || (cpf == k[i].cpf));
}
