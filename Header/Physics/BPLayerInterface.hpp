#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include "Layer.hpp"

namespace Engine::Physics
{
    class BPLayerInterface final : public JPH::BroadPhaseLayerInterface {
    public:
        uint32_t GetNumBroadPhaseLayers() const override;
        JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer layer) const override;


    };
}
