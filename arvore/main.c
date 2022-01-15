#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"arvore.h"

Arv raiz;

int main(){
    int escolha;
    char nome[50];
    int telefone;
    int matricula;
    int m,contador;
    do{
        printf("\n\tMenu\n\n");
        printf("1-Criar Lista Telefônica\n");
        printf("2-Inserir\n");
        printf("3-Remover\n");
        printf("4-Buscar\n");
        printf("5-Imprimir\n");
        printf("0-Sair\n\n");
        scanf("%d",&escolha);
        switch(escolha){
            case 1:
                raiz=inicializar();
                printf("Lista telefônica criada com sucesso\n");
                break;

            case 2: //inserção
                printf("\nPor favor entre com a matrícula do aluno que deseja INSERIR\n");
                scanf("%d",&matricula);
                printf("Por favor entre com o nome do aluno\n");
                scanf("%s",nome);
                printf("Por favor entre com o telefone do aluno\n");
                scanf("%d",&telefone);
                raiz=inserir_arvore(raiz,matricula,nome,telefone);
                printf("Valor inserido com sucesso!\n");
                printf("\n\tLista:\n");    //printando arvore após a inserção 
                verificar_lista_vazia(raiz);
                printar_arvore(raiz, 1);
                printf("\n");
                break;

            case 3:  //remoção
                m = verificar_lista_vazia(raiz);
                if(m){
                    break;
                }
                printf("\nPor favor informe o número de matrícula do aluno que deseja REMOVER\n");
                scanf("%d",&matricula);
                remover_arvore(&raiz,matricula);  
                m = verificar_lista_vazia(raiz);
                //printando arvore após a remoção
                if(m){
                    break;
                }
                printar_arvore(raiz, 1);
                printf("\n");
                break;

            case 4: //buscar
                m = verificar_lista_vazia(raiz);
                if(m){
                    break;
                }
                printf("\nPor favor informe o número de matrícula do aluno que deseja BUSCAR\n");
                scanf("%d",&matricula);
                buscar_arvore(raiz,matricula);  
                break;

            case 5: //imprimir
                m = verificar_lista_vazia(raiz);
                if(m){
                    break;
                }
                printf("\n\tLista:\n");
                printar_arvore(raiz, 1);
                printf("\n");
                break;
            case 0: //sair
                return 0;

            default:  
                printf("opção inválida");
        }
    }while(escolha!=0);  //laço para fazer loop no menu
}

		
//Amaury Mário Ribeiro Neto | Matrícula: 17.205.0071