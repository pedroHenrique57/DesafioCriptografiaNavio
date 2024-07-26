#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Input do código a ser descriptografado.
// Dado salvo em memória pois foi feito para descriptografar um código específico,
// mas se informar mais binários com o mesmo padrão de cripto, irá funcionar igualmente.
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

// Pega os binários com espaços e converte para se adequar a convenção 0B00000000 para facilidade da manipulação dos dados.
void conversaoTextoParaBinario(char *dadosBinarioCru) {
  // Calcula o tamanho exato de alocação de memória para não haver alocação de memória desnecessária.
  // O +4 é contituido por: +3 espaços para contabilizar a não existencia de um ' ' (2 espaços para o 0B e 1 para o ' ') no ultimo valor+ 1 espaço para o caracter Nulo '\0'.
  char dadosDivididosEmConjuntosDeBits[strlen(textoCriptografado) + calculaEspacos(dadosBinarioCru) * 2 + 4];
  const char *conjuntoDeOito = strtok(dadosBinarioCru, " ");
  int tamanhoArray = 0;

  // Continua obtendo tokens até não haver mais
  while (conjuntoDeOito != NULL) {
    //Adiciona 0B antes do valor em binario.
    strcpy(&dadosDivididosEmConjuntosDeBits[tamanhoArray], "0B");
    // avança o contador de index da array para não sobrepor o dado já existente
    tamanhoArray += 2;

    // Copia o valor binario para o array
    strncpy(&dadosDivididosEmConjuntosDeBits[tamanhoArray], conjuntoDeOito, strlen(conjuntoDeOito));
    // avança o contador de index da array para não sobrepor o dado já existente
    tamanhoArray += strlen(conjuntoDeOito);

    // adiciona um espaço para separar os Byte para facilitar a navegação.
    dadosDivididosEmConjuntosDeBits[tamanhoArray++] = ' ';

    // Obtém o próximo valor binario e mantem o loop até não ter mais espaços
    conjuntoDeOito = strtok(NULL, " ");
  }

  // Certifica de que a string finaliza com um caractere nulo
  dadosDivididosEmConjuntosDeBits[tamanhoArray++] = '\0';

  // Imprime os dados divididos
  printf("Dados Divididos:\n%s\n", dadosDivididosEmConjuntosDeBits);
  system("pause");
}

int main(void) {
  // Primeiro formata os dados para a convenção 0B00000000 para facilidade da manipulação dos dados.
  conversaoTextoParaBinario(textoCriptografado);

  return 0;
}
