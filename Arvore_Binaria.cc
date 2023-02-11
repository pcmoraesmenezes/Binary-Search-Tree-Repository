#include <stdio.h> // incluindo a biblioteca basica de C
#include <stdlib.h> // biblioteca que permite o uso das funções free e malloc
#include <iostream> // biblioteca basica de C++
typedef struct arvore // criando uma struct
{
    int valor; //variavel que recebera os valores a ser armazenados
    arvore * direita; // variavel do tipo arvore cujo nome é direita
    arvore * esquerda; // variavel do tipo arvore cujo nome é esquerda
}arvore; // nome da struct

arvore * busca(int valor, arvore * raiz) // função de busca, recebe como parametro o valor a ser buscado e uma variavel do tipo arvore
{
  if(raiz == NULL) // verifica se a raiz e nula
  { 
    printf("Valor não encontrado!\n"); // mensagem na tela
    return NULL; // encerra a função
  }
  if( raiz->valor == valor) // verifica se o valor da raiz e igual ao valor desejado
   { 
    printf("Achou!\n"); // mensagem na tela
    return raiz; // encerra a função
   }
  if(valor < raiz->valor) // verifica se o valor desejado e menor que o valor na raiz
  {
    return busca(valor, raiz->esquerda); // chama recursivamente a função, entretanto para o lado esquerdo da arvore
  }
  return busca(valor, raiz->direita); // caso contrario chamará a função recursivamente para o lado direito da arvore

}
arvore * removeNo(int valor, arvore * raiz) // função de removeNó, recebe como parametro o valor a ser removido e uma variavel do tipo arvore
{
  if(raiz == NULL) // verifica se a raiz e nula
  {
    return NULL; // encerra a função
  }
  if(valor < raiz->valor) // verifica se o valor desejado e menor que o valor na raiz
  {
    raiz->esquerda = removeNo(valor, raiz->esquerda); // atribuí o lado esquerdo da arvore a função remove no, os parametros são o valor e a propria raiz apontada para a esquerda
  }
  else if(valor > raiz->valor) // senao se
  {
    raiz->direita = removeNo(valor, raiz->direita); // atribui o lado direito da arvore a função remove nó
  }
  else //se nao
  {
    if(raiz->esquerda == NULL && raiz->direita == NULL) // verifica se o valor apontado para a esquerda E o valor apontado para a direita são nulos
    {
      free(raiz); // libera o espaço na memoria
      raiz = NULL; // faz a raiz receber null
    }
    else if (raiz->esquerda == NULL) // se nao se, verificara se o valor apontado para a esquerda e nulo
    {
      arvore * temp = raiz; // criando uma variavel auxiliar do tipo arvore que recebera a raiz
      raiz = raiz->direita; // fazendo a raiz receber raiz apontada para a direita
      free(temp); // liberando espaço na memoria
    }
    else if(raiz->direita == NULL) // se nao se, verificará se o valor apontado para a direita da raiz e nulo
    {
      arvore * temp = raiz; // criando uma variavel auxiliar do tipo arvore que recebera a raiz
      raiz = raiz->esquerda; // fazendo a raiz receber a raiz apontada para a esquerda
      free(temp); // liberando espaço na memoria
    }
    else // se nao 
    {
      arvore * temp = raiz->direita; // criando uma variavel do tipo arvore e está recebendo a raiz apontada para a direita
      while(temp->esquerda!=NULL) // enquanto o lado esquerdo da arvore não for nulo
      {
        temp = temp->esquerda; // andando com a arvore
      }
      raiz->valor = temp->valor; // atribuindo o valor a variavel temporaria apontada para valor
      raiz->direita = removeNo(temp->valor, raiz->direita); // atribuindo o lado direito da arvore a função removeNó
    }
  }
  return raiz; // encerrando a função
}
arvore * inicia_no(int valor) // função que irá iniciar a arvore
  {
    arvore * inicia = (arvore *) malloc(sizeof(arvore)); // criando um espaço dinamicamente na memoria do tipo arvore e do tamanho da arvore
    inicia->valor = valor; // atribuindo o valor da variavel inicia ao valor  iniciado pela função
    inicia->direita = NULL; // atribuindo o lado direito da arvore como nulo
    inicia->esquerda = NULL; // atribuindo o lado esquerdo da arvore como nulo
    return inicia; // encerrando a função
  }
  
arvore * insere (arvore * raiz, int valor) // função que irá inserir valores na arvore
{
  if(raiz == NULL) // verifica se a raiz é nula
  {
    raiz = inicia_no(valor); // chama a função inicia_no
  }
  else if(valor <= raiz->valor) //se nao se, verifica se o valor a ser inserido e menor que o valor no nó
  {
    raiz->esquerda = insere(raiz->esquerda, valor); // chama recursivamente a função insere, atribuindo ao nó esquerdo esquerda a função
  }
  else // se nao
  {
    raiz->direita = insere(raiz->direita, valor); // chama recursivamente a função insere, atribuindo ao nó direito
  }
return raiz; // encerra a função
}

void printTree(arvore * raiz, int level = 0) // função que irá printar a arvore na tela, recebe como parametro uma variavel do tipo arvore e uma variavel que irá contabilizar a arvore para printar os valores de forma sincrona
{
  if (raiz == NULL) // verifica se a raiz é nula
  {
    return; // encerra a função
  }
  printTree(raiz->direita, level + 1); // chama recursivamente a função, mas para o lado direito e contabiliza a variavel 'level'
  for (int i = 0; i < level; i++) // // laço de repetição para printar todo o lado direito
  {
    std::cout << "       "; // saltando espaços 
  }
  std::cout << raiz->valor << std::endl; // printado o valor
  printTree(raiz->esquerda, level + 1); // chama a função recursivamente, mas agora para o lado esquerdo
}

int main() //corpo principal da função
{   int level = 0; // variavel que mostrará a arvore detalhadamente
    arvore * raiz = NULL; // inicializando a arvore
    int navegador = 0; // essa variavel será responsavel por guiar o usuario na interface
    int adicionar = 0; // variavel responsavel por receber o numero que o usuario gostaria de inserir na fila
    while (true) // essa condição faz com que o laço de repetição seja sempre verdade
   { 
        printf("Bem vindo a sua Arvore Binaria de Busca! Para visualizar a sua Arvore digite '1', para inserir um valor em sua Arvore digite '2', para remover um elemento de sua arvore digite '3' e para sair digite '4'\n"); // mensagem para o usuario
        scanf("%d", &navegador); // está recebendo do usuario um numero para ação
        while (navegador != 1 && navegador != 2 && navegador != 3 && navegador != 4) // verifica se o usuario digitou algo além do que esperado
        {
            printf("Você não informou uma opção válida! Tente novamente \n"); // informa que ele não digitou uma opção válida das que foram ofertadas
            scanf("%d", &navegador);// recebe do usuario outra opção
        }
        if (navegador == 1) // verifica se ele escolheu a opção 1
        {
            if(raiz == NULL) // verifica se a arvore está vazia
            {
                printf("Arvore vazia ! \n"); // retorna uma mensagem
            }
            else
            { // senao
                printf("Você optou por visualizar a Arvore!\n "); // retorna uma mensagem
                printTree(raiz, level); // imprime a arvore na tela
            }
        }
        if (navegador == 2) // verifica se ele optou pela opção 2
        {
            printf("Você optou por inserir! Por favor insira o numero abaixo: \n"); // retorna uma mensagem
            scanf("%d", &adicionar); // recebe do usuario um numero a ser adicionado
            raiz = insere(raiz, adicionar); // chamando a função que adiciona elementos na arvore
        }
        if (navegador == 3) // verifica se o usuario optou pela opção 3
        {
            if(raiz == NULL) // verifica se a arvore está vazia
            {
                printf("Arvore vazia! \n"); // retorna uma mensagem
            }
            else // senao
            {
              printf("Você optou por remover um elemento da arvore!\n "); // imprime uma mensagem na tela
              printf("Informe um valor!\n"); // imprime uma mensagem na tela
              scanf("%d", &adicionar); // pede ao usuario um valor
              removeNo(adicionar, raiz);//remove um valor
            }
        }
        if(navegador == 4) // verifica se o usuario optou pela opção 4
        {
            printf("Você optou por realizar uma busca, informe o valor desejado a ser buscado!\n"); // mensagem na tela
            scanf("%d", &adicionar); // pede ao usuario um valor
            busca(adicionar, raiz); // função de busca
        }
        if (navegador == 5) // verifica se o usuario optou pela opção 5
        {   printf("Você optou por sair do Navegador! \n"); // retorna uma mensagem
            break; // quebra o laço de repetição
        }
    }
}

