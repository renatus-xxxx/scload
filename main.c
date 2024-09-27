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
  }
  return 1;
}

int edge_key(int line, int bitmask, int* old) {
  int s = ((snsmat(line) & bitmask) == 0);
  int r = (s && !*old);
  *old = s;
  return r;
}

int main( int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: scload <filename>\n");
    exit(0);
  } else {
    ginit();
    screen(8);
    int ret = scload(argv[1]);
    int old_esc = 0, old_l = 0, old_r = 0;
    while(!edge_key(7, 0x04, &old_esc)){ // ESC
      if (edge_key(8, 0x80, &old_r)) {   //  ->
        scload("night.sc8");
      }
      if (edge_key(8, 0x10, &old_l)) {   // <-
        scload("flower.sc8");
      }
    }
    screen(0);
  }
  return 0;
}
