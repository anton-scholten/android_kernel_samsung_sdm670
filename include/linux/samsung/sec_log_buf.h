/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __SEC_LOG_BUF_H__
#define __SEC_LOG_BUF_H__

#define SEC_LOG_MAGIC		0x4d474f4c	/* "LOGM" */

/* Layout shared with the bootloader (sec_log=SIZE@ADDR) */
struct sec_log_buf {
	uint32_t boot_cnt;
	uint32_t magic;
	uint32_t idx;
	char buf[];
};

#ifdef CONFIG_SEC_LOG_BUF
/* called from kernel/printk/printk.c */
void sec_log_buf_write(const char *s, unsigned int count);
void sec_log_buf_pull_early_buffer(bool *init_done);
#else
static inline void sec_log_buf_write(const char *s, unsigned int count) {}
#endif

#endif /* __SEC_LOG_BUF_H__ */
