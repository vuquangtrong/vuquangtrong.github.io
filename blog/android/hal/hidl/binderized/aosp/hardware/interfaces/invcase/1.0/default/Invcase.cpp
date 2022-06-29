#define LOG_TAG "Invcase"

#include <utils/Log.h>
#include <iostream>
#include <fstream>
#include "Invcase.h"

namespace android {
namespace hardware {
namespace invcase {
namespace V1_0 {
namespace implementation {

// Methods from ::android::hardware::invcase::V1_0::IInvcase follow.
Return<void> Invcase::putChars(const hidl_string& msg) {
    std::ofstream invcase_dev;
    invcase_dev.open ("/dev/invcase");
    if(invcase_dev.good()) {
        invcase_dev << msg;
        ALOGE("putChars: %s", msg.c_str());
    } else {
        ALOGE("putChars: can not open /dev/invcase");
    }
    return Void();
}

Return<void> Invcase::getChars(getChars_cb _hidl_cb) {
    std::ifstream invcase_dev;
    invcase_dev.open("/dev/invcase");
    if(invcase_dev.good()) {
        std::string line;
        invcase_dev >> line;
        ALOGE("getChars: %s", line.c_str());
        hidl_string result(line);
        _hidl_cb(result);
    } else {
        ALOGE("getChars: can not open /dev/invcase");
    }
    return Void();
}


// Methods from ::android::hidl::base::V1_0::IBase follow.

//IInvcase* HIDL_FETCH_IInvcase(const char* /* name */) {
    //return new Invcase();
//}
//
}  // namespace implementation
}  // namespace V1_0
}  // namespace invcase
}  // namespace hardware
}  // namespace android
