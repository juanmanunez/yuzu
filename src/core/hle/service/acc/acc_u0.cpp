// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/logging/log.h"
#include "core/hle/ipc_helpers.h"
#include "core/hle/service/acc/acc_u0.h"

namespace Service {
namespace Account {

class IProfile final : public ServiceFramework<IProfile> {
public:
    IProfile() : ServiceFramework("IProfile") {
        static const FunctionInfo functions[] = {
            {1, &IProfile::GetBase, "GetBase"},
        };
        RegisterHandlers(functions);
    }

private:
    void GetBase(Kernel::HLERequestContext& ctx) {
        LOG_WARNING(Service, "(STUBBED) called");
        ProfileBase profile_base{};
        IPC::RequestBuilder rb{ctx, 16};
        rb.Push(RESULT_SUCCESS);
        rb.PushRaw(profile_base);
    }
};

class IManagerForApplication final : public ServiceFramework<IManagerForApplication> {
public:
    IManagerForApplication() : ServiceFramework("IProfile") {
        static const FunctionInfo functions[] = {
            {0, &IManagerForApplication::CheckAvailability, "CheckAvailability"},
        };
        RegisterHandlers(functions);
    }

private:
    void CheckAvailability(Kernel::HLERequestContext& ctx) {
        LOG_WARNING(Service, "(STUBBED) called");
        IPC::RequestBuilder rb{ctx, 3};
        rb.Push(RESULT_SUCCESS);
        rb.Push(true); // TODO: Check when this is supposed to return true and when not
    }
};

void ACC_U0::GetUserExistence(Kernel::HLERequestContext& ctx) {
    LOG_WARNING(Service, "(STUBBED) called");
    IPC::RequestBuilder rb{ctx, 3};
    rb.Push(RESULT_SUCCESS);
    rb.Push(true); // TODO: Check when this is supposed to return true and when not
}

void ACC_U0::GetProfile(Kernel::HLERequestContext& ctx) {
    IPC::RequestBuilder rb{ctx, 2, 0, 0, 1};
    rb.Push(RESULT_SUCCESS);
    rb.PushIpcInterface<IProfile>();
    LOG_DEBUG(Service, "called");
}

void ACC_U0::InitializeApplicationInfo(Kernel::HLERequestContext& ctx) {
    LOG_WARNING(Service, "(STUBBED) called");
    IPC::RequestBuilder rb{ctx, 2};
    rb.Push(RESULT_SUCCESS);
}

void ACC_U0::GetBaasAccountManagerForApplication(Kernel::HLERequestContext& ctx) {
    IPC::RequestBuilder rb{ctx, 2, 0, 0, 1};
    rb.Push(RESULT_SUCCESS);
    rb.PushIpcInterface<IManagerForApplication>();
    LOG_DEBUG(Service, "called");
}

ACC_U0::ACC_U0() : ServiceFramework("acc:u0") {
    static const FunctionInfo functions[] = {
        {1, &ACC_U0::GetUserExistence, "GetUserExistence"},
        {5, &ACC_U0::GetProfile, "GetProfile"},
        {100, &ACC_U0::InitializeApplicationInfo, "InitializeApplicationInfo"},
        {101, &ACC_U0::GetBaasAccountManagerForApplication, "GetBaasAccountManagerForApplication"},
    };
    RegisterHandlers(functions);
}

} // namespace Account
} // namespace Service
