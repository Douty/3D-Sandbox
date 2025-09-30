// Physics/CollisionFilters.cpp
#include "Physics/CollisionFilters.hpp"

namespace Engine::Physics {

    bool ObjVsBPFilter::ShouldCollide(JPH::ObjectLayer layer1, JPH::BroadPhaseLayer layer2) const
    {
        switch (layer1)
        {
        case Layers::NON_MOVING:
          
            return layer2 == JPH::BroadPhaseLayer(BPLayers::BP_MOVING);

        case Layers::MOVING:
         
            return layer2 == JPH::BroadPhaseLayer(BPLayers::BP_MOVING) ||
                layer2 == JPH::BroadPhaseLayer(BPLayers::BP_NON_MOVING);

        default:
            return false;
        }
    }

    bool ObjPairFilter::ShouldCollide(JPH::ObjectLayer layer1, JPH::ObjectLayer layer2) const
    {
        if (layer1 == Layers::NON_MOVING && layer2 == Layers::NON_MOVING)
            return false;

        return true;
    }

} 
