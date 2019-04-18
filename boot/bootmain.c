#include "x86.h"

#define SCREEN_WIDTH 256

void bootmain() {
    /* References:
     *
     * https://wiki.osdev.org/Printing_To_Screen
     * 
     * https://en.wikipedia.org/wiki/VGA-compatible_text_mode
     * 
     * http://www.brokenthorn.com/Resources/OSDev10.html
     *
     */

    // Video memory
    volatile char* VIDMEM = (volatile char*)0xB8000;

    *(VIDMEM) = '4';
    ++VIDMEM;
    *(VIDMEM) = 0x09;
    ++VIDMEM;
    *(VIDMEM) = '2';
    ++VIDMEM;
    *(VIDMEM) = 0x09;
    ++VIDMEM;

    int i;
    for (i = 0; i < 2048; i++) {
        *(VIDMEM) = ' ';
        ++VIDMEM;
        *(VIDMEM) = 0x09;
        ++VIDMEM;
    }

    // Moving the cursor

    // Set high byte index to VGA register
    outb(0x03D4, 0x0E);
    outb(0x03D5, 0x02 / SCREEN_WIDTH);

    // Set low byte index to VGA register
    outb(0x03D4, 0x0F);
    outb(0x03D5, 0x02 % SCREEN_WIDTH);

    while (1) {
        // It was a long time before anyone spoke.
    }
}
