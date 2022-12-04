#include <stdio.h>
#include <stdlib.h>
typedef struct node Node;
struct node{
        int num, grau;
        Node *prox;
    };
Node *primeiro = NULL;
void insere(int num){
        Node *temp, *pt;
        temp =(struct node*)malloc(sizeof(struct node));
        temp->num = num;
        temp->grau = 0;
        temp->prox = NULL;
        if(primeiro == NULL){
            primeiro = temp;
        }
        else{
            pt=primeiro;
            while(pt->prox != NULL){
                pt = pt->prox;
            }
            pt->prox = temp;
        }
}
void ordtop(int *ordenados, int nv, int **adjacencia){
    int ord=0;
    Node *pt; 
    Node *temp;
    pt = primeiro;
    for(int i = 0; i<nv;i++){
        if(pt->grau == 0){
            ordenados[ord] = pt->num;
            ord++;
        }
    pt=pt->prox;
    }
    pt = primeiro;
    temp = primeiro;
    for(int i=0;i<ord;i++){
        int k=0;
        for(int j=0; j<nv;j++){
            if(pt->num == ordenados[i]){
                while(adjacencia[(pt->num)-1][k]!= 0){
                    if(adjacencia[(pt->num)-1][k]== temp->num){
                        (temp->grau)--;
                        k++;
                        if(temp->grau == 0){
                            ordenados[ord] = temp->num;
                            ord++;
                            temp= temp->prox;
                        }
                        else{
                            temp = temp->prox;
                        }
                    }
                    else{
                        if(temp->prox == NULL){
                            temp = primeiro;
                        }
                        else{
                        temp = temp->prox;
                        }
                    }
                }
            }
            else{
                pt=pt->prox;
            }
        }
        if(ord == nv){
            break;
        }
        pt=primeiro;
        temp=primeiro;
    }

}
int main(){
    Node *pt;
    pt =(struct node*)malloc(sizeof(struct node));
    int nv;
    int lin=0;
    scanf("%d", &nv);
    int **arestas, *ordenados, **adjacencia;
    int am = (nv*(nv-1))/2;
    adjacencia = calloc(nv-1, sizeof(int)*nv-1);
    ordenados = calloc(nv, sizeof(int)*nv);
    arestas = calloc(am, sizeof(int)*am);
    for(int i=0; i<am; i++){
        arestas[i] = calloc(1, sizeof(int)*am);
    }
    for(int i=0; i<nv; i++){
        adjacencia[i] = calloc(1, sizeof(int)*nv-1);
    }
    for(int i = 0; i<nv;i++){
        insere(i+1);
    }
    pt = primeiro;
    for(int i=0; i<am; i++){
        scanf("%d", &arestas[i][0]);
        lin++;
        if(arestas[i][0] == EOF){
            lin--;
            break;
        }
        for(int j=1; j<2; j++){
            scanf("%d", &arestas[i][j]);
        }
    }
    for(int i=0; i<nv; i++){
        for(int j=0; j<lin; j++){
            if(pt->num == arestas[j][1]){
                (pt->grau)++;
            }
        }
        if(pt->prox == NULL){
            break;
        }
        else{
            pt=pt->prox;
        }
    }
    pt=primeiro;
    for(int i=0; i<nv;i++){
        int k=0;
        for(int j=0;j<am;j++){
            if(arestas[j][0] == i+1){
                adjacencia[i][k] = arestas[j][1];
                k++;
            }   
        }
    }
    ordtop(ordenados, nv, adjacencia);
    for(int i=0; i<nv;i++){
        printf("%d ", ordenados[i]);
    }
}