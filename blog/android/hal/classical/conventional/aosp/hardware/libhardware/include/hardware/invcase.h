#ifndef INVCASE_CONVENTIONAL_H
#define INVCASE_CONVENTIONAL_H

#include <sys/types.h>			// size_t, ssize_t
#include <hardware/hardware.h>	// hw_module_t, hw_device_t

/* Use this for C++ */
__BEGIN_DECLS

#define INVCASE_HARDWARE_MODULE_ID	"invcase" 	// must be the same as the header file
#define INVCASE_DEBUG				"invcase: "
#define INVCASE_BUFFER_MAX_SIZE     1024

struct invcase_module_t {
	struct hw_module_t common;
};

struct invcase_device_t {
	struct hw_device_t common;
	ssize_t (*write)(char *, size_t);
	ssize_t (*read)(char *, size_t);
};

__END_DECLS

#endif /* INVCASE_CONVENTIONAL_H */
