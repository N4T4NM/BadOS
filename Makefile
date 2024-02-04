C_SOURCES = $(wildcard src/*.c)
HEADERS = $(wildcard src/*.h)
OBJ_FILES = $(patsubst %.c,link/%.o,$(filter-out src/BadKernel.c,$(C_SOURCES)) link/interrupt.o)
C_FLAGS = -g -m32 -ffreestanding -fno-PIC -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror

bin/image.bin: bin/boot.bin bin/kernel.bin
	cat $^ > $@

bin/kernel.bin: link/kernel_entry.o link/kernel.o $(OBJ_FILES)
	ld -m elf_i386 -o $@ -Ttext 0x1000 $(addprefix link/,$(notdir $^)) --oformat binary
	
bin/%.bin: boot/%.asm
	nasm $< -I boot -f bin -o $@

link/%.o: boot/%.asm
	nasm $< -I boot -f elf -o $@

link/kernel.o: src/BadKernel.c
	gcc -g -m32 -ffreestanding -fno-PIC -I include -c $< -o $@

link/%.o: %.c $(HEADERS)
	gcc -g -m32 -ffreestanding -fno-PIC -I include -c $< -o link/$(notdir $@)

bin/kernel.elf: link/kernel_entry.o link/kernel.o $(OBJ_FILES)
	ld -m elf_i386 -o $@ -Ttext 0x1000 $(addprefix link/,$(notdir $^))

setup: resources/public/encoder.py resources/private/source.mp4
	python3 $(word 1,$^) $(word 2,$^) resources/private/video.bin

py-preview: resources/public/preview.py resources/private/video.bin
	python3 $(word 1,$^) $(word 2,$^)

run: bin/image.bin
	qemu-system-i386 -fda $<

debug: bin/image.bin bin/kernel.elf
	qemu-system-i386 -s -fda $(word 1,$^) &
	gdb -ex "target remote localhost:1234" -ex "symbol-file $(word 2,$^)"

play: bin/image.bin bin/kernel.elf resources/private/video.bin
	qemu-system-i386 -s -fda $(word 1,$^) &
	gdb -ex "target remote localhost:1234" -ex "symbol-file $(word 2,$^)" -ex "restore $(word 3,$^) binary 0xFFF000"