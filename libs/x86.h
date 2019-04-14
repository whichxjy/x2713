#ifndef __X86_H__
#define __X86_H__

#include <types.h>

/* References:
 * 
 * https://wiki.osdev.org/Inline_Assembly
 * 
 * https://wiki.osdev.org/Inline_Assembly/Examples
 * 
 */

//static inline void outb
static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a" (val), "d" (port));
}

#endif /* !__X86_H__ */
