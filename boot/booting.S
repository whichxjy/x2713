.set PROT_MODE_CSEG,    0x8
.set PROT_MODE_DSEG,    0x10
.set CR0_PE_ON,         0x1

.globl start
start:
.code16
    cli
    cld

    xorw    %ax, %ax
    movw    %ax, %ds
    movw    %ax, %es
    movw    %ax, %ss

seta20.1:
    inb     $0x64, %al
    testb   $0x2, %al
    jnz     seta20.1

    movb    $0xd1, %al
    outb    %al, $0x64

seta20.2:
    inb     $0x64, %al
    testb   $0x2, %al
    jnz     seta20.2

    movb    $0xdf, %al
    outb    %al, $0x60

real_to_prot:
    lgdt    gdtdesc
    movl    %cr0, %eax
    orl     $CR0_PE_ON, %eax
    movl    %eax, %cr0

    ljmp    $PROT_MODE_CSEG, $protcseg

.code32
protcseg:
    movw    $PROT_MODE_DSEG, %ax
    movw    %ax, %ds
    movw    %ax, %es
    movw    %ax, %fs
    movw    %ax, %gs
    movw    %ax, %ss

    movl    $0x0, %ebp
    movl    $start, %esp
    call    bootmain

spinloop:
    jmp     spinloop

#define SEG_NULLASM                 \
        .word 0, 0;                 \
        .byte 0, 0, 0, 0

#define SEG_ASM(type, base, lim)                            \
        .word (((lim) >> 12) & 0xffff), ((base) & 0xffff);  \
        .byte (((base) >> 16) & 0xff), (0x90 | (type)),     \
        (0xC0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)

#define STA_X   0x8
#define STA_W   0x2
#define STA_R   0x2

.p2align 2
gdt:
    SEG_NULLASM
    SEG_ASM(STA_X | STA_R, 0x0, 0xffffffff)
    SEG_ASM(STA_W, 0x0, 0xffffffff)

gdtdesc:
    .word   0x17
    .long   gdt
