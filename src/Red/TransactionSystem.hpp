#pragma once

// Patch 2.5 moved these virtuals one slot down compared to RED4ext::ITransactionSystem,
// so they are called by their 2.5 offsets instead of through the SDK class.
namespace Raw::TransactionSystem
{
constexpr auto IsSlotSpawning = Core::RawVFunc<
    /* addr = */ 0x3D0,
    /* type = */ bool (Red::ITransactionSystem::*)(Red::IScriptable* aOwner, Red::TweakDBID aSlotID)>();

constexpr auto RegisterSlotListener = Core::RawVFunc<
    /* addr = */ 0x498,
    /* type = */ void (Red::ITransactionSystem::*)(Red::IScriptable* aOwner,
                                                   Red::Handle<Red::game::IAttachmentSlotsListener> aListener)>();

constexpr auto UnregisterSlotListener = Core::RawVFunc<
    /* addr = */ 0x4A0,
    /* type = */ void (Red::ITransactionSystem::*)(Red::IScriptable* aOwner,
                                                   Red::Handle<Red::game::IAttachmentSlotsListener> aListener)>();

constexpr auto MatchVisualTagByItemID = Core::RawVFunc<
    /* addr = */ 0x4D8,
    /* type = */ bool (Red::ITransactionSystem::*)(const Red::ItemID& aItemID,
                                                   const Red::Handle<Red::IScriptable>& aOwner,
                                                   Red::CName aTag)>();

constexpr auto MatchVisualTag = Core::RawVFunc<
    /* addr = */ 0x4E0,
    /* type = */ bool (Red::ITransactionSystem::*)(const Red::Handle<Red::IScriptable>& aItem,
                                                   Red::CName aTag,
                                                   bool aUseDefaultAppearance)>();
}
