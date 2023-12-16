#ifndef __MSXALIB_H__
#define __MSXALIB_H__

/* From "Introduction to MSX-C" */
/* ISBN: 4-7561-0057-0          */
struct regs {
    char     f;
    char     a;
    unsigned bc;
    unsigned de;
    unsigned hl;
};

void ginit();
void calbio(unsigned ad, struct regs *rg);
void ldirvm(unsigned int ds, char *sr, unsigned int ln);

#endif /* __MSXALIB_H__ */