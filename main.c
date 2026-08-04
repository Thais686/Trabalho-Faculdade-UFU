#include <stdio.h>
#include <stdlib.h>
#include "gastronomia.h"

int main()
{
	ListaRegiao *lr = criarRegiao();
	
	if(lr == NULL){
    printf("Erro ao criar lista\n");
    return 1;
}

	carregarRegioes(lr);
	carregarPratos(lr);

	int op;

	do {

		printf("\n===== MENU =====\n");
		printf("1 - Inserir Regiao\n");
		printf("2 - Alterar Regiao\n");
		printf("3 - Remover Regiao\n");
		printf("4 - Buscar Regiao\n");
		printf("5 - Listar Regioes\n");
		printf("6 - Quantidade de Regioes\n");
		printf("7 - Inserir Prato\n");
		printf("8 - Alterar Prato\n");
		printf("9 - Remover Prato\n");
		printf("10 - Buscar Prato\n");
		printf("11 - Listar Pratos de uma Regiao\n");
		printf("12 - Quantidade de Pratos de uma Regiao\n");
		printf("13 - Pratos para fazer com um determinado tempo\n");
		printf("14 - Localizar o prato em qualquer região \n");
		printf("15 - Listar todos os pratos \n");
		printf("16 - Relatorio Geral \n");
		printf("17 - Filtrar pelo ingrediente e tempo \n");
		printf("18 - Buscar pratos com tempo de preparo menor ou igual ao informado\n");
		printf("0 - Sair\n");

		scanf("%d",&op);

		switch(op) {

		case 1: {

			int id;
			char nome[100];
			char descricao[400];

			printf("ID da regiao: ");
			scanf("%d",&id);

			printf("Nome da regiao: ");
			scanf(" %[^\n]",nome);

			printf("Descricao: ");
			scanf(" %[^\n]",descricao);

			if(inserirRegiao(lr,id,nome,descricao)) {
				printf("Regiao cadastrada com sucesso!\n");
			}
			else {
				printf("Erro ao cadastrar regiao!\n");
			}

			break;

		}

		case 2:
		{

			int id;

			printf("Digite o ID da regiao: ");
			scanf("%d",&id);

			if (alterarRegiao(lr, id)) {
				printf("Regiao alterada com sucesso!\n");
			} else {
				printf("Regiao nao encontrada!\n");
			}

			break;
		}

		case 3: {

			int id;

			printf("Digite o ID da regiao que deseja remover: ");
			scanf("%d", &id);

			if (removerRegiao(lr, id)) {
				printf("Regiao removida com sucesso!\n");
			} else {
				printf("Regiao nao encontrada!\n");
			}

			break;
		}

		case 4: {

			int id;
			Regiao *r;

			printf("Digite o ID da regiao: ");
			scanf("%d", &id);

			r = buscarElementoRegiao(lr, id);

			if(r == NULL) {
				printf("Regiao nao encontrada!\n");
			}
			else {
				printf("ID: %d\n", r->id);
				printf("Nome: %s\n", r->nome);
				printf("Descricao: %s\n", r->descricao);
			}

			break;
		}

		case 5:
		{

			if(qtdRegiao(lr) == 0) {
				printf("Nenhuma regiao cadastrada!\n");
			}
			else {
				listarRegiao(lr);
			}

			break;
		}

		case 6: {

			printf("Quantidade de regioes: %d\n", qtdRegiao(lr));

			break;
		}


		case 7:
		{

			int idRegiao;
			int idPrato;
			char nome[500];
			char ingredientes[700];
			char modoPreparo[700];
			float tempo;

			Regiao *r;

			printf("Digite o ID da regiao: ");
			scanf("%d",&idRegiao);

			r = buscarElementoRegiao(lr,idRegiao);

			if(r == NULL) {
				printf("Regiao nao encontrada!\n");
				break;
			}

			printf("ID do prato: ");
			scanf("%d",&idPrato);

			printf("Nome do prato: ");
			scanf(" %[^\n]",nome);

			printf("Ingredientes: ");
			scanf(" %[^\n]",ingredientes);

			printf("Modo de preparo: ");
			scanf(" %[^\n]",modoPreparo);

			printf("Tempo de preparo: ");
			scanf("%f",&tempo);


			if(inserirPrato(r->pratos,
			                idPrato,
			                nome,
			                ingredientes,
			                modoPreparo,
			                tempo)) {

				printf("Prato cadastrado com sucesso!\n");
			}
			else {
				printf("Erro ao cadastrar prato!\n");
			}

			break;
		}

		case 8:
		{
			int idRegiao;
			int idPrato;

			Regiao *r;

			printf("Digite o ID da regiao: ");
			scanf("%d", &idRegiao);

			r = buscarElementoRegiao(lr, idRegiao);

			if (r == NULL) {
				printf("Regiao nao encontrada!\n");
				break;
			}

			printf("Digite o ID do prato: ");
			scanf("%d", &idPrato);

			if (alterarPrato(r->pratos, idPrato)) {
				printf("Prato alterado com sucesso!\n");
			} else {
				printf("Prato nao encontrado!\n");
			}

			break;
		}

		case 9:
		{
			int idRegiao;
			int idPrato;

			Regiao *r;

			printf("Digite o ID da regiao: ");
			scanf("%d", &idRegiao);

			r = buscarElementoRegiao(lr, idRegiao);

			if(r == NULL) {
				printf("Regiao nao encontrada!\n");
				break;
			}

			printf("Digite o ID do prato: ");
			scanf("%d", &idPrato);

			if(removerPrato(r->pratos, idPrato)) {
				printf("Prato removido com sucesso!\n");
			}
			else {
				printf("Prato nao encontrado!\n");
			}

			break;
		}

		case 10:
		{

			int idRegiao;
			int idPrato;

			Regiao *r;
			Prato *p;

			printf("Digite o ID da regiao: ");
			scanf("%d",&idRegiao);

			r = buscarElementoRegiao(lr,idRegiao);

			if(r == NULL) {
				printf("Regiao nao encontrada!\n");
				break;
			}

			printf("Digite o ID do prato: ");
			scanf("%d",&idPrato);

			p = buscarElementoPrato(r->pratos,idPrato);

			if(p == NULL) {
				printf("Prato nao encontrado!\n");
			}
			else {

				printf("\n--- Prato encontrado ---\n");
				printf("ID: %d\n",p->id);
				printf("Nome: %s\n",p->nome);
				printf("Ingredientes: %s\n",p->ingredientes);
				printf("Modo de preparo: %s\n",p->modoPreparo);
				printf("Tempo de preparo: %.2f\n",p->tempoPreparo);

			}

			break;
		}

		case 11:
		{

			int idRegiao;

			Regiao *r;

			printf("Digite o ID da regiao: ");
			scanf("%d",&idRegiao);

			r = buscarElementoRegiao(lr,idRegiao);

			if(r == NULL) {
				printf("Regiao nao encontrada!\n");
				break;
			}

			if(qtdPrato(r->pratos) == 0) {
				printf("Essa regiao nao possui pratos cadastrados!\n");
			}
			else {
				listarPrato(r->pratos);
			}

			break;
		}

		case 12:
		{

			int idRegiao;

			Regiao *r;

			printf("Digite o ID da regiao: ");
			scanf("%d",&idRegiao);

			r = buscarElementoRegiao(lr,idRegiao);

			if(r == NULL) {
				printf("Regiao nao encontrada!\n");
				break;
			}

			printf("Quantidade de pratos: %d\n", qtdPrato(r->pratos));

			break;

		}

		case 13:
		{
			float tempo;

			if(qtdRegiao(lr) == 0) {
				printf("Nenhuma regiao cadastrada!\n");
			}
			else {

				printf("Pratos para fazer em: ");
				scanf("%f",&tempo);

				if (!filtrarTempo(lr, tempo)) {
					printf("Nenhum prato encontrado com esse tempo.\n");
				}
			}

			break;

		}

		case 14:
		{

			if(qtdRegiao(lr) == 0) {
				printf("Nenhuma regiao cadastrada!\n");
			}
			else {

				char nome[500];

				printf("Digite o nome do prato: ");
				scanf(" %[^\n]", nome);

				if (!localizarPrato(lr, nome)) {
					printf("Prato nao encontrado!\n");
				}
			}

			break;

		}

		case 15:
		{
			if(qtdRegiao(lr) == 0) {
				printf("Nenhuma regiao cadastrada!\n");
			}
			else if(!listarTodosPratos(lr)) {
				printf("Nenhum prato cadastrado!\n");
			}

			break;
		}
		case 16:
		{

			if(!relatorioGeral(lr)) {
				printf("Nenhum dado cadastrado para gerar o relatorio!\n");
			}

			break;
		}

		case 17:
		{

			if(qtdRegiao(lr) == 0) {
				printf("Nenhuma regiao cadastrada!\n");
			}
			else {

				float tempo;
				char ingrediente[700];

				printf("Digite o tempo de preparo: ");
				scanf("%f", &tempo);

				printf("Digite um ingrediente: ");
				scanf(" %[^\n]", ingrediente);

				if (!filtrarTempoIngrediente(lr, tempo, ingrediente)) {
					printf("Nenhum prato encontrado com esses criterios!\n");
				}
			}

			break;
		}

		case 18:
		{

			if(qtdRegiao(lr) == 0) {
				printf("Nenhuma regiao cadastrada!\n");
			}
			else {

				float tempo;

				printf("Mostrar pratos com tempo de preparo de ate: ");
				scanf("%f", &tempo);

				if (!menorTempo(lr, tempo)) {
					printf("Nenhum prato encontrado com tempo de preparo de ate %.2f minutos.\n", tempo);
				}
			}

			break;
		}


		case 0: {

			printf("Encerrando...\n");
			
			liberarRegioes(lr);
			break;
		}

		}
	} while(op != 0);


	return 0;
}
