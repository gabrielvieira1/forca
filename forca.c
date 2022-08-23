#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

char palavrasecreta[20];
char chutes[26];
int chutesdados = 0;

int enforcou()
{
 int erros = 0;
 for (int i = 0; i < chutesdados; i++)
 {
  int existe = 0;
  for (int j = 0; j < strlen(palavrasecreta); j++)
  {
   if (chutes[i] == palavrasecreta[j])
   {
    existe = 1;
    break;
   }
  }
  if (!existe)
   erros++;
 }
 return erros >= 5;
}

int ganhou()
{
 for (int i = 0; i < strlen(palavrasecreta); i++)
 {
  if (!jachutou(palavrasecreta[i]))
   return 0;
 }
 return 1;
}

void abertura()
{
 printf("/****************/\n");
 printf("/ Jogo de Forca */\n");
 printf("/****************/\n\n");
}

void chuta()
{
 char chute;
 printf("\n\nQual letra? \n");
 scanf(" %c", &chute);

 chutes[chutesdados] = chute;
 chutesdados++;
}

int jachutou(char letra)
{
 int achou = 0;
 for (int j = 0; j < chutesdados; j++)
 {
  if (chutes[j] == letra)
  {
   achou = 1;
   break;
  }
 }
 return achou;
}

void desenhaforca()
{
 printf("Você já deu %d chutes\n", chutesdados);

 for (int i = 0; i < strlen(palavrasecreta); i++)
 {
  if (jachutou(palavrasecreta[i]))
  {
   printf("%c ", palavrasecreta[i]);
  }
  else
  {
   printf("_ ");
  }
 }
 printf("\n");
}

void escolhepalavra()
{
 FILE *f;
 f = fopen("palavras.txt", "r");
 if (f == NULL)
 {
  printf("Erro ao abrir o arquivo\n");
  exit(1);
 }
 int tamanho;

 fscanf(f, "%d", &tamanho);
 srand(time(NULL));
 int numero = rand() % tamanho;

 for (int i = 0; i < numero; i++)
 {
  fscanf(f, "%s", palavrasecreta);
 }
 fclose(f);
}

void adicionapalavra()
{
 char escolha;

 printf("\nDeseja adicionar uma palavra? (s/n) ");
 scanf(" %c", &escolha);

 if (escolha == 's')
 {
  char novapalavra[20];
  printf("\nDigite a palavra: ");
  scanf("%s", novapalavra);

  FILE *f;

  f = fopen("palavras.txt", "r+");
  if (f == NULL)
  {
   printf("Erro ao abrir o arquivo\n");
   exit(1);
  }
  int qtd;
  fscanf(f, "%d", &qtd);
  qtd++;
  fseek(f, 0, SEEK_SET);
  fprintf(f, "%d", qtd);

  fseek(f, 0, SEEK_END);
  fprintf(f, "\n%s", novapalavra);

  fclose(f);
 }
}

int main()
{
 abertura();
 escolhepalavra();

 do
 {
  desenhaforca();
  chuta();

 } while (!ganhou() && !enforcou());

 adicionapalavra();

 return 0;
}
