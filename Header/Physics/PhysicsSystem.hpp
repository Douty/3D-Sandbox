#pragma once

#include <memory>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Body/BodyID.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h> 
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Physics/BPLayerInterface.hpp> 
#include <Physics/CollisionFilters.hpp>

namespace Engine::Physics {
    class PhysicsSystem {
    public:

        PhysicsSystem() = default;
        ~PhysicsSystem() = default;

        void Init();
        void Update(float deltaTime);


        JPH::BodyID addStaticBox(const JPH::Vec3& halfExtents, const JPH::RVec3& position);
        JPH::BodyID addDynamicBox(const JPH::Vec3& halfExtents, const JPH::RVec3& position);

        JPH::BodyID addStaticSphere(float radius, const JPH::RVec3& position);
        JPH::BodyID addDynamicSphere(float radius, const JPH::RVec3& position);

        void RemoveBody(const JPH::BodyID& bodyID);
        void DestroyBody(const JPH::BodyID& bodyID);


        static JPH::Vec3 ToJoltVec3(const glm::vec3& vec);
        static glm::mat4 ToGLMMat4(const JPH::RMat44& t);

    private:
        using ObjectLayer = JPH::ObjectLayer;
        using BroadPhaseLayer = JPH::BroadPhaseLayer;



    private:

        JPH::PhysicsSystem m_physics; 
        std::unique_ptr<JPH::TempAllocatorImpl>   m_tempAlloc;
        std::unique_ptr<JPH::JobSystemThreadPool> m_jobs;
        BPLayerInterface m_bp;
        ObjVsBPFilter    m_ovbp;
        ObjPairFilter    m_opair;

    };
};