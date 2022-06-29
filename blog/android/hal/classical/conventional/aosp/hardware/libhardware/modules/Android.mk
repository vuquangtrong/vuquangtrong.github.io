hardware_modules := \
    camera \
    gralloc \
    sensors \
    invcase
include $(call all-named-subdir-makefiles,$(hardware_modules))
