#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gastronomia.h"


ListaRegiao *criarRegiao(){
    
     ListaRegiao *lr= (ListaRegiao*)malloc(sizeof(ListaRegiao));
     if(lr==NULL){
         return NULL;
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
     if(buscarElementoRegiao(lr,id)!=NULL){
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
    
    Regiao *aux=lr->inicio;
    
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


void removerRegiao(ListaRegiao *lr, int iden){
        
        // lembrar de na hora de fazer colocar o remover prato 
        
    if(lr->inicio==NULL){
            
        return;
     }
    
    
    if(lr->inicio==lr->fim){
        
    if(lr->inicio->id==iden){
            
        free(lr->inicio);
        lr->inicio=NULL;
        lr->fim=NULL;
        lr->qtd--;
        return;
            
        }
    }
    
    if(lr->inicio->id==iden){
       
       Regiao *aux=lr->inicio;
       
       lr->inicio=aux->prox;
       lr->inicio->ant=NULL;
       lr->qtd--;
       free(aux);
       
       return;
   }
   
   Regiao *atual = lr->inicio;
   
        while (atual != NULL && atual->id != iden){
            atual = atual -> prox;
        }
        if (atual == NULL){
            printf("id não encontrado");
            return;
        }
        
        if(atual==lr->fim){
       
       lr->fim=atual->ant;
       lr->fim->prox=NULL;
       
       free(atual);
       
   }
   
   else{
       
       atual->ant->prox=atual->prox;
       atual->prox->ant=atual->ant;
       
       free(atual);
   }
        lr->qtd--;
    }

Regiao*buscarElementoRegiao(ListaRegiao *lr,int id){
    
     Regiao *aux=lr->inicio;
    
    while(aux!=NULL){
        
        if(aux->id==id){
            
            return aux;
        }
        
        aux=aux->prox;
    }
    
    return NULL;
}
    
void alterarRegiao(ListaRegiao *lr,int id){

    Regiao *r = buscarElementoRegiao(lr,id);

    if(r==NULL){
        printf("Nao encontrada");
        return;
    }

    printf("Novo nome: ");
    scanf(" %[^\n]", r->nome);

    printf("Nova descricao: ");
    scanf(" %[^\n]", r->descricao);
}

