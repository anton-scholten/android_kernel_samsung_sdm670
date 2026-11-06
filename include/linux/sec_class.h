/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef __SEC_CLASS_H__
#define __SEC_CLASS_H__

struct device;

#if IS_ENABLED(CONFIG_DRV_SAMSUNG)
extern struct device *sec_dev_get_by_name(const char *name);
extern void sec_device_destroy(dev_t devt);
extern struct device *___sec_device_create(void *drvdata, const char *fmt);
#define sec_device_create(__drvdata, __fmt)				\
	___sec_device_create(__drvdata, __fmt)
#else
static inline struct device *sec_dev_get_by_name(const char *name) { return NULL; }
static inline void sec_device_destroy(dev_t devt) {}
#define sec_device_create(...)	(NULL)
#endif

#endif /* __SEC_CLASS_H__ */
