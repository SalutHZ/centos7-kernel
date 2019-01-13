/*
 * X86 specific ACPICA environments and implementation
 *
 * Copyright (C) 2014, Intel Corporation
 *   Author: Lv Zheng <lv.zheng@intel.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _ASM_X86_ACENV_H
#define _ASM_X86_ACENV_H

#include <asm/special_insns.h>

#define COMPILER_DEPENDENT_INT64   long long
#define COMPILER_DEPENDENT_UINT64  unsigned long long

/*
 * Calling conventions:
 *
 * ACPI_SYSTEM_XFACE        - Interfaces to host OS (handlers, threads)
 * ACPI_EXTERNAL_XFACE      - External ACPI interfaces
 * ACPI_INTERNAL_XFACE      - Internal ACPI interfaces
 * ACPI_INTERNAL_VAR_XFACE  - Internal variable-parameter list interfaces
 */
#define ACPI_SYSTEM_XFACE
#define ACPI_EXTERNAL_XFACE
#define ACPI_INTERNAL_XFACE
#define ACPI_INTERNAL_VAR_XFACE

/* Asm macros */

#define ACPI_FLUSH_CPU_CACHE()	wbinvd()

int __acpi_acquire_global_lock(unsigned int *lock);
int __acpi_release_global_lock(unsigned int *lock);

#define ACPI_ACQUIRE_GLOBAL_LOCK(facs, Acq) \
	((Acq) = __acpi_acquire_global_lock(&facs->global_lock))

#define ACPI_RELEASE_GLOBAL_LOCK(facs, Acq) \
	((Acq) = __acpi_release_global_lock(&facs->global_lock))

/*
 * Math helper asm macros
 */
#define ACPI_DIV_64_BY_32(n_hi, n_lo, d32, q32, r32) \
	asm("divl %2;"				     \
	    : "=a"(q32), "=d"(r32)		     \
	    : "r"(d32),				     \
	     "0"(n_lo), "1"(n_hi))

#define ACPI_SHIFT_RIGHT_64(n_hi, n_lo) \
	asm("shrl   $1,%2	;"	\
	    "rcrl   $1,%3;"		\
	    : "=r"(n_hi), "=r"(n_lo)	\
	    : "0"(n_hi), "1"(n_lo))

#endif /* _ASM_X86_ACENV_H */
