#pragma once

namespace Raw::ItemObject
{
using ItemID = Core::OffsetPtr<0x288, Red::ItemID>;

// Patch 2.5 inserted a virtual before it, moving it from 0x280.
constexpr auto GetAppearanceName = Core::RawVFunc<
    /* offset = */ 0x288,
    /* type = */ Red::CName* (Red::ItemObject::*)(Red::CName& aOut)>();
}
