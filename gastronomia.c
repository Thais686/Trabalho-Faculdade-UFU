#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gastronomia.h"

void carregarRegioes(ListaRegiao *lr){

    FILE *arq;

    arq = fopen("regioes.txt","r");

    if(arq == NULL){
        printf("Erro ao abrir arquivo de regioes\n");
        return;
    }


    int id;
    char nome[100];
    char descricao[400];


    while(fscanf(arq,"%d",&id)==1){

        fscanf(arq," %[^\n]",nome);
        fscanf(arq," %[^\n]",descricao);


        inserirRegiao(lr,id,nome,descricao);
    }


    fclose(arq);
}

void carregarPratos(ListaRegiao *lr){

    FILE *arq;

    arq = fopen("pratos.txt","r");

    if(arq == NULL){
        printf("Erro ao abrir arquivo de pratos\n");
        return;
    }


    int idRegiao;
    int idPrato;

    char nome[500];
    char ingredientes[700];
    char modo[700];

    float tempo;


    while(fscanf(arq,"%d",&idRegiao)==1){


        fscanf(arq,"%d",&idPrato);

        fscanf(arq," %[^\n]",nome);

        fscanf(arq," %[^\n]",ingredientes);

        fscanf(arq," %[^\n]",modo);

        fscanf(arq,"%f",&tempo);



        Regiao *r = buscarElementoRegiao(lr,idRegiao);


        if(r != NULL){

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


void removerRegiao(ListaRegiao *lr, int iden) {

	// lembrar de na hora de fazer colocar o remover prato

	if(lr->inicio==NULL) {

		return;
	}


	if(lr->inicio==lr->fim) {

		if(lr->inicio->id==iden) {

			free(lr->inicio);
			lr->inicio=NULL;
			lr->fim=NULL;
			lr->qtd--;
			return;

		}
	}

	if(lr->inicio->id==iden) {

		Regiao *aux=lr->inicio;

		lr->inicio=aux->prox;
		lr->inicio->ant=NULL;
		lr->qtd--;
		free(aux);

		return;
	}

	Regiao *atual = lr->inicio;

	while (atual != NULL && atual->id != iden) {
		atual = atual -> prox;
	}
	if (atual == NULL) {
		printf("id não encontrado");
		return;
	}

	if(atual==lr->fim) {

		lr->fim=atual->ant;
		lr->fim->prox=NULL;

		free(atual);

	}

	else {

		atual->ant->prox=atual->prox;
		atual->prox->ant=atual->ant;

		free(atual);
	}
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


int inserirPrato(ListaPrato *lp, int id, char nome[], char ingredientes[],char modoPreparo[],float tempoPreparo){
    
    
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

void alterarPrato(ListaPrato *lp, int id){
    
    
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


void removerPrato(ListaPrato *lp,int id){
    
    
    	if(lp->inicio==NULL) {

		return;
	}


	if(lp->inicio==lp->fim) {

		if(lp->inicio->id==id) {

			free(lp->inicio);
			lp->inicio=NULL;
			lp->fim=NULL;
			lp->qtd--;
			return;

		}
	}

	if(lp->inicio->id==id) {

		Prato *aux=lp->inicio;

		lp->inicio=aux->prox;
		lp->inicio->ant=NULL;
		lp->qtd--;
		free(aux);

		return;
	}

	Prato *atual = lp->inicio;

	while (atual != NULL && atual->id != id) {
		atual = atual -> prox;
	}
	if (atual == NULL) {
		printf("id não encontrado");
		return;
	}

	if(atual==lp->fim) {

		lp->fim=atual->ant;
		lp->fim->prox=NULL;

		free(atual);

	}

	else {

		atual->ant->prox=atual->prox;
		atual->prox->ant=atual->ant;

		free(atual);
	}
	lp->qtd--;
}
    

void listarPrato(ListaPrato *lp){

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

int qtdPrato(ListaPrato *lp){
    return lp->qtd;
}
