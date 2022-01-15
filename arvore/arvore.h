

typedef struct no *Arv;

struct aluno{    //todo o conteudo do nó 
    int matricula;
    char nome[50];
    int telefone;
};

struct no{
    struct aluno conteudo;  //struct com os valores do nó
    int alt; //apontador que representa a altura do nó  
    struct no *esq, *dir; //apontador esquerda 
};


//auxiliares 

int fator_balanceamento(Arv r);

int altura(Arv r);

int maior(int a,int b);

int verificar_lista_vazia(Arv r);

Arv criar_no(int matricula,char nome[],int telefone);

Arv menor_filho_esq(Arv meu_no);

Arv balanceamento_dir(Arv r);

Arv balanceamento_esq(Arv r);

Arv inicializar_ponteiros(Arv r);

//rotações

Arv rotacao_sd(Arv r);

Arv rotacao_se(Arv r);

Arv rotacao_dd(Arv r);

Arv rotacao_de(Arv r);

//principais
Arv inicializar();

Arv inserir_arvore(Arv r,int matricula,char nome[],int telefone);

int remover_arvore(Arv *r,int matricula);

void buscar_arvore(Arv r,int matricula);

void printar_arvore(Arv r, int nivel);
		
//Amaury Mário Ribeiro Neto | Matrícula: 17.205.0071