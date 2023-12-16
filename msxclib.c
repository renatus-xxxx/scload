/* From "Introduction to MSX-C" */
/* ISBN: 4-7561-0057-0          */

#include <msxclib.h>

void screen(int md){
  struct regs r;
  r.a = (char)md;
  calbio(0x005f, &r);
}
