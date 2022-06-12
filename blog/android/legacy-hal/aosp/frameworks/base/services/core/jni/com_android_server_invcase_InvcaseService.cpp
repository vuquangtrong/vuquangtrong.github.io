#define LOG_TAG "Invcase"

#include "jni.h"
#include <nativehelper/JNIHelp.h>
#include "android_runtime/AndroidRuntime.h"

#include <utils/misc.h>
#include <utils/Log.h>
#include <stdio.h>

#include <hardware_legacy/invcase.h>

namespace android
{
    static void jni_init (
        JNIEnv* /* env */,
        jobject /* clazz */
    ) {
    }

    static void jni_deinit (
        JNIEnv* /* env */,
        jobject /* clazz */
    ) {
    }

    static jstring jni_read (
        JNIEnv* env,
        jobject /* clazz */
    ) {
        char buff[INVCASE_BUFFER_MAX_SIZE];
        int err = -1;

        ALOGD("JNI: invcase_read: %p\n", invcase_read);
        err = invcase_read(buff, INVCASE_BUFFER_MAX_SIZE);

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

        ALOGD("JNI: invcase_write: %p\n", invcase_write);
        err = invcase_write((char *)buff, length);

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
