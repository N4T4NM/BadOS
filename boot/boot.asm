[org 0x7C00]
KERNEL_OFFSET equ 0x1000
    mov [BOOT_DRIVE], dl
    mov bp, 0x9000
    mov sp, bp

    call load_kernel

    mov bx, MSG_READY
    call print_line

    ; This switches the VGA mode
    ; The resolution is 640x480
    ; Each bits is a pixel
    ; The address of the video memory is 0xA0000
    mov ax, 0x12
    int 0x10

    call switch_to_pm
    jmp $

%include "print_funcs.asm"
%include "disk.asm"
%include "gdt.asm"
%include "switch_32.asm"

[bits 16]
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print_line

    mov bx, KERNEL_OFFSET
    mov dh, 12
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]
BEGIN_PM:
    mov ebx, MSG_READY
    call print_string_pm
    call KERNEL_OFFSET
    jmp $

BOOT_DRIVE db 0
MSG_LOAD_KERNEL db "Loading kernel...", 0
MSG_READY db "Ready.", 0

times 510 - ($-$$) db 0
dw 0xAA55