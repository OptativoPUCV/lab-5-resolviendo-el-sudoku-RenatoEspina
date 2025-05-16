#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int visto[10];

// Validar filas
  for (int i = 0; i < 9; i++) {
    for (int x = 0; x < 10; x++) visto[x] = 0;
    for (int j = 0; j < 9; j++) {
      int val = n->sudo[i][j];
      if (val == 0) continue;
      if (visto[val]) return 0;
      visto[val] = 1;
    }
  }

// Validar columnas
  for (int j = 0; j < 9; j++) {
    for (int x = 0; x < 10; x++) visto[x] = 0;
    for (int i = 0; i < 9; i++) {
      int val = n->sudo[i][j];
      if (val == 0) continue;
      if (visto[val]) return 0;
      visto[val] = 1;
    }
  }

// Validar submatrices 3x3
  for (int k = 0; k < 9; k++) {
    for (int x = 0; x < 10; x++) visto[x] = 0;
    for (int p = 0; p < 9; p++) {
      int i = 3 * (k / 3) + (p / 3);
      int j = 3 * (k % 3) + (p % 3);
      int val = n->sudo[i][j];
      if (val == 0) continue;
      if (visto[val]) return 0;
      visto[val] = 1;
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  for(size_t i=0;i<9;i++) for(size_t k=0;k<9;k++){
    if(n->sudo[i][k]==0){
      for(size_t j=1;j<=9;j++){
        Node* n2=copy(n);
        n2->sudo[i][k]=j;
        if(is_valid(n2)) pushBack(list,n2);
        else free(n2);
      }
      return list;
    }
  }
  return list;
}


int is_final(Node* n){
  for(size_t i=0;i<9;i++) for(size_t k=0;k<9;k++){
    if(n->sudo[i][k]==0) return 0;
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* pila = createStack();
  push(pila, initial);
  while (!is_empty(pila)) {
    Node* n = top(pila);
    pop(pila);
    (*cont)++;
    if (is_final(n)) {
      return n;
    }
    List* adyacentes = get_adj_nodes(n);
    Node* nodo = first(adyacentes);
    while (nodo != NULL) {
      push(pila, nodo);
      nodo = next(adyacentes);
    }
    free(n);
  }
  clean(pila);
  return NULL;
}





/*int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/