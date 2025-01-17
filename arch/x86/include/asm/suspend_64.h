/*
 * Copyright 2001-2003 Pavel Machek <pavel@suse.cz>
 * Based on code
 * Copyright 2001 Patrick Mochel <mochel@osdl.org>
 */
#ifndef _ASM_X86_SUSPEND_64_H
#define _ASM_X86_SUSPEND_64_H

#include <asm/desc.h>
#include <asm/i387.h>

/*
 * Image of the saved processor state, used by the low level ACPI suspend to
 * RAM code and by the low level hibernation code.
 *
 * If you modify it, check how it is used in arch/x86/kernel/acpi/wakeup_64.S
 * and make sure that __save/__restore_processor_state(), defined in
 * arch/x86/power/cpu.c, still work as required.
 *
 * Because the structure is packed, make sure to avoid unaligned members. For
 * optimisation purposes but also because tools like kmemleak only search for
 * pointers that are aligned.
 */
struct saved_context {
	struct pt_regs regs;
	u16 ds, es, fs, gs, ss;
	unsigned long gs_base, gs_kernel_base, fs_base;
	unsigned long cr0, cr2, cr3, cr4, cr8;
	u64 misc_enable;
	unsigned long efer;
	u16 gdt_pad; /* Unused */
	struct desc_ptr gdt_desc;
	u16 idt_pad;
	u16 idt_limit;
	unsigned long idt_base;
	u16 ldt;
	u16 tss;
	unsigned long tr;
	unsigned long safety;
	unsigned long return_address;
	bool misc_enable_saved;
} __attribute__((packed));

#define loaddebug(thread,register) \
	set_debugreg((thread)->debugreg##register, register)

/* routines for saving/restoring kernel state */
extern int acpi_save_state_mem(void);
extern char core_restore_code;
extern char restore_registers;

#endif /* _ASM_X86_SUSPEND_64_H */
