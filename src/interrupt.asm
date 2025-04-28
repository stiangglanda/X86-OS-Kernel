[BITS 32]
[GLOBAL isr0]
[GLOBAL isr33]
[EXTERN isr_handler]

isr0:
    cli                     ; Disable interrupts
    push byte 0            ; Push a dummy error code
    push byte 0            ; Push the interrupt number
    
    pusha                  ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
    
    mov ax, ds            ; Save the data segment
    push eax
    
    mov ax, 0x10         ; Load the kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov eax, esp         ; Push esp as argument to handler
    push eax
    
    call isr_handler
    
    pop eax              ; Remove pushed stack pointer
    
    pop eax              ; Restore data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    popa                 ; Restore registers
    add esp, 8          ; Remove error code and interrupt number
    sti                 ; Re-enable interrupts
    iret                ; Return from interrupt

isr33:
    cli
    push byte 0     ; Push dummy error code
    push byte 33    ; Push interrupt number
    
    pusha          ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
    
    mov ax, ds     ; Save data segment
    push eax
    
    mov ax, 0x10   ; Load kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    call isr_handler
    
    pop eax        ; Restore data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    popa           ; Restore registers
    add esp, 8     ; Remove error code and interrupt number
    sti            ; Re-enable interrupts
    iret           ; Return from interrupt