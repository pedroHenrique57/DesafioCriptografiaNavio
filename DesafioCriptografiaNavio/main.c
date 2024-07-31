#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Input do código a ser descriptografado.
char textoCriptografado[] =
    "10010110 11110111 01010110 00000001 00010111 00100110 01010111 00000001 00010111 01110110 01010111 00110110 11110111 11010111 01010111 00000011";

// Calcula a quantidade de espaços dentro de uma String.
int calculaEspacos(const char *texto) {
  int totalDeEspacos = 0;

  for (int i = 0; texto[i] != '\0'; i++) {
    if (texto[i] == ' ') {
      totalDeEspacos++;
    }
  }
  return totalDeEspacos;
}

// Pega os bytes com espaços entre si e os converte para se adequar a convenção 0B00000000 para facilidade da manipulação dos dados.
char* formatarTextoCriptografado(const char *dadosBinarioCru) {
  // Calcula o tamanho exato de alocação de memória para não haver alocação de memória desnecessária.
  const int tamanhoTexto = strlen(dadosBinarioCru);
  const int quantidadeEspacos = calculaEspacos(dadosBinarioCru);
  char* dadosDivididosEmBytes = malloc((tamanhoTexto + quantidadeEspacos * 2 + 3 + 1) * sizeof(char));

  // Duplica a string para preservar o original ao usar strtok.
  char* dadosBinarioCruDup = strdup(dadosBinarioCru);

  // Utilizado para ler os Bytes dentro da array.
  char *conjuntoDeOito = strtok(dadosBinarioCruDup, " ");
  // Utilizado para navegar nos indexes da array para gravar os dados.
  int indexArray = 0;

  // Continua obtendo bytes até não haver mais.
  while (conjuntoDeOito != NULL) {
    // Adiciona 0B antes do valor em byte.
    strcpy(&dadosDivididosEmBytes[indexArray], "0B");
    indexArray += 2;

    // Copia o valor binario para o array.
    strcpy(&dadosDivididosEmBytes[indexArray], conjuntoDeOito);
    indexArray += strlen(conjuntoDeOito);

    // adiciona um espaço para separar os Byte para facilitar a navegação.
    dadosDivididosEmBytes[indexArray++] = ' ';

    // Obtém o próximo valor em byte e mantem o loop até não ter mais espaços.
    conjuntoDeOito = strtok(NULL, " ");
  }

  // Remove o último espaço e adiciona um caractere nulo.
  dadosDivididosEmBytes[indexArray - 1] = '\0';

  // Libera a memória duplicada.
  free(dadosBinarioCruDup);

  return dadosDivididosEmBytes;
}

int main(void) {
  // Primeiro formata os dados para a convenção 0B00000000 para facilidade da manipulação dos dados.
  char* textoFormatado = formatarTextoCriptografado(textoCriptografado);
  printf("%p\n\n", &textoCriptografado);
  printf("%p", &textoFormatado);
  // Libera a memória alocada.
  free(textoFormatado);

  return 0;
}
