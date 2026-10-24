#pragma once

namespace Red
{
struct ResourceRequest
{
    ResourcePath path;    // 00
    uint64_t unk08{};     // 08
    uint8_t unk10[0x9]{}; // 10
    bool unk19{true};     // 19
    uint8_t unk1A[0x6]{}; // 1A
    int32_t unk20{-1};    // 20
    int32_t unk24{};      // 24
    uint64_t unk28{};     // 28
};
RED4EXT_ASSERT_SIZE(ResourceRequest, 0x30);
RED4EXT_ASSERT_OFFSET(ResourceRequest, path, 0x0);
}

namespace Raw::ResourceLoader
{
constexpr auto LoadAsync = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceLoader_RequestResource,
    /* type = */ void (*)(Red::ResourceLoader* aLoader,
                          Red::SharedPtr<Red::ResourceToken<>>& aToken,
                          Red::ResourceRequest& aRequest)>();

constexpr auto OnUpdate = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceLoader_OnUpdate,
    /* type = */ void (*)(Red::ResourceLoader* aLoader)>();
}
