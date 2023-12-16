/* From "Introduction to MSX-C" */
/* ISBN: 4-7561-0057-0          */
#include <msxalib.h>

char rdport = 98;
char wrport = 99;

void ginit() {
#asm
GINIT_EXPTBL	equ	0fcc1h		;slot address of BIOS ROM
	ld	hl,6
	ld	a,(GINIT_EXPTBL)
	call	000ch
	ld	(_rdport),a
	ld	hl,7
	ld	a,(GINIT_EXPTBL)
	call	000ch
	ei
	ld	(_wrport),a
#endasm
}

void etc_func01() {

#asm
	jp	jmp_etc_func01
;--- SETADR ---
;low level routine for SETRD and SETWRT
;entry  HL..read/write address

ETC_FUNC01_ACPAGE	equ	0faf6h
ETC_FUNC01_EXBRSA	equ	0faf8h
ETC_FUNC01_SCRMOD	equ	0fcafh
SETADR:
	ld	c,a
	inc	c
	ld	a,(ETC_FUNC01_EXBRSA)
	or	a		;MSX1?
	jr	z,SETAD3	;Yes
	ld	a,(ETC_FUNC01_SCRMOD)
	cp	5
	jr	c,SETAD3
	ld	b,h
	cp	7		;extract the high address
	ld	a,(ETC_FUNC01_ACPAGE)
	jr	c,SETAD1
	sla	b
	rla
	jr	SETAD2
SETAD1:
	sla	b
SETAD2:
	sla	b
	rla
	di
	out	(c),a		;set data to be written
	ld	a,14+80h	;set it to register #14
	out	(c),a
SETAD3:
	di
	out	(c),l		;set the low address
	ld	a,h		;prepare to set the middle address
	and	3fh
	ret

;--- SETWRT ---
;sets up the VDP for write

SETWRT:
	ld	a,(_wrport)
	call	SETADR
	or	01000000b	;set the low address with wirte bit
	out	(c),a
	dec	c
	ei
	ret

;--- SETRD ---
;sets up the VDP for read

SETRD:
	ld	a,(_rdport)
	call	SETADR
	out	(c),a
	dec	c
	ei
	ret
jmp_etc_func01:

#endasmm
}

unsigned int ldirvm_param3;
void ldirvm(unsigned int ds, char *sr, unsigned int ln) {
#asm
	ld	hl,2
	add	hl,sp
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	inc	hl
	ld	(_ldirvm_param3),bc
	ld	e,(hl)
	inc	hl
	ld	d,(hl)
	inc	hl
	ld	c,(hl)
	inc	hl
	ld	b,(hl)
	ld	l,c
	ld	h,b
	ld	bc,(_ldirvm_param3)

ldirvm01:
	push	bc		;save length
	call	SETWRT
	ex	de,hl		;C..(_wrport)
	pop	de		;HL..pointer to souce DE..length
	ld	b,e		;set higher byte of length
	ld	a,e
	or	a
	ld	a,d		;set higher byte of length
	jr	z,LDIRV1
	inc	a
LDIRV1:
	outi
	jp	nz,LDIRV1
	dec	a
	jp	nz,LDIRV1
#endasm
}

void calbio(unsigned int address, struct regs *r) {
	
#asm

CALBIO_CALSLT	equ	001ch
CALBIO_EXPTBL	equ	0fcc1h		;slot address of BIOS ROM

    ld	hl,2
	add	hl,sp
	ld	e,(hl)	;second param to de
	inc	hl
	ld	d,(hl)
	inc	hl
	ld	c,(hl)	;first param to hl
	inc	hl
	ld	b,(hl)
	ld  l,c
	ld	h,b


CALBIO01:
	push	hl
	pop	ix
	push	de
	ex	de,hl
	ld	iy,0
	add	iy,sp
	di
	ld	sp,hl
	pop	af
	pop	bc
	pop	de
	pop	hl
	ei
	ld	sp,iy
	push	iy
	ld	iy,(CALBIO_EXPTBL-1)
	call	CALBIO_CALSLT
	pop	iy
	exx
	pop	hl
	ld	bc,8
	add	hl,bc
	di
	ld	sp,hl
	exx
	push	hl
	push	de
	push	bc
	push	af
	ei
	ld	sp,iy
	pop	af
#endasm
}