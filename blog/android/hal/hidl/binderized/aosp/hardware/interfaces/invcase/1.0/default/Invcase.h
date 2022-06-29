#pragma once

#include <android/hardware/invcase/1.0/IInvcase.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>

namespace android {
namespace hardware {
namespace invcase {
namespace V1_0 {
namespace implementation {

using ::android::hardware::hidl_array;
using ::android::hardware::hidl_memory;
using ::android::hardware::hidl_string;
using ::android::hardware::hidl_vec;
using ::android::hardware::Return;
using ::android::hardware::Void;
using ::android::sp;

struct Invcase : public IInvcase {
    // Methods from ::android::hardware::invcase::V1_0::IInvcase follow.
    Return<void> putChars(const hidl_string& msg) override;
    Return<void> getChars(getChars_cb _hidl_cb) override;

    // Methods from ::android::hidl::base::V1_0::IBase follow.

};

// FIXME: most likely delete, this is only for passthrough implementations
// extern "C" IInvcase* HIDL_FETCH_IInvcase(const char* name);

}  // namespace implementation
}  // namespace V1_0
}  // namespace invcase
}  // namespace hardware
}  // namespace android
