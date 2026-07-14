#include <stdio.h>
#include <stdlib.h>
#include "gastronomia.h"


ListaRegiao *criarRegiao(ListaRegiao *lr){
    
     ListaRegiao *lr= (ListaRegiao*)malloc(sizeof(ListaRegiao));
     if(lr==NULL){
         return;
     }
     
     lr->inicio=NULL;
     lr->fim=NULL;
     lr->qtd=0;
     
     return lr;
}

int  inserirRegiao(ListaRegiao *lr, int id, char nome[], char descricao[]){
    
    Regiao *novo=(Regiao*)malloc(sizeof(Regiao));
    
     if(novo==NULL){
         return 0;
     }
     
    novo->id=id;
    strcpy(novo->nome,nome);
    strcpy(novo->descricao,descricao);
    
    if(lr->inicio==NULL){
        
        novo->prox=NULL;
        novo->ant=NULL;
        
        lr->inicio=novo;
        lr->fim=novo;
        lr->qtd++;
        return 1;
    }
    
    else{
        
        novo->prox=lr->inicio;
        novo->ant=NULL;
        
       
        lr->inicio->ant=novo;
        lr->inicio=novo;
        lr->qtd++;
        
        return 1;
    }
    
    return 0;
    
}

void listarRegiao(ListaRegiao *lr){
    
    No *aux=lr->inicio;
    
    while(aux!=NULL){
        
        printf("%d",aux->id);
        printf("%s",aux->nome);
        printf("%s",aux->descricao);
        
        aux=aux->prox;
    }
    
}

int qtdRegiao(ListaRegiao *lr){
    
    return lr->qtd;
}