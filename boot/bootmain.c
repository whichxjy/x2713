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
    char* VIDMEM = (char*)0xB8000;

    VIDMEM[0] = '4';
    VIDMEM[1] = 0x09;
    VIDMEM[2] = '2';
    VIDMEM[3] = 0x09;

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
