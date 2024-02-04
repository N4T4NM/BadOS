[bits 16]
print_str:
    pusha

print_str_next:
    mov al, [bx] ; bx is our string pointer
    cmp al, 0
    je print_str_end

    ; Print the current character
    mov ah, 0x0E
    int 0x10

    add bx, 1 ; Move pointer to next character
    jmp print_str_next

print_str_end:
    popa
    ret

print_line:
    call print_str
    pusha

    mov ah, 0x0E ; We are printing
    
    mov al, 0x0A ; 0x0A is LF
    int 0x10

    mov al, 0x0D ; 0x0D is CR
    int 0x10

    popa
    ret

[bits 32]
VIDEO_MEMORY equ 0xB8000
WHITE_ON_BLACK equ 0x0F

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY

print_string_pm_loop:
    mov al, [ebx] ; [ebx] is the address of our character
    mov ah, WHITE_ON_BLACK

    cmp al, 0 ; check if end of string
    je print_string_pm_done

    mov [edx], ax ; store character + attribute in video memory
    add ebx, 1 ; next char
    add edx, 2 ; next video memory position

    jmp print_string_pm_loop

print_string_pm_done:
    popa
    ret