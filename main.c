#include <stdio.h>
#include <stdlib.h>
#include "msxclib.h"
#include "msxalib.h"

#define BUF_SZ (1024)

int scload(char* fn) {
  FILE* fp;
  static char buff[BUF_SZ];
  unsigned int vram = 0x0000;
  if ((fp = fopen(fn, "rb"))) {
    fread(buff, 7, 1, fp); /* skip header */
    int read;
    while ((read = fread(buff, sizeof(char), BUF_SZ, fp))) {
      ldirvm(vram, buff, read);
      vram += BUF_SZ;
    }
    fclose(fp);
    return 0;
  } else {
    return 1;
  }
}

int main( int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: scload <filename>\n");
    exit(0);
  } else {
    ginit();
    screen(8);
    int ret = scload(argv[1]);
    getchar();
    screen(0);
  }
  return 0;
}
