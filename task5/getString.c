#include <stdio.h>
#include <stdlib.h>

int main() {
  char array[28] = {0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0xe5, 0x51, 0x55, 0x55, 0x55, 0x55, 0x00, 0x00};
  FILE *fp;

  fp = fopen("input.txt", "w");

  if (fp == NULL) {
    perror("Ошибка открытия файла");
    exit(1);
  }

  fprintf(fp, "%s", array);

  fclose(fp);

  printf("Успешно!\n");

  return 0;
}

