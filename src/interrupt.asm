; filepath: /home/stiangglanda/dev/X86-OS-Kernel/src/interrupt.asm
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
[GLOBAL isr9]
[GLOBAL isr10]
[GLOBAL isr11]
[GLOBAL isr12]
[GLOBAL isr13]
[GLOBAL isr14]
[GLOBAL isr128]
[GLOBAL irq1_handler]

[EXTERN isr_handler]
[EXTERN keyboard_handler] 

; Common ISR stub that calls C handler
isr_common_stub:
    ; Save registers
    pusha
    
    ; Save data segments
    mov ax, ds
    push eax
    
    ; Load kernel data segment
    mov ax, 0x10    ; Kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    ; Push pointer to stack structure as argument to handler
    push esp
    
    ; Call C handler
    call isr_handler
    
    ; Remove pushed stack pointer
    add esp, 4
    
    ; Restore data segments
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    ; Restore registers
    popa
    
    ; Cleanup error code and interrupt number
    add esp, 8
    iret

irq1_handler:
    cli          ; Disable interrupts
    pusha        ; Save all general purpose registers

    mov ax, ds   ; Save the data segment
    push eax

    mov ax, 0x10 ; Load kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call keyboard_handler ; Call our C keyboard code

    pop eax      ; Restore data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa         ; Restore all registers
    sti          ; Re-enable interrupts
    iret         ; Return from interrupt

; Divide by zero handler
isr0:
    cli
    push dword 0    ; Push error code (zero)
    push dword 0    ; Push interrupt number (zero)
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

; Double Fault handler
isr8:
    cli            ; Disable interrupts
    push dword 0   ; Push error code (even though CPU pushes one)
    push dword 8   ; Push interrupt number
    jmp isr_common_stub

isr9:
    cli
    push dword 0
    push dword 9
    jmp isr_common_stub

isr10:
    cli
    ; Error code already pushed
    push dword 10
    jmp isr_common_stub

isr11:
    cli
    ; Error code already pushed
    push dword 11
    jmp isr_common_stub

isr12:
    cli
    ; Error code already pushed
    push dword 12
    jmp isr_common_stub

isr13:
    cli
    ; Error code already pushed
    push dword 13
    jmp isr_common_stub

isr14:
    cli
    ; Error code already pushed
    push dword 14
    jmp isr_common_stub

isr128:
    cli
    push dword 0
    push dword 128
    jmp isr_common_stub