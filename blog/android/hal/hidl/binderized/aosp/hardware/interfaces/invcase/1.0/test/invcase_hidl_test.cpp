#define LOG_TAG "Invcase"

#include <iostream>
#include <android/hardware/invcase/1.0/IInvcase.h>
#include <hidl/HidlTransportSupport.h>
#include <hidl/LegacySupport.h>
#include <utils/Log.h>
#include <android/hardware/invcase/1.0/default/Invcase.h>

using android::hardware::invcase::V1_0::IInvcase;
using android::hardware::hidl_string;
using android::sp;

void logd(std::string msg) {
    std::cout << msg << std::endl;
    ALOGD("%s", msg.c_str());
}

void loge(std::string msg) {
    std::cout << msg << std::endl;
    ALOGE("%s", msg.c_str());
}

int main(int /* argc */, char** /* argv */) {

    android::sp<IInvcase> invcase = IInvcase::getService();
    if (invcase == nullptr) {
        loge("Failed to get Invcase service");
        return -1;
    }

    logd("Got Invcase service");

    std::string msg = "Hello World!";
    logd("Send: " + msg);
    invcase->putChars(msg);

    invcase->getChars([&](hidl_string result) {
        logd("Receive: " + std::string(result));
    });

    return 0;
}
