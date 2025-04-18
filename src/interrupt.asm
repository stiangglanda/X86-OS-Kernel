[GLOBAL isr0]
[GLOBAL load_idt]

isr0:
    cli                     ; Disable interrupts
    push byte 0            ; Push a dummy error code
    push byte 0            ; Push the interrupt number
    jmp isr_common_stub    ; Go to our common handler

isr_common_stub:
    pusha                  ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
    
    mov ax, ds            ; Save the data segment
    push eax
    
    mov ax, 0x10         ; Load the kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    push esp            ; Push pointer to stack as argument to handler
    
    ; Call C handler
    extern isr_handler
    call isr_handler
    
    add esp, 4          ; Remove the pushed stack pointer
    
    pop eax              ; Reload the original data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    popa                 ; Pops edi,esi,ebp,esp,ebx,edx,ecx,eax
    add esp, 8          ; Cleans up the pushed error code and pushed ISR number
    sti                 ; Re-enable interrupts
    iret                ; Return from interrupt