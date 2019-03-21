C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)

OBJ = ${C_SOURCES:.c=.o}

CC = C:/MinGW/bin/gcc.exe
GDB = C:/MinGW/bin/gdb.exe

CFLAGS = -g

os-image.bin: boot/bootsect.bin kernel.bin
	bash
	cat $< > os-image.bin

kernel.bin: boot/kernel_entry.o ${OBJ}
	ld -T NUL -o kernel.tmp -Ttext 0x1000 $^
	objcopy -O binary -j .text  kernel.tmp $@

kernel.elf: boot/kernel_entry.o ${OBJ}
	ld -T NUL -o kernel.tmp -Ttext 0x1000 $^

run: os-image.bin
	qemu-system-i386 -fda os-image.bin

debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin & ${GDB} -ex "target remove localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm *.bin *.o *.dis *.tmp -rf