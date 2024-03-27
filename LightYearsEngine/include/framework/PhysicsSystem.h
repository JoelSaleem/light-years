#pragma once
#include "framework/Core.h"
#include <box2d/b2_world.h>

namespace ly
{
    class Actor;
    class PhysicsContactListener : public b2ContactListener
    {
        virtual void EndContact(b2Contact *contact) override;
        virtual void BeginContact(b2Contact *contact) override;
    };

    class PhysicsSystem
    {
    public:
        static PhysicsSystem &Get();
        void Step(float deltaTime);
        b2Body *AddListener(Actor *listener);
        float GetPhysicsScale() const { return mPhysicsScale; }
        void RemoveListener(b2Body *bodyToRemove);

        static void Cleanup();

    protected:
        PhysicsSystem();

    private:
        void ProcessPendingRemoveListeners();
        static unique<PhysicsSystem> physicsSystem;
        b2World mPhysicsWorld;
        float mPhysicsScale;
        int mVelocityIterations;
        int mPositionIterations;
        PhysicsContactListener mContactListener;

        Set<b2Body *> mPendingRemoveListeners;
    };
}