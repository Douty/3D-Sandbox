#pragma once 
#include "Jolt/Jolt.h"
#include "Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h"

struct BPLayers {
    enum : JPH::BroadPhaseLayer::Type {
        BP_NON_MOVING = 0,
        BP_MOVING = 1,
        NUM_BP_LAYERS
    };
};

struct Layers {
    enum : JPH::ObjectLayer {
        NON_MOVING = 0,
        MOVING = 1,
        NUM_LAYERS
    };
};