/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Logging helpers and feature bits shared by Samsung input drivers.
 * Samsung carries these in uapi/linux/input.h; keep them kernel-only.
 */
#ifndef _SEC_INPUT_H_
#define _SEC_INPUT_H_

#include <linux/device.h>

/* /sys/class/sec/tsp/support_feature bits, shared with the framework */
#define INPUT_FEATURE_ENABLE_SETTINGS_AOT		(1 << 0)
#define INPUT_FEATURE_ENABLE_PRESSURE			(1 << 1)
#define INPUT_FEATURE_ENABLE_SYNC_RR120			(1 << 2)
#define INPUT_FEATURE_ENABLE_VRR			(1 << 3)
#define INPUT_FEATURE_ENABLE_SYSINPUT_ENABLED		(1 << 5)
#define INPUT_FEATURE_SUPPORT_OPEN_SHORT_TEST		(1 << 8)
#define INPUT_FEATURE_SUPPORT_MIS_CALIBRATION_TEST	(1 << 9)
#define INPUT_FEATURE_ENABLE_MULTI_CALIBRATION		(1 << 10)

#define SECLOG			"[sec_input]"
#define INPUT_LOG_BUF_SIZE	512

#define input_dbg(mode, dev, fmt, ...)	dev_dbg(dev, SECLOG fmt, ## __VA_ARGS__)
#define input_info(mode, dev, fmt, ...)	dev_info(dev, SECLOG fmt, ## __VA_ARGS__)
#define input_err(mode, dev, fmt, ...)	dev_err(dev, SECLOG fmt, ## __VA_ARGS__)
#define input_raw_info(mode, dev, fmt, ...) \
	input_info(mode, dev, fmt, ## __VA_ARGS__)
#define input_log_fix()			do { } while (0)
#define input_raw_data_clear()		do { } while (0)

static inline void sec_debug_tsp_command_history(char *buf) {}

#endif /* _SEC_INPUT_H_ */
