/* From "Introduction to MSX-C" */
/* ISBN: 4-7561-0057-0          */

#include <msxclib.h>

void screen(int md){
  struct regs r;
  r.a = (char)md;
  calbio(0x005f, &r);
}
void color(int fg, int bg, int bd){
  struct regs r;
  *((char *)0xf3e9) = (char)fg;
  *((char *)0xf3ea) = (char)bg;
  *((char *)0xf3eb) = (char)bd;
  calbio(0x0062, &r);
}
char snsmat(int mt){
  struct regs r;
  r.a = (char)mt;
  calbio(0x0141, &r);
  return (r.a);
}