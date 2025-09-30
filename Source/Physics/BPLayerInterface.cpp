#include "Physics/BPLayerInterface.hpp"


using namespace Engine::Physics;

JPH::BroadPhaseLayer BPLayerInterface::GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const
{
	switch (inLayer) {
	case Layers::NON_MOVING:
		return JPH::BroadPhaseLayer(BPLayers::BP_NON_MOVING);
	case Layers::MOVING:
		return JPH::BroadPhaseLayer(BPLayers::BP_MOVING);
	default:
		return JPH::BroadPhaseLayer(BPLayers::BP_NON_MOVING);
	}
}
uint32_t BPLayerInterface::GetNumBroadPhaseLayers() const
{
	return BPLayers::NUM_BP_LAYERS;
}
