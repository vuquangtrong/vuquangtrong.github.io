#define LOG_TAG "Invcase"
// #define INVCASE_USE_CONVENTIONAL_HAL

#include "jni.h"
#include <nativehelper/JNIHelp.h>
#include "android_runtime/AndroidRuntime.h"

#include <utils/misc.h>
#include <utils/Log.h>
#include <stdio.h>

#include <hardware/hardware.h>
#include <hardware/invcase.h>

namespace android
{
    static struct invcase_module_t *module = NULL;
    static struct invcase_device_t *device = NULL;

    static void jni_init (
        JNIEnv* /* env */,
        jobject /* clazz */
    ) {
        int err;

        err =  hw_get_module(
            INVCASE_HARDWARE_MODULE_ID, 
            (struct hw_module_t const**) &module
        );

        if (err != 0) {
            ALOGE("JNI: hw_get_module() failed: (%s)\n", strerror(-err));
            return;
        } else {
            ALOGD("JNI: hw_get_module() OK\n");
            if (module->common.methods->open(
                        (struct hw_module_t *) module, 
                        INVCASE_HARDWARE_MODULE_ID, 
                        (struct hw_device_t **) &device
                    ) != 0) {
                ALOGE("JNI: HAL failed to open! (%s)\n",strerror(-err));
                return;
            } else {
                ALOGD("JNI: hw_get_module() Open: OK\n");
            }
        }
    }

    static void jni_deinit (
        JNIEnv* /* env */,
        jobject /* clazz */
    ) {
        if (device) {
            free(device);
            ALOGD("JNI: Free device\n");
        }
    }

    static jstring jni_read (
        JNIEnv* env,
        jobject /* clazz */
    ) {
        char buff[INVCASE_BUFFER_MAX_SIZE];
        int err = -1;

        if(device) {
            ALOGD("JNI: device->read: %p\n", device->read);
            err = device->read(buff, INVCASE_BUFFER_MAX_SIZE);
        } else {
            ALOGE("JNI: Device is NULL\n");
        }

        if (err != 0) {
            ALOGE("JNI: Can not read from device\n");
        }
        ALOGD("JNI: jni_read: %s\n", buff);
        return env->NewStringUTF(buff);
    }

    static void jni_write (
        JNIEnv* env,
        jobject /* clazz */,
        jstring string
    ) {
        const char *buff = env->GetStringUTFChars(string, NULL);
        int length = env->GetStringLength(string);
        int err = -1;
        
        ALOGD("JNI: jni_write: %s length= %d\n", buff, length);

        if(device) {
            ALOGD("JNI: device->write: %p\n", device->write);
            err = device->write((char *)buff, length);
        } else {
            ALOGE("JNI: Device is NULL\n");
        }

        if (err != 0) {
            ALOGE("JNI: Can not write to device\n");
        }
    }

    static const JNINativeMethod method_table[] = {
        { "invcase_native_init", "()V", (void*)jni_init },
        { "invcase_native_deinit", "()V", (void*)jni_deinit },
        { "invcase_native_read", "()Ljava/lang/String;", (void*)jni_read },
        { "invcase_native_write", "(Ljava/lang/String;)V", (void*)jni_write },
    };

    int register_android_server_InvcaseService(JNIEnv *env) {
        ALOGD("JNI: register_android_server_InvcaseService\n");
        return jniRegisterNativeMethods(
                env, 
                "com/android/server/invcase/InvcaseService",
                method_table, 
                NELEM(method_table)
            );
    }
}
