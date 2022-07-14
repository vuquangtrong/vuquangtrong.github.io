#define LOG_TAG "Invcase"

#include <utils/Log.h>
#include <iostream>
#include <fstream>
#include "Invcase.h"

namespace aidl {
namespace android {
namespace hardware {
namespace invcase {

//String getChars();
ndk::ScopedAStatus Invcase::getChars(std::string* _aidl_return) {
    std::ifstream invcase_dev;
    invcase_dev.open("/dev/invcase");
    if(invcase_dev.good()) {
        std::string line;
        invcase_dev >> line;
        ALOGD("Invcase service: getChars: %s", line.c_str());
        *_aidl_return =  line;
    } else {
        ALOGE("getChars: can not open /dev/invcase");
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    }
    return ndk::ScopedAStatus::ok();
}

//void putChars(in String msg);
ndk::ScopedAStatus Invcase::putChars(const std::string& in_msg) {
    std::ofstream invcase_dev;
    invcase_dev.open ("/dev/invcase");
    if(invcase_dev.good()) {
        invcase_dev << in_msg;
        ALOGD("Invcase service: putChars: %s", in_msg.c_str());
    } else {
        ALOGE("putChars: can not open /dev/invcase");
        return ndk::ScopedAStatus::fromServiceSpecificError(-1);
    }
    return ndk::ScopedAStatus::ok();
}

}  // namespace invcase
}  // namespace hardware
}  // namespace android
}  // namespace aidl
