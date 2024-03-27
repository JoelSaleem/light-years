#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_contact.h>
#include "framework/MathUtility.h"

namespace ly
{
    unique<PhysicsSystem> PhysicsSystem::physicsSystem{nullptr};

    PhysicsSystem &PhysicsSystem::Get()
    {

        if (!physicsSystem)
        {
            physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
        }

        return *physicsSystem;
    };

    PhysicsSystem::PhysicsSystem() : mPhysicsWorld{b2Vec2{0, 0}},
                                     mPhysicsScale{0.01f},
                                     mVelocityIterations{8},
                                     mPositionIterations{8},
                                     mContactListener{}
    {
        mPhysicsWorld.SetContactListener(&mContactListener);
        mPhysicsWorld.SetAllowSleeping(false);
    }

    void PhysicsSystem::Step(float deltaTime)
    {
        mPhysicsWorld.Step(deltaTime, mVelocityIterations, mPositionIterations);
    }

    b2Body *PhysicsSystem::AddListener(Actor *listener)
    {
        if (listener->IsPendingDestroy())
        {
            return nullptr;
        }

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);

        auto loc = listener->GetActorLocation();
        bodyDef.position.Set(loc.x * GetPhysicsScale(), loc.y * GetPhysicsScale());
        bodyDef.angle = DegreesToRadians(listener->GetActorRotation());

        b2Body *body = mPhysicsWorld.CreateBody(&bodyDef);

        b2PolygonShape shape;
        auto bound = listener->GetActorGlobalBounds();
        shape.SetAsBox(bound.width / 2.f * GetPhysicsScale(), bound.height / 2.f * GetPhysicsScale());

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.isSensor = true;

        body->CreateFixture(&fixtureDef);

        return body;
    }

    void PhysicsSystem::RemoveListener(b2Body *bodyToRemove) {}

    void PhysicsContactListener::BeginContact(b2Contact *contact)
    {
        Actor *actorA = reinterpret_cast<Actor *>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        Actor *actorB = reinterpret_cast<Actor *>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

        if (actorA && !actorA->IsPendingDestroy())
        {
            actorA->OnActorBeginOverlap(actorB);
        }

        if (actorB && !actorB->IsPendingDestroy())
        {
            actorB->OnActorBeginOverlap(actorA);
        }
    }

    void PhysicsContactListener::EndContact(b2Contact *contact)
    {
        Actor *actorA = nullptr;
        Actor *actorB = nullptr;

        if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
        {
            actorA = reinterpret_cast<Actor *>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        }

        if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
        {
            actorB = reinterpret_cast<Actor *>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
        }

        if (actorA && !actorA->IsPendingDestroy())
        {
            actorA->OnActorEndOverlap(actorB);
        }

        if (actorB && !actorB->IsPendingDestroy())
        {
            actorB->OnActorEndOverlap(actorA);
        }
    }
}