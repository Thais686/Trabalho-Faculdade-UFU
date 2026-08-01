#ifndef _GASTRONOMIA_H
#define _GASTRONOMIA_H

struct prato{
    
    int id;
    char nome[500];
    char ingredientes[700];
    char modoPreparo[700];
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
    char descricao[400];
    
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

void carregarRegioes(ListaRegiao *lr);
void carregarPratos(ListaRegiao *lr);

// as operações com a lista de região
ListaRegiao *criarRegiao();
int inserirRegiao(ListaRegiao *lr, int id, char nome[], char descricao[]);
Regiao *buscarElementoRegiao(ListaRegiao *lr,int id);
void alterarRegiao(ListaRegiao *lr, int id);
void removerRegiao(ListaRegiao *lr,int id);
void listarRegiao(ListaRegiao *lr);
int qtdRegiao(ListaRegiao *lr);

// as operaçoes com a lista de PratoTipico

ListaPrato *criarPrato();
int inserirPrato(ListaPrato *lp, int id, char nome[], char ingredientes[],char modoPreparo[],float tempoPreparo);
Prato *buscarElementoPrato(ListaPrato *lp,int id);
void alterarPrato(ListaPrato *lp, int id);
void removerPrato(ListaPrato *lp,int id);
void listarPrato(ListaPrato *lp);
int qtdPrato(ListaPrato *lp);



#endif
