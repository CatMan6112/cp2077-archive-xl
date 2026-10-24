#pragma once

#include "Red/Entity.hpp"

namespace Red
{
using ComponentPredicate = FlexCallback<bool (*)(IComponent*)>;

struct EntityBuilderRequest : EntityInitializeRequest
{
    using AllocatorType = Memory::EngineAllocator;

    uint64_t unkD0;                                 // D0
    WeakHandle<entEntityInstanceData> instanceData; // D8
    ComponentPredicate componentPredicate;          // E8 - Called during entity assemble to select components
    uint64_t unk118;                                // 118
};
RED4EXT_ASSERT_SIZE(EntityBuilderRequest, 0x120);

struct EntityBuilderAppearance
{
    Handle<appearanceAppearanceDefinition> definition; // 00
    Handle<appearanceAppearanceResource> resource;     // 10
    SharedPtr<ObjectPackageExtractor> extractor;       // 20
};
RED4EXT_ASSERT_SIZE(EntityBuilderAppearance, 0x30);

// Element of the builder's 0xD0 / 0xE0 arrays: a SharedPtr to an unknown type (16 bytes)
struct EntityBuilderUnkRef
{
    void* instance; // 00
    void* refCount; // 08
};
RED4EXT_ASSERT_SIZE(EntityBuilderUnkRef, 0x10);

struct EntityBuilder
{
    using AllocatorType = Memory::EntityResourceAllocator;

    struct Flags
    {
        uint8_t ExtractEntity : 1;              // 00
        uint8_t unk01 : 1;                      // 01
        uint8_t ExtractAppearance : 1;          // 02
        uint8_t ExtractAppearances : 1;         // 03
        uint8_t InitializeVisualComponents : 1; // 04
    };
    RED4EXT_ASSERT_SIZE(Flags, 0x1);

    WeakPtr<EntityBuilder> self;                       // 00
    SharedPtr<ObjectPackageExtractor> entityExtractor; // 10
    EntityBuilderAppearance appearance;                // 20
    EntityBuilderAppearance unk50;                     // 50
    DynArray<EntityBuilderAppearance> appearances;     // 80
    Handle<entEntityTemplate> entityTemplate;          // 90
    SharedPtr<EntityBuilderRequest> request;           // A0
    Handle<Entity> entity;                             // B0
    DynArray<Handle<IComponent>> components;           // C0
    DynArray<EntityBuilderUnkRef> unkD0;               // D0
    DynArray<EntityBuilderUnkRef> unkE0;               // E0
    SharedSpinLock lock;                               // F0
    redTagList visualTags;                             // F8
    uint64_t unk108;                                   // 108
    Flags flags;                                       // 110
};
RED4EXT_ASSERT_SIZE(EntityBuilder, 0x118);
RED4EXT_ASSERT_OFFSET(EntityBuilder, appearance, 0x20);
RED4EXT_ASSERT_OFFSET(EntityBuilder, appearances, 0x80);
RED4EXT_ASSERT_OFFSET(EntityBuilder, entityTemplate, 0x90);
RED4EXT_ASSERT_OFFSET(EntityBuilder, request, 0xA0);
RED4EXT_ASSERT_OFFSET(EntityBuilder, components, 0xC0);
RED4EXT_ASSERT_OFFSET(EntityBuilder, visualTags, 0xF8);
RED4EXT_ASSERT_OFFSET(EntityBuilder, flags, 0x110);

struct EntityBuilderJobParams
{
    EntityBuilder* entityBuilder;
    WeakPtr<EntityBuilder> entityBuilderWeak;
};
}

namespace Raw::EntityBuilder
{
// using Template = Core::OffsetPtr<0x90, Red::Handle<Red::EntityTemplate>>;
// using Entity = Core::OffsetPtr<0xB0, Red::Handle<Red::Entity>>;
// using Components = Core::OffsetPtr<0xC0, Red::DynArray<Red::Handle<Red::IComponent>>>;
// using VisualTags = Core::OffsetPtr<0xF8, Red::redTagList>;
// using Flags = Core::OffsetPtr<0x110, uint8_t>;

constexpr auto ExtractComponentsJob = Core::RawFunc<
    /* addr = */ Red::AddressLib::EntityBuilder_ExtractComponentsJob,
    /* type = */ void (*)(Red::EntityBuilderJobParams* aParams, void* a2)>();

constexpr auto ScheduleExtractComponentsJob = Core::RawFunc<
    /* addr = */ Red::AddressLib::EntityBuilder_ScheduleExtractComponentsJob,
    /* type = */ void (*)(Red::JobQueue& aJobQueue, void* a2, Red::EntityBuilderJobParams* aParams)>();

// Drops one strong reference, destroying the builder with the game's destructor and allocator on the last one
constexpr auto ReleaseRef = Core::RawFunc<
    /* addr = */ Red::AddressLib::EntityBuilder_ReleaseRef,
    /* type = */ void (*)(Red::SharedPtr<Red::EntityBuilder>& aBuilder)>();
}

namespace Red
{
// Strong reference to an entity builder that is always released by the game.
// The builder is owned by the engine, so the plugin must never run its own destructor on it.
class EntityBuilderRef
{
public:
    explicit EntityBuilderRef(const WeakPtr<EntityBuilder>& aWeak)
        : m_builder(aWeak.Lock())
    {
    }

    ~EntityBuilderRef()
    {
        if (m_builder.refCount)
        {
            Raw::EntityBuilder::ReleaseRef(m_builder);
            m_builder.instance = nullptr;
            m_builder.refCount = nullptr;
        }
    }

    EntityBuilderRef(const EntityBuilderRef&) = delete;
    EntityBuilderRef& operator=(const EntityBuilderRef&) = delete;

    EntityBuilder* operator->() const
    {
        return m_builder.instance;
    }

    explicit operator bool() const
    {
        return m_builder.instance != nullptr;
    }

private:
    SharedPtr<EntityBuilder> m_builder;
};
}
