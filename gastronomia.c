#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gastronomia.h"

void carregarRegioes(ListaRegiao *lr) {

	FILE *arq;

	arq = fopen("regioes.txt","r");

	if(arq == NULL) {
		printf("Erro ao abrir arquivo de regioes\n");
		return;
	}


	int id;
	char nome[100];
	char descricao[400];


	while(fscanf(arq,"%d",&id)==1) {

		fscanf(arq," %[^\n]",nome);
		fscanf(arq," %[^\n]",descricao);


		inserirRegiao(lr,id,nome,descricao);
	}


	fclose(arq);
}

void carregarPratos(ListaRegiao *lr) {

	FILE *arq;

	arq = fopen("pratos.txt","r");

	if(arq == NULL) {
		printf("Erro ao abrir arquivo de pratos\n");
		return;
	}


	int idRegiao;
	int idPrato;

	char nome[500];
	char ingredientes[700];
	char modo[700];

	float tempo;


	while(fscanf(arq,"%d",&idRegiao)==1) {


		fscanf(arq,"%d",&idPrato);

		fscanf(arq," %[^\n]",nome);

		fscanf(arq," %[^\n]",ingredientes);

		fscanf(arq," %[^\n]",modo);

		fscanf(arq,"%f",&tempo);



		Regiao *r = buscarElementoRegiao(lr,idRegiao);


		if(r != NULL) {

			inserirPrato(&r->pratos,
			             idPrato,
			             nome,
			             ingredientes,
			             modo,
			             tempo);
		}

	}


	fclose(arq);
}



ListaRegiao *criarRegiao() {

	ListaRegiao *lr= (ListaRegiao*)malloc(sizeof(ListaRegiao));
	if(lr==NULL) {
		return NULL;
	}

	lr->inicio=NULL;
	lr->fim=NULL;
	lr->qtd=0;

	return lr;
}

int  inserirRegiao(ListaRegiao *lr, int id, char nome[], char descricao[]) {

	Regiao *novo=(Regiao*)malloc(sizeof(Regiao));

	if(novo==NULL) {
		return 0;
	}
	if(buscarElementoRegiao(lr,id)!=NULL) {
		free(novo);
		return 0;
	}
	novo->id=id;
	strcpy(novo->nome,nome);
	strcpy(novo->descricao,descricao);

	novo->pratos.inicio=NULL;
	novo->pratos.fim=NULL;
	novo->pratos.qtd=0;

	if(lr->inicio==NULL) {

		novo->prox=NULL;
		novo->ant=NULL;

		lr->inicio=novo;
		lr->fim=novo;
		lr->qtd++;
		return 1;
	}

	else {

		novo->prox=lr->inicio;
		novo->ant=NULL;


		lr->inicio->ant=novo;
		lr->inicio=novo;
		lr->qtd++;

		return 1;
	}

	return 0;

}

void listarRegiao(ListaRegiao *lr) {

	Regiao *aux=lr->inicio;

	while(aux!=NULL) {

		printf("\n Id: %d",aux->id);
		printf("\n Nome: %s",aux->nome);
		printf("\n Desceição: %s",aux->descricao);

		aux=aux->prox;
	}

}

int qtdRegiao(ListaRegiao *lr) {

	return lr->qtd;
}

void removerTodosPratos(ListaPrato *lp){

    Prato *aux = lp->inicio;

    while(aux != NULL){

        int id = aux->id;

        aux = aux->prox;

        removerPrato(lp, id);
    }
}


void removerRegiao(ListaRegiao *lr, int id){

    if(lr == NULL || lr->inicio == NULL){
        return;
    }

    Regiao *atual = lr->inicio;

    while(atual != NULL && atual->id != id){
        atual = atual->prox;
    }

    if(atual == NULL){
        printf("Regiao nao encontrada!\n");
        return;
    }

    removerTodosPratos(&atual->pratos);

    if(atual->ant == NULL){
        lr->inicio = atual->prox;
    }
    else{
        atual->ant->prox = atual->prox;
    }

    if(atual->prox == NULL){
        lr->fim = atual->ant;
    }
    else{
        atual->prox->ant = atual->ant;
    }

    free(atual);
    lr->qtd--;
}

Regiao*buscarElementoRegiao(ListaRegiao *lr,int id) {

	Regiao *aux=lr->inicio;

	while(aux!=NULL) {

		if(aux->id==id) {

			return aux;
		}

		aux=aux->prox;
	}

	return NULL;
}

void alterarRegiao(ListaRegiao *lr,int id) {

	Regiao *r = buscarElementoRegiao(lr,id);

	if(r==NULL) {
		printf("Nao encontrada");
		return;
	}

	printf("Novo nome: ");
	scanf(" %[^\n]", r->nome);

	printf("\n Nova descricao: ");
	scanf(" %[^\n]", r->descricao);
}



ListaPrato *criarPrato() {
	ListaPrato *lp = (ListaPrato*) malloc(sizeof(ListaPrato));
	if  (lp == NULL) {
		return NULL;
	}
	lp->inicio = NULL;
	lp->fim = NULL;
	lp->qtd = 0;
	return lp;
}


int inserirPrato(ListaPrato *lp, int id, char nome[], char ingredientes[],char modoPreparo[],float tempoPreparo) {


	Prato *novoprato = (Prato*) malloc(sizeof(Prato));
	if (novoprato == NULL) {
		return 0;
	}

	if (buscarElementoPrato(lp, id)!= NULL) {
		free(novoprato);
		return 0;
	}


	novoprato->id = id;
	strcpy(novoprato->nome, nome);
	strcpy(novoprato->ingredientes, ingredientes);
	strcpy(novoprato->modoPreparo, modoPreparo);
	novoprato->tempoPreparo = tempoPreparo;

	if(lp->inicio == NULL) {
		novoprato->prox = NULL;
		novoprato->ant = NULL;
		lp->inicio = novoprato;
		lp->fim = novoprato;

	} else {
		novoprato->prox= lp->inicio;
		novoprato->ant= NULL;
		lp->inicio->ant = novoprato;
		lp->inicio= novoprato;
	}

	lp->qtd++;
	return 1;
}


Prato *buscarElementoPrato(ListaPrato *lp,int id) {
	Prato *aux= lp->inicio;

	while(aux!=NULL) {
		if(aux->id==id) {
			return aux;
		}
		aux=aux->prox;
	}
	return NULL;
}

void alterarPrato(ListaPrato *lp, int id) {


	Prato *p = buscarElementoPrato(lp,id);

	if(p==NULL) {
		printf("Nao encontrada");
		return;
	}

	printf("Novo nome: ");
	scanf(" %[^\n]", p->nome);

	printf("Novos ingredientes: ");
	scanf(" %[^\n]", p->ingredientes);

	printf("Novo modo de preparo: ");
	scanf(" %[^\n]", p->modoPreparo);

	printf("Novo tempo de preparo: ");
	scanf("%f",&p->tempoPreparo);
}




void removerPrato(ListaPrato *lp, int id){

    if(lp == NULL || lp->inicio == NULL){
        return;
    }

    Prato *atual = lp->inicio;

    // Procura o prato
    while(atual != NULL && atual->id != id){
        atual = atual->prox;
    }

    if(atual == NULL){
        printf("Prato nao encontrado!\n");
        return;
    }

    if(atual->ant == NULL){
        lp->inicio = atual->prox;
    }
    else{
        atual->ant->prox = atual->prox;
    }

    if(atual->prox == NULL){
        lp->fim = atual->ant;
    }
    else{
        atual->prox->ant = atual->ant;
    }

    free(atual);
    lp->qtd--;
}



void listarPrato(ListaPrato *lp) {

	Prato *aux=lp->inicio;

	while(aux!=NULL) {

		printf("\n Id: %d ",aux->id);
		printf("\n Nome: %s: ",aux->nome);
		printf("\n Ingredientes: %s ",aux->ingredientes);
		printf("\n Modo Preparo: %s ",aux->modoPreparo);
		printf("\n Tempo Preparo: %f ",aux->tempoPreparo);
		aux=aux->prox;
	}
}

int qtdPrato(ListaPrato *lp) {
	return lp->qtd;
}

void filtrarTempo(ListaRegiao *lr, float tempo){

    Regiao *r = lr->inicio;
    int encontrou = 0;

    while(r != NULL){

        Prato *p = r->pratos.inicio;

        while(p != NULL){

            if(p->tempoPreparo == tempo){

                printf("\nRegiao: %s", r->nome);
                printf("\nPrato: %s", p->nome);
                printf("\nIngredientes: %s", p->ingredientes);
                printf("\nModo de preparo: %s", p->modoPreparo);
                printf("\nTempo de preparo: %.2f minutos\n", p->tempoPreparo);

                encontrou = 1;
            }

            p = p->prox;
        }

        r = r->prox;
    }

    if(encontrou == 0){
        printf("Nenhum prato encontrado com esse tempo.\n");
    }
}


void localizarPrato(ListaRegiao *lr, char nome[]){

    Regiao *r = lr->inicio;

    while(r != NULL){

        Prato *p = r->pratos.inicio;

        while(p != NULL){

            if(strcmp(p->nome, nome) == 0){

                printf("\nPrato encontrado!\n");
                printf("Regiao: %s\n", r->nome);
                printf("Nome: %s\n", p->nome);
                printf("Ingredientes: %s\n", p->ingredientes);
                printf("Modo de preparo: %s\n", p->modoPreparo);
                printf("Tempo de preparo: %.2f minutos\n", p->tempoPreparo);

                return;
            }

            p = p->prox;
        }

        r = r->prox;
    }

    printf("\nPrato nao encontrado!\n");
}

void listarTodosPratos(ListaRegiao *lr){

    Regiao *r = lr->inicio;
    int encontrou = 0;

    while(r != NULL){

        Prato *p = r->pratos.inicio;

        while(p != NULL){

            printf("\nRegiao: %s", r->nome);
            printf("\nPrato: %s\n", p->nome);

            encontrou = 1;

            p = p->prox;
        }

        r = r->prox;
    }

    if(encontrou == 0){
        printf("Nenhum prato cadastrado!\n");
    }
}

void relatorioGeral(ListaRegiao *lr){

    if(lr == NULL){
        return;
    }

    Regiao *r = lr->inicio;
    int totalPratos = 0;

    printf("\n========== RELATORIO GERAL ==========\n");
    printf("\nQuantidade de regioes cadastradas: %d\n", lr->qtd);

    while(r != NULL){

        printf("\n====================================");
        printf("\nRegiao: %s", r->nome);
        printf("\nDescricao: %s", r->descricao);
        printf("\nQuantidade de pratos: %d\n", r->pratos.qtd);

        Prato *p = r->pratos.inicio;

        while(p != NULL){

            printf("\n----------- PRATO -----------");
            printf("\nId: %d", p->id);
            printf("\nNome: %s", p->nome);
            printf("\nIngredientes: %s", p->ingredientes);
            printf("\nModo de preparo: %s", p->modoPreparo);
            printf("\nTempo de preparo: %.2f minutos\n", p->tempoPreparo);

            totalPratos++;

            p = p->prox;
        }

        r = r->prox;
    }

    printf("\n====================================");
    printf("\nTotal de pratos cadastrados: %d", totalPratos);
    printf("\n====================================\n");
}

void filtrarTempoIngrediente(ListaRegiao *lr, float tempo, char ingrediente[]){

    Regiao *r = lr->inicio;
    int encontrou = 0;

    while(r != NULL){

        Prato *p = r->pratos.inicio;

        while(p != NULL){

            if(p->tempoPreparo == tempo &&
               strstr(p->ingredientes, ingrediente) != NULL){

                printf("\nRegiao: %s", r->nome);
                printf("\nPrato: %s", p->nome);
                printf("\nIngredientes: %s", p->ingredientes);
                printf("\nModo de preparo: %s", p->modoPreparo);
                printf("\nTempo de preparo: %.2f minutos\n", p->tempoPreparo);

                encontrou = 1;
            }

            p = p->prox;
        }

        r = r->prox;
    }

    if(encontrou == 0){
        printf("\nNenhum prato encontrado com esses criterios.\n");
    }
}

void menorTempo(ListaRegiao *lr, float tempo){

    Regiao *r = lr->inicio;
    int encontrou = 0;

    while(r != NULL){

        Prato *p = r->pratos.inicio;

        while(p != NULL){

            if(p->tempoPreparo <= tempo){

                printf("\nRegiao: %s", r->nome);
                printf("\nPrato: %s", p->nome);
                printf("\nIngredientes: %s", p->ingredientes);
                printf("\nModo de preparo: %s", p->modoPreparo);
                printf("\nTempo de preparo: %.2f minutos\n", p->tempoPreparo);

                encontrou = 1;
            }

            p = p->prox;
        }

        r = r->prox;
    }

    if(encontrou == 0){
        printf("\nNenhum prato encontrado com tempo de preparo de ate %.2f minutos.\n", tempo);
    }
}
