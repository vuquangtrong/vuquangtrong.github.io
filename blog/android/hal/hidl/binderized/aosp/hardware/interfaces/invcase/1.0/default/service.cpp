#define LOG_TAG "Invcase"

#include <iostream>
#include <android/hardware/invcase/1.0/IInvcase.h>
#include <hidl/HidlTransportSupport.h>
#include <hidl/LegacySupport.h>
#include <utils/Log.h>
#include "Invcase.h"

using android::hardware::invcase::V1_0::IInvcase;
using android::hardware::invcase::V1_0::implementation::Invcase;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
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
    configureRpcThreadpool(1, true /*callerWillJoin*/);

    android::sp<IInvcase> invcase = new Invcase();
    if (invcase != nullptr) {
        if (invcase->registerAsService() != ::android::OK) {
            loge("Failed to register IInvcase service");
            return -1;
        }
    } else {
        loge("Failed to get IInvcase instance");
        return -1;
    }

    logd("IInvcase service starts to join service pool");
    joinRpcThreadpool();
    return 1;  // joinRpcThreadpool shouldn't exit
}
