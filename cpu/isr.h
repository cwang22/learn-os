#ifndef ISR_H
#define ISR_H

#include "types.h"

/* ISRs reserved for CPU exceptions */
extern void isr0() asm("isr0");
extern void isr1() asm("isr1");
extern void isr2() asm("isr2");
extern void isr3() asm("isr3");
extern void isr4() asm("isr4");
extern void isr5() asm("isr5");
extern void isr6() asm("isr6");
extern void isr7() asm("isr7");
extern void isr8() asm("isr8");
extern void isr9() asm("isr9");
extern void isr10() asm("isr10");
extern void isr11() asm("isr11");
extern void isr12() asm("isr12");
extern void isr13() asm("isr13");
extern void isr14() asm("isr14");
extern void isr15() asm("isr15");
extern void isr16() asm("isr16");
extern void isr17() asm("isr17");
extern void isr18() asm("isr18");
extern void isr19() asm("isr19");
extern void isr20() asm("isr20");
extern void isr21() asm("isr21");
extern void isr22() asm("isr22");
extern void isr23() asm("isr23");
extern void isr24() asm("isr24");
extern void isr25() asm("isr25");
extern void isr26() asm("isr26");
extern void isr27() asm("isr27");
extern void isr28() asm("isr28");
extern void isr29() asm("isr29");
extern void isr30() asm("isr30");
extern void isr31() asm("isr31");

extern void irq0() asm("irq0");
extern void irq1() asm("irq1");
extern void irq2() asm("irq2");
extern void irq3() asm("irq3");
extern void irq4() asm("irq4");
extern void irq5() asm("irq5");
extern void irq6() asm("irq6");
extern void irq7() asm("irq7");
extern void irq8() asm("irq8");
extern void irq9() asm("irq9");
extern void irq10() asm("irq10");
extern void irq11() asm("irq11");
extern void irq12() asm("irq12");
extern void irq13() asm("irq13");
extern void irq14() asm("irq14");
extern void irq15() asm("irq15");

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

/* Struct which aggregates many registers */
typedef struct
{
  u32 ds;                                     /* Data segment selector */
  u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
  u32 int_no, err_code;                       /* Interrupt number and error code (if applicable) */
  u32 eip, cs, eflags, useresp, ss;           /* Pushed by the processor automatically */
} registers_t;

void isr_install();
void isr_handler(registers_t r);

typedef void (*isr_t)(registers_t);
void register_interrupt_handler(u8 n, isr_t handler);

#endif