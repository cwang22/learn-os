all: run

kernel.bin: kernel_entry.o kernel.o
		ld -T NUL -o kernel.tmp -Ttext 0x1000 $^
		objcopy -O binary -j .text  kernel.tmp $@

kernel_entry.o: kernel_entry.asm
		nasm $< -f elf -o $@

kernel.o: kernel.c
	gcc -ffreestanding -c $< -o $@

# Rule to disassemble the kernel - may be useful to debug
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

bootsect.bin: bootsect.asm
	nasm $< -f bin -o $@

os-image.bin: bootsect.bin kernel.bin
	cat $< > $@

run: os-image.bin
	qemu-system-i386 -fda $<

clean:
	rm *.bin *.o *.dis *.tmp