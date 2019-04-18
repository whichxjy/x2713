#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        exit(1);
    }

    char buffer[512];

    FILE* fp = fopen(argv[1], "rb");
    int size = fread(buffer, 1, 512, fp);
    if (size > 510) {
        exit(1);
    }
    fclose(fp);

    memset(buffer + size, 0, 510 - size);
    buffer[510] = 0x55;
    buffer[511] = 0xAA;
    fwrite(buffer, 1, 512, stdout);

    memset(buffer, 0, 512);
    for (int i = 0; i < 1023; i++) {
        fwrite(buffer, 1, 512, stdout);
    }
    
    return 0;
}
