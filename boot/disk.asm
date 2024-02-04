disk_load:
    pusha
    push dx

    mov ah, 0x02 ; Read mode
    mov al, dh ; Number of sectors
    mov cl, 0x02 ; Sector 0x02 is the first available sector

    mov ch, 0x00 ; Cylinder
    mov dh, 0x00 ; Head number

    int 0x13 ; INTERRUPT
    jc disk_err ; Error is stored in carry bit

    pop dx
    cmp al, dh
    jne sector_err
    popa

    ret

disk_err:
    mov bx, MSG_DISK_ERR
    call print_line

    mov dh, ah
    jmp disk_loop

sector_err:
    mov bx, MSG_SECTOR_ERR
    call print_str

disk_loop:
    jmp $

MSG_DISK_ERR db "Could not read disk", 0
MSG_SECTOR_ERR db "Could not read the sectors", 0