#define LOG_TAG "Invcase"

#include "jni.h"
#include <nativehelper/JNIHelp.h>
#include "android_runtime/AndroidRuntime.h"

#include <utils/misc.h>
#include <utils/Log.h>
#include <stdio.h>

#include <android/hardware/invcase/1.0/IInvcase.h>

using android::hardware::invcase::V1_0::IInvcase;
using android::hardware::hidl_string;

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
        sp<IInvcase> invcase = IInvcase::getService();

        if (invcase == nullptr) {
            ALOGE("JNI: Failed to get Invcase service\n");
            return env->NewStringUTF("");
        }

        std::string msg;

        invcase->getChars([&](hidl_string result) {
            msg = std::string(result);
        });

        const char* buff = msg.c_str();
        ALOGD("JNI: Receive: %s\n", buff);
        return env->NewStringUTF(buff);
    }

    static void jni_write (
        JNIEnv* env,
        jobject /* clazz */,
        jstring string
    ) {
        sp<IInvcase> invcase = IInvcase::getService();

        if (invcase == nullptr) {
            ALOGE("JNI: Failed to get Invcase service\n");
            return;
        }

        const char *buff = env->GetStringUTFChars(string, NULL);
        ALOGD("JNI: Send: %s\n", buff);
        
        invcase->putChars(std::string(buff));
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
