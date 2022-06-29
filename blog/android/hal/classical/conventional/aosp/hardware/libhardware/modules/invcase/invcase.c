#define LOG_TAG "Invcase"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <utils/Log.h>
#include "hardware/invcase.h"

#define INVCASE_DEVICE_FILE "/dev/invcase"

static int dev_open(const struct hw_module_t *module, const char *name, struct hw_device_t **device);
static int dev_close(struct hw_device_t* device);
static ssize_t dev_write(char *buf, size_t count);
static ssize_t dev_read(char *buf, size_t count);

/* defined in hardware/hardware.h */
static struct hw_module_methods_t invcase_module_methods = {
	.open = dev_open,
};


/* every module must have HAL_MODULE_INFO_SYM */
struct invcase_module_t HAL_MODULE_INFO_SYM = {
	.common = {
		.tag = HARDWARE_MODULE_TAG,
		.version_major = 1,
		.version_minor = 0,
		.id = INVCASE_HARDWARE_MODULE_ID,
		.name = INVCASE_HARDWARE_MODULE_ID,
		.author = "vqtrong",
		.methods = &invcase_module_methods,
	},
};

struct invcase_device_t *invcase_dev;

static void __attribute__ ((constructor)) dev_loaded() {
	ALOGD("Conventional HAL Module: Loaded");
}

static void __attribute__ ((destructor )) dev_unloaded() {
	ALOGD("Conventional HAL Module: Unloaded");
}

static int dev_open(
    const struct hw_module_t *module, 
    const char *id, 
    struct hw_device_t **device
) {
	// use calloc to initialize memory with 0
	invcase_dev = (struct invcase_device_t *) calloc(1, sizeof(struct invcase_device_t));
	if(invcase_dev == NULL) {
		ALOGE("Conventional HAL Module: Unable to calloc, %s, ID: %s\n", strerror(errno), id);
		return -ENOMEM;
	}

	invcase_dev->common.tag = HARDWARE_MODULE_TAG;
	invcase_dev->common.version = 1;
	invcase_dev->common.module = (struct hw_module_t *)module;
	invcase_dev->common.close = dev_close;
	invcase_dev->write = dev_write;
	invcase_dev->read = dev_read;

	*device = (struct hw_device_t *)invcase_dev;
	ALOGD("Conventional HAL Module: Device %s is initialized\n", id);

	return 0;
}

static int dev_close(struct hw_device_t *device) {
	if(device) {
		free(device);
		ALOGD("Conventional HAL Module: free device\n");
	}
	return 0;
}

static ssize_t dev_write(char *buf, size_t count) {
	int fd;
	int ret;

	fd = open(INVCASE_DEVICE_FILE, O_WRONLY);
	if (fd < 0) {
		ALOGE("Conventional HAL Module: Unable to open %s to write\n", INVCASE_DEVICE_FILE);
		return fd;
	}

	ret = write(fd, buf, count);
	if (ret < 0) {
		ALOGE("Conventional HAL Module: Unable to write to %s\n", INVCASE_DEVICE_FILE);
		return ret;
	}

	ALOGD("Conventional HAL Module: invcase_write: buf= %s\n", buf);
	close(fd);
	return 0;
}

static ssize_t dev_read(char *buf, size_t count) {
	int fd;
	int ret;

	fd = open(INVCASE_DEVICE_FILE, O_RDONLY);
	if (fd < 0) {
		ALOGE("Conventional HAL Module: Unable to open %s to read\n", INVCASE_DEVICE_FILE);
		return fd;
	}

	ret = read(fd, buf, count);
	if (ret < 0) {
		ALOGE("Conventional HAL Module: Unable to read from %s\n", INVCASE_DEVICE_FILE);
		return ret;
	}

	ALOGD("Conventional HAL Module: invcase_read: buf= %s\n", buf);
	close(fd);
	return 0;
}
