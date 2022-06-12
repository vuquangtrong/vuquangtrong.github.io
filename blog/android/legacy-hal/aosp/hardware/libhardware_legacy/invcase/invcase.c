#define LOG_TAG "Invcase"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <utils/Log.h>
#include "hardware_legacy/invcase.h"

#define INVCASE_DEVICE_FILE "/dev/invcase"

void __attribute__ ((constructor)) invcase_loaded() {
	ALOGD("Legacy HAL Module: Loaded");
}

void __attribute__ ((destructor )) invcase_unloaded() {
	ALOGD("Legacy HAL Module: Unloaded");
}

int invcase_write(char *buf, size_t count) {
	int fd;
	int ret;

	fd = open(INVCASE_DEVICE_FILE, O_WRONLY);
	if (fd < 0) {
		ALOGE("Unable to open %s to write\n", INVCASE_DEVICE_FILE);
		return fd;
	}

	ret = write(fd, buf, count);
	if (ret < 0) {
		ALOGE("Unable to write to %s\n", INVCASE_DEVICE_FILE);
		return ret;
	}

	ALOGD("invcase_write: buf= %s\n", buf);
	close(fd);
	return 0;
}

int invcase_read(char *buf, size_t count) {
	int fd;
	int ret;

	fd = open(INVCASE_DEVICE_FILE, O_RDONLY);
	if (fd < 0) {
		ALOGE("Unable to open %s to read\n", INVCASE_DEVICE_FILE);
		return fd;
	}

	ret = read(fd, buf, count);
	if (ret < 0) {
		ALOGE("Unable to read from %s\n", INVCASE_DEVICE_FILE);
		return ret;
	}

	ALOGD("invcase_read: buf= %s\n", buf);
	close(fd);
	return 0;
}
