// SPDX-License-Identifier: GPL-2.0
/*
 * Mirrors the kernel log into the bootloader-provided sec_log buffer,
 * which survives resets and upload mode, and exposes the previous boot's
 * log as /proc/last_kmsg.
 *
 * COPYRIGHT(C) 2010-2019 Samsung Electronics Co., Ltd. All Right Reserved.
 */

#define pr_fmt(fmt)     KBUILD_MODNAME ":%s() " fmt, __func__

#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/log2.h>
#include <linux/proc_fs.h>
#include <linux/samsung/sec_log_buf.h>
#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/vmalloc.h>

/* Example usage: sec_log=0x200000@0xA1600000 */

static struct sec_log_buf __iomem *s_log_buf;

static phys_addr_t sec_log_paddr;
static size_t sec_log_size;
static size_t sec_log_buf_size __read_mostly;
static bool sec_log_buf_init_done __read_mostly;

static int __init sec_log_setup(char *str)
{
	unsigned long long base;

	sec_log_size = (size_t)memparse(str, &str);

	if (!sec_log_size ||
	    (sec_log_size != roundup_pow_of_two(sec_log_size)) ||
	    (*str != '@'))
		goto err;

	if (kstrtoull(++str, 16, &base))
		goto err;

	sec_log_paddr = base;
	sec_log_buf_size = sec_log_size - offsetof(struct sec_log_buf, buf);

	return 0;

err:
	sec_log_paddr = 0;
	sec_log_size = 0;
	sec_log_buf_size = 0;

	return 0;
}
early_param("sec_log", sec_log_setup);

static char *last_log_buf;
static size_t last_log_buf_size;

static int __init sec_last_kmsg_prepare(void)
{
	unsigned int head;

	last_log_buf = vmalloc(sec_log_buf_size);
	if (!last_log_buf)
		return -ENOMEM;

	if (s_log_buf->idx > sec_log_buf_size) {
		head = s_log_buf->idx % sec_log_buf_size;
		memcpy_fromio(last_log_buf, &s_log_buf->buf[head],
			      sec_log_buf_size - head);
		if (head)
			memcpy_fromio(&last_log_buf[sec_log_buf_size - head],
				      s_log_buf->buf, head);
		last_log_buf_size = sec_log_buf_size;
	} else {
		memcpy_fromio(last_log_buf, s_log_buf->buf, s_log_buf->idx);
		last_log_buf_size = s_log_buf->idx;
	}

	return 0;
}

static ssize_t sec_last_log_buf_read(struct file *file, char __user *buf,
				     size_t len, loff_t *offset)
{
	loff_t pos = *offset;
	ssize_t count;

	if (pos >= last_log_buf_size || !last_log_buf)
		return 0;

	count = min(len, (size_t)(last_log_buf_size - pos));
	if (copy_to_user(buf, last_log_buf + pos, count))
		return -EFAULT;

	*offset += count;

	return count;
}

static const struct file_operations last_log_buf_fops = {
	.owner	= THIS_MODULE,
	.read	= sec_last_log_buf_read,
};

static int __init sec_last_kmsg_init(void)
{
	struct proc_dir_entry *entry;
	int err;

	err = sec_last_kmsg_prepare();
	if (err)
		return err;

	entry = proc_create_data("last_kmsg", 0444, NULL,
				 &last_log_buf_fops, NULL);
	if (!entry)
		return -ENOMEM;

	proc_set_size(entry, last_log_buf_size);

	return 0;
}

void sec_log_buf_write(const char *s, unsigned int count)
{
	unsigned int f_len, s_len, remain_space;
	size_t idx;

	if (unlikely(!sec_log_buf_init_done))
		return;

	idx = s_log_buf->idx % sec_log_buf_size;
	remain_space = sec_log_buf_size - idx;
	f_len = min(count, remain_space);
	memcpy_toio(&s_log_buf->buf[idx], s, f_len);

	s_len = count - f_len;
	if (unlikely(s_len))
		memcpy_toio(s_log_buf->buf, &s[f_len], s_len);

	s_log_buf->idx += (uint32_t)count;
}

static int __init sec_log_buf_init(void)
{
	if (!sec_log_size) {
		pr_info("no sec_log= on the cmdline\n");
		return 0;
	}

	s_log_buf = ioremap_wc(sec_log_paddr, sec_log_size);
	if (!s_log_buf) {
		pr_err("failed to ioremap log region\n");
		return -ENOMEM;
	}

	pr_info("sec_log at %pa (%zu bytes)\n", &sec_log_paddr, sec_log_size);

	if (s_log_buf->magic != SEC_LOG_MAGIC) {
		pr_warn("sec_log_magic is not valid: 0x%x\n", s_log_buf->magic);
		s_log_buf->magic = SEC_LOG_MAGIC;
		s_log_buf->idx = 0;
	}

	if (sec_last_kmsg_init())
		pr_warn("failed to create /proc/last_kmsg\n");

	sec_log_buf_pull_early_buffer(&sec_log_buf_init_done);

	return 0;
}
core_initcall_sync(sec_log_buf_init);
