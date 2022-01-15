#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"arvore.h"

//funções auxiliares 

int fator_balanceamento(Arv r){ //calcula e retorna o fator de balanceamento de um nó 
    return labs(altura(r->dir) - altura(r->esq));  //labs para pegar o valor absoluto
}

int altura(Arv r){   // retorna a altura de um nó 
    if(r==NULL){
        return -1;
    }
    return (r->alt);
}

int maior(int a, int b){  //retorna o maior valor 
    if(a>b){
        return a;
    }
    else{
        return b;
    }
}

Arv criar_no(int matricula,char nome[],int telefone){  //função para criar um nó e salvar o conteudo dele

    Arv novo=(Arv)malloc(sizeof(struct no));
    novo->conteudo.matricula = matricula;
    strcpy(novo->conteudo.nome,nome);
    novo->conteudo.telefone = telefone;
    novo->esq= NULL;
    novo->dir= NULL;
    return(novo);
}

Arv menor_filho_esq(Arv meu_no){  //função retorna o menor filho do lado esquerdo 
    
    Arv menor = meu_no; 
    Arv auxiliar = meu_no->esq;  //auxiliar
    while(auxiliar != NULL){  //busco o nó mais a esquerda existente 
        menor = auxiliar;
        auxiliar = auxiliar->esq; //indo para esquerda 
    }
    return (menor); //retorno ele 
}

Arv balanceamento_dir(Arv r){ //tendendo para a esquerda
    if( altura(r->esq->dir) <= altura(r->esq->esq) ){ //comparando alturas para verificar se a rotação é dupla ou simples              
        r=rotacao_sd(r);  //rotação simples
    }else{
        r=rotacao_dd(r);  //rotação dupla
    }
    return (r);
}

Arv balanceamento_esq(Arv r){  //tendendo para a direito
    if(altura(r->dir->esq) <= altura(r->dir->dir)){  //comparando alturas para verificar se a rotação é dupla ou simples
        r=rotacao_se(r); //rotação simples
    }
    else{
        r=rotacao_de(r); //rotação dupla
    }
    return (r);
}

int verificar_lista_vazia(Arv r){
    if(r==NULL){
        printf("Lista Vazia!\n");
        return 1;
    }else{
        return 0;
    }
}


//funções de rotação
Arv rotacao_sd(Arv r){  //rotação simples direita
    Arv aux;  //no auxiliar 
    aux = r->esq;
    r->esq = aux->dir;
    aux->dir = r;
    r->alt = maior( altura(r->dir), altura(r->esq) ) +1;  //recalculando a altura
    aux->alt = maior( altura(aux->esq), r->alt ) +1;  // atualizar altura do nó 
    printf("ROTAÇÃO DIREITA\n");
    return(aux);
    
}

Arv rotacao_se(Arv r){  //rotação simples direita
    Arv aux;  //no auxiliar 
    aux = r->dir;
    r->dir = aux->esq;
    aux->esq = r;
    r->alt = maior( altura(r->dir), altura(r->esq) ) +1;  //recalculando a altura
    aux->alt = maior( altura(aux->dir),r->alt ) +1;  // atualizar altura do nó 
    printf("ROTAÇÃO esquerda\n");
    return(aux);
}

Arv rotacao_dd(Arv r){  //rotação dupla direita
    //rotaciono para a esquerda e depois para direita
    r->esq= rotacao_se(r->esq);
    return (rotacao_sd(r));
}

Arv rotacao_de(Arv r){  //rotação dupla esquerda
    //rotaciono para a direita e depois para esquerda
    r->dir= rotacao_sd(r->dir);
    return (rotacao_se(r));
}


//funções principais 
Arv inicializar(){
    return NULL;
}

Arv inserir_arvore(Arv r,int matricula,char nome[], int telefone){  //duvida como inserir struct

    if(r==NULL){ //nó está vazio? então encontrei sua posição e vou salva-lo
        return (criar_no(matricula,nome,telefone));
    }

    if(matricula < r->conteudo.matricula){  //matricula a ser inserida é menor, vou para esquerda
        r->esq = inserir_arvore(r->esq,matricula,nome,telefone);  //recursão para a esquerda
        if((fator_balanceamento(r)) == 2){  //desbalanceada 
            r=balanceamento_dir(r);
        }
    }
    else if (matricula > r->conteudo.matricula){   //matricula a ser inserida é maior,vou para direita
        r->dir = inserir_arvore(r->dir,matricula,nome,telefone); //recursão para a direita
        if((fator_balanceamento(r)) == 2){  //desbalanceada 
            r=balanceamento_esq(r);
        }
    }
    r->alt = maior( altura(r->dir), altura(r->esq)) +1;  //atualizar altura do nó 
    return (r);
}

int remover_arvore(Arv *r, int matricula){ //busca o nó a ser removido 

    if(r==NULL){
        printf("Valor inexistente\n");
        return 0;
    }
    int recursao; //valor a ser retornado recursivamente para indicar que o nó ja foi removido

    if((*r)->conteudo.matricula < matricula){  //recursão para direita
        
        //o proximo nó possui um filho, terei q diminuir a altura do pai pois ele será removido.
        //repetirei antes de cada recursão
        if( (recursao = remover_arvore(&(*r)->dir,matricula) )==1){  //verificando se o nó ja foi removido
            if(r)
                (*r)->alt = maior( altura((*r)->dir), altura((*r)->esq)+1);//atualizando altura
            if(fator_balanceamento(*r) >= 2 ){ //desbalanceado
                *r=balanceamento_dir(*r);
            } 
        }
    }else if((*r)->conteudo.matricula > matricula ){   //recursão para esquerda
        
        if( ( recursao = remover_arvore(&(*r)->esq,matricula) ) ==1){ //verificando se o nó ja foi removido
            if(r)
                (*r)->alt = maior( altura((*r)->dir), altura((*r)->esq)+1);//atualizando altura
            if(fator_balanceamento(*r) >=2 ){  // desbalanceado
                *r=balanceamento_esq(*r);
            }
        }
    }
    else if((*r)->conteudo.matricula == matricula){  //achei o nó a ser removido
        if( (*r)->esq == NULL && (*r)->dir==NULL){ // nenhum filho
            printf("Matrícula %d removida com sucesso!", (*r)->conteudo.matricula);
            free(*r);
            *r = NULL;
        }else if ((*r)->esq != NULL && (*r)->dir != NULL){  //nó tem 2 filhos
            //subtituir pelo nó mais a esquerda da sub-arvore da direita 
            Arv temporario = menor_filho_esq((*r)->dir);  //meu nó temporario recebe o menor filho retornado pela função
            (*r)->conteudo.matricula = temporario->conteudo.matricula; //raiz recebe o conteudo do nó temporario
            remover_arvore(&(*r)->dir, (*r)->conteudo.matricula);
            if(fator_balanceamento(*r) >=2 ){  // desbalanceado
                *r = balanceamento_dir(*r);
            }
            printf("Matrícula %d removida com sucesso!!", matricula);
        }else{ //1 filho
            Arv auxiliar = *r;
            if( (*r)->dir != NULL){ // possui filho a direita
                *r = (*r)->dir; //filho da direita toma seu lugar
            }
            else{// possui filho a esquerda ou nenhum
                *r = (*r)->esq; //filho da esquerda toma seu lugar
            }
            free(auxiliar);  //removido o nó
            auxiliar = NULL;
            printf("Matrícula %d removida com sucesso!", matricula);

        }
        return 1;   
    }
    return (recursao);
}


void buscar_arvore(Arv r, int matricula){  //fazer verificação de arvore vazia e arvore nula anteriormente
    if(r==NULL){  
        printf("Não existe esse valor registrado\n");
        return;
    }
    if( r->conteudo.matricula == matricula){  //valor igual a chave
        //encontrei meu valor, printar dados e finalizar
        printf("\nMatricula: %d\n",r->conteudo.matricula);
        printf("Aluno: %s\n",r->conteudo.nome);
        printf("Telefone: %d\n\n",r->conteudo.telefone);  
        return;
    }
    if( r->conteudo.matricula > matricula){  //valor menor que a chave de busca 
        return (buscar_arvore(r->esq,matricula)); //recursão pra esquerda
    }else{ //valor menor que a chave de busca 
        return (buscar_arvore(r->dir,matricula)); //recursão pra direita
    }
}


void printar_arvore(Arv r, int nivel){   //(caminhamento central) (árvore é deitada)
    int i;
    if(r){
        printar_arvore(r->dir, nivel+1);
        printf("\n\n");
        for(i=0; i<nivel; i++){
            printf("\t");
        }
        printf("[%d]%d",r->alt, r->conteudo.matricula);
        printar_arvore(r->esq, nivel+1);
    }
}  
	
//Amaury Mário Ribeiro Neto | Matrícula: 17.205.0071
