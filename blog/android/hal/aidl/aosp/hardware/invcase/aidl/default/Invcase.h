#pragma once

#include <aidl/android/hardware/invcase/BnInvcase.h>

namespace aidl {
namespace android {
namespace hardware {
namespace invcase {

class Invcase : public BnInvcase {
    public:
        //String getChars();
        ndk::ScopedAStatus getChars(std::string* _aidl_return);
        //void putChars(in String msg);
        ndk::ScopedAStatus putChars(const std::string& in_msg);
};

}  // namespace invcase
}  // namespace hardware
}  // namespace android
}  // namespace aidl
