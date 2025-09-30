#pragma once

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>
#include <Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h>
#include "Physics/Layer.hpp" // for Layers and BPLayers

namespace Engine::Physics {

    class ObjVsBPFilter final : public JPH::ObjectVsBroadPhaseLayerFilter {
    public:
        bool ShouldCollide(JPH::ObjectLayer layer1, JPH::BroadPhaseLayer layer2) const override;
    };

    class ObjPairFilter final : public JPH::ObjectLayerPairFilter {
    public:
        bool ShouldCollide(JPH::ObjectLayer layer1, JPH::ObjectLayer layer2) const override;
    };

} 
