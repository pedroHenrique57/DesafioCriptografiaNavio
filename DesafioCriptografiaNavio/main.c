#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Input do código a ser descriptografado.
char textoCriptografado[] =
    "10010110 11110111 01010110 00000001 00010111 00100110 01010111 00000001 00010111 01110110 01010111 00110110 "
    "11110111 11010111 01010111 00000011";

// Criação dos protótipos
char *tradutorCriptografia(const char *textoCriptografado);

char *inverteUltimosDoisBit(const char *charByteToken);

char *trocaMetadeBit(const char *charByteTokenInvertido);

char binarioParaChar(const char *binario);

int calculaEspacos(const char *texto);

// Implementação dos metodos

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

// Inverte os valores binários dos ultimos dois bits
char *inverteUltimosDoisBit(const char *charByteToken) {
  char *charByte = malloc(9 * sizeof(char));
  for (int i = 0; i < 8; i++) {
    if (i == 6 || i == 7) {
      strcpy(&charByte[i], ((charByteToken[i] == '1') ? "0" : "1"));
    } else {
      strcpy(&charByte[i], ((charByteToken[i] == '1') ? "1" : "0"));
    }
  }
  // Adiciona null para terminar a string
  charByte[8] = '\0';
  return charByte;
}

// Inverte os 4 primeiros bits com os 4 ultimos
char *trocaMetadeBit(const char *charByteTokenInvertido) {
  // Aloca a memória para o armazenamento dos bits
  char *byteTrocado = malloc(9 * sizeof(char));

  // Pega os ultimos 4 e os 4 primeiros e salva dentro das variáveis
  for (int i = 0; i < 4; i++) {
    byteTrocado[i] = charByteTokenInvertido[i + 4];
    byteTrocado[i + 4] = charByteTokenInvertido[i];
  }
  // Termina a string com um caractere nulo
  byteTrocado[8] = '\0';

  return byteTrocado;
}

// Recebe um valor em byte e o converte pra ASCII Code
char binarioParaChar(const char *byte) {
  int asciiCode = 0;
  for (int i = 0; i < 8; i++) {
    asciiCode = asciiCode * 2 + (byte[i] - '0');
  }
  return asciiCode;
}

// Responsável por realizar a descriptografia.
char *tradutorCriptografia(const char *textoCriptografado) {
  // Calcula o tamanho exato de alocação de memória Baseado na quantidade de Bytes.
  char *textoDescriptografado = malloc((calculaEspacos(textoCriptografado) + 1) * sizeof(char));

  // Duplica a string para preservar a original ao usar strtok.
  char *textoCriptografadoDup = strdup(textoCriptografado);

  // Utilizado para ler o primeiro Byte dentro da array.
  char *charByteToken = strtok(textoCriptografadoDup, " ");

  // Utilizado para navegar nos indexes da array para gravar os dados.
  int indexTextoDescriptografado = 0;

  // Continua obtendo charBytesToken até não haver mais.
  while (charByteToken != NULL) {
    // Inverte os dois ultimos bits
    char *byteInvertido = inverteUltimosDoisBit(charByteToken);

    // Inverte os 4 primeiros bits com os 4 ultimos
    char *byteTrocado = trocaMetadeBit(byteInvertido);
    // Transforma o valor em binário para caractere e salva na variável.
    textoDescriptografado[indexTextoDescriptografado++] = binarioParaChar(byteTrocado);

    // Obtém o próximo valor em charByteToken de onde parou e mantem o loop até não ter mais espaços.
    charByteToken = strtok(NULL, " ");

    //Libera os espaços alocados para próxima iteração
    free(byteTrocado);
    free(byteInvertido);
  }

  // Termina a string com um caractere nulo.
  textoDescriptografado[indexTextoDescriptografado++] = '\0';

  // Libera a memória duplicada.
  free(textoCriptografadoDup);

  return textoDescriptografado;
}

int main(void) {
  //Executa a descriptografia
  char *textoDescriptografado = tradutorCriptografia(textoCriptografado);

  //Exibe as variáveis no terminal
  printf("Texto Criptografado: %s\n\n", textoCriptografado);
  printf("Texto Descriptografado: %s\n\n", textoDescriptografado);

  // Libera a memória alocada.
  free(textoDescriptografado);

  // Pausa o terminal para leitura de dados.
  system("pause");
  return 0;
}
