#pragma once

namespace Red
{
// Patch 2.5 renumbered the archive scopes (1 content, 2 ep1, 4 and 5 patch, 6 mod),
// but the SDK enum still has Mod = 4.
constexpr auto ModArchiveScope = static_cast<ArchiveScope>(6);
}

namespace Raw::ResourceDepot
{
constexpr auto InitializeArchives = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceDepot_InitializeArchives,
    /* type = */ void (*)(Red::ResourceDepot* aDepot)>{};

constexpr auto LoadArchives = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceDepot_LoadArchives,
    /* type = */ bool (*)(Red::ResourceDepot* aDepot,
                          Red::ArchiveGroup& aGroup,
                          const Red::DynArray<Red::CString>& aArchivePaths,
                          Red::DynArray<Red::ResourcePath>& aLoadedResourcePaths,
                          uint32_t aMemoryResident,
                          uint8_t aErrorCategory)>{};

constexpr auto RequestResource = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceDepot_RequestResource,
    /* type = */ uintptr_t* (*)(Red::ResourceDepot* aDepot,
                                const uintptr_t* aOutResourceHandle,
                                Red::ResourcePath aPath,
                                const int32_t* aArchiveHandle)>{};

constexpr auto CheckResource = Core::RawFunc<
    /* addr = */ Red::AddressLib::ResourceDepot_CheckResource,
    /* type = */ bool (*)(Red::ResourceDepot* aDepot, Red::ResourcePath aPath)>{};
}
