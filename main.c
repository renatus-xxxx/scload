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

int edge_esc() {
  static int old_s = 0;
  int s = ((snsmat(7) & 0x04) == 0);
  int r = (s && !old_s);
  old_s = s;
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
    while(1){
      if (edge_esc()) {
        break; // ESC
      }
    }
    screen(0);
  }
  return 0;
}
