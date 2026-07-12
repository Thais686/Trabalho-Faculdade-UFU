#ifndef _GASTRONOMIA_H
#define _GASTRONOMIA_H

struct prato{
    
    int id;
    char nome[50];
    char ingredientes[100];
    char modoPreparo[200];
    float tempoPreparo;
    
   struct prato *ant;
   struct prato *prox;
};
typedef struct prato Prato;

struct listaPrato{
    
    Prato *inicio;
    Prato *fim;
    int qtd;
};

typedef struct listaPrato ListaPrato;


struct regiao{
    
    int id;
    char nome[100];
    char descricao[300];
    
    ListaPrato pratos;
    
    struct regiao *ant;
    struct regiao *prox;
};
typedef struct regiao Regiao;

struct listaRegiao{
    
    Regiao *inicio;
    Regiao *fim;
    int qtd;
};

typedef struct listaRegiao ListaRegiao;

// as operações com a lista de região
void criarRegiao(ListaRegiao *lr);
void inserirRegiao(ListaRegiao *lr, int id, char nome[], char descricao[]);
Regiao *buscarElementoRegiao(ListaRegiao *lr,int id);
void alterarRegiao(ListaRegiao *lr, int id);
void removerRegiao(ListaRegiao *lr,int id);
void listarRegiao(ListaRegiao *lr);
int qtdRegiao(ListaRegiao *lr);

// as operaçoes com a lista de PratoTipico

void criarPrato(ListaPrato *pr);
void inserirPrato(ListaPrato *pr, int id, char nome[], char ingredientes[],char modoPreparo[],float tempoPreparo);
Prato  *buscarElementoPrato(ListaPrato *pr,int id);
void alterarPrato(ListaPrato *pr, int id);
void removerPrato(ListaPrato *pr,int id);
void listarPrato(ListaPrato *pr);
int qtdPrato(ListaPrato *pr);



#endif
