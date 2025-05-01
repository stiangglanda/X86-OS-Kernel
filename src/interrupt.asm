[BITS 32]
[GLOBAL isr0]
[GLOBAL isr1]
[GLOBAL isr2]
[GLOBAL isr3]
[GLOBAL isr4]
[GLOBAL isr5]
[GLOBAL isr6]
[GLOBAL isr7]
[GLOBAL isr8]
[GLOBAL isr13]
[GLOBAL isr14]
[GLOBAL isr33]
[EXTERN isr_handler]

; ISR handlers
isr0:
    cli
    push dword 0    ; Push error code
    push dword 0    ; Push interrupt number
    jmp isr_common_stub

isr1:
    cli
    push dword 0
    push dword 1
    jmp isr_common_stub

isr2:
    cli
    push dword 0
    push dword 2
    jmp isr_common_stub

isr3:
    cli
    push dword 0
    push dword 3
    jmp isr_common_stub

isr4:
    cli
    push dword 0
    push dword 4
    jmp isr_common_stub

isr5:
    cli
    push dword 0
    push dword 5
    jmp isr_common_stub

isr6:
    cli
    push dword 0
    push dword 6
    jmp isr_common_stub

isr7:
    cli
    push dword 0
    push dword 7
    jmp isr_common_stub

isr8:
    cli
    ; Error code is pushed automatically
    push dword 8
    jmp isr_common_stub

isr13:
    cli
    ; Error code is pushed automatically
    push dword 13
    jmp isr_common_stub

isr14:
    cli
    ; Error code is pushed automatically
    push dword 14
    jmp isr_common_stub

isr33:
    cli
    push dword 0
    push dword 33
    jmp isr_common_stub

; Common ISR stub that calls the C handler
isr_common_stub:
    pusha           ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    mov ax, ds      ; Save data segment
    push eax

    mov ax, 0x10    ; Load kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp        ; Push pointer to stack structure as argument
    call isr_handler
    add esp, 4      ; Remove pushed stack pointer

    pop eax         ; Restore data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa            ; Restore registers
    add esp, 8      ; Remove error code and interrupt number
    sti             ; Re-enable interrupts
    iret            ; Return from interrupt