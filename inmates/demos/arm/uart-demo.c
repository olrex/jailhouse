/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) ARM Limited, 2014
 *
 * Authors:
 *  Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include <inmates/inmate.h>

/*
 * To ease the debugging, we can send a spurious hypercall, which should return
 * -ENOSYS, but appear in the hypervisor stats for this cell.
 */
static void heartbeat(void)
{
	asm volatile (
	".arch_extension virt\n"
	"mov	r0, %0\n"
	"hvc	#0\n"
	: : "r" (0xbea7) : "r0");
}

void inmate_main(void)
{
	unsigned int i = 0, j;
	/*
	 * The cell config can set up a mapping to access UARTx instead of UART0
	 */
	while(++i) {
		for (j = 0; j < 100000000; j++);
		printk("Hello %d from cell!\n", i);
		heartbeat();
	}

	/* lr should be 0, so a return will go back to the reset vector */
}
