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
[EXTERN isr_handler]

; Common ISR stub that calls C handler
isr_common_stub:
    ; Save all registers and segments
    pusha
    mov ax, ds     ; Save the data segment
    push eax
    
    ; Load kernel data segment
    mov ax, 0x10   ; Load kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    ; Call C handler
    push esp        ; Push pointer to register state
    call isr_handler
    add esp, 4      ; Clean up pushed argument
    
    ; Restore segments and registers
    pop eax        ; Restore original data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    
    ; Clean up error code and interrupt number
    add esp, 8     ; Clean error code and interrupt number
    iret           ; Return from interrupt

; CPU Exception handlers
isr0:
    cli
    push byte 0     ; Push dummy error code
    push byte 0     ; Push interrupt number
    jmp isr_common_stub

isr1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub

isr2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_stub

isr3:
    cli
    push byte 0
    push byte 3
    jmp isr_common_stub

isr4:
    cli
    push byte 0
    push byte 4
    jmp isr_common_stub

isr5:
    cli
    push byte 0
    push byte 5
    jmp isr_common_stub

isr6:
    cli
    push byte 0
    push byte 6
    jmp isr_common_stub

isr7:
    cli
    push byte 0
    push byte 7
    jmp isr_common_stub

; Double Fault handler (needs special care)
isr8:
    cli                    ; Disable interrupts
    ; Note: CPU pushes error code automatically for #DF
    push byte 8           ; Push interrupt number
    jmp isr_common_stub

isr9:
    cli
    push byte 0
    push byte 9
    jmp isr_common_stub

isr10:
    cli
    ; Error code already pushed
    push byte 10
    jmp isr_common_stub

isr11:
    cli
    ; Error code already pushed
    push byte 11
    jmp isr_common_stub

isr12:
    cli
    ; Error code already pushed
    push byte 12
    jmp isr_common_stub

isr13:
    cli
    ; Error code already pushed
    push byte 13
    jmp isr_common_stub

isr14:
    cli
    ; Error code already pushed
    push byte 14
    jmp isr_common_stub

isr128:
    cli
    push byte 0
    push byte 128
    jmp isr_common_stub