V = @

CC = gcc
CFLAGS = -Wall -I ./libs

LD = ld

BOOT = boot
MAKER = maker

OBJ = obj
OBJDUMP = objdump
OBJCOPY = objcopy

QEMU = qemu-system-i386

x2713.img: $(OBJ)/bootsector disk-image-maker
	$(V)./disk-image-maker $< > $@

$(OBJ)/bootsector: $(OBJ)/booting.o $(OBJ)/bootmain.o
	$(V)$(LD) -N -e start -Ttext 0x7C00 -o $@.out $^
	$(V)$(OBJDUMP) -S $@.out > $@.asm
	$(V)$(OBJCOPY) -S -O binary $@.out $@

disk-image-maker: $(MAKER)/disk-image-maker.c
	$(V)$(CC) $< -o $@

$(OBJ)/booting.o: $(BOOT)/booting.S
	$(V)mkdir -p $(@D)
	$(V)$(CC) -nostdinc $(CFLAGS) -c $< -o $@

$(OBJ)/bootmain.o: $(BOOT)/bootmain.c
	$(V)mkdir -p $(@D)
	$(V)$(CC) -nostdinc $(CFLAGS) -c $< -o $@

qemu: x2713.img
	$(V)$(QEMU) -no-reboot -hda $<

clean:
	$(V)rm -rf $(OBJ) x2713.img disk-image-maker
