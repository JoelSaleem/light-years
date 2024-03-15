#include "framework/Object.h"
#include "framework/Core.h"

namespace ly
{
    Object::Object() : mIsPendingDestroy{false} {}
    Object::~Object()
    {
        LOG("obj destroy");
    }

    void Object::Destroy()
    {
        mIsPendingDestroy = true;
    }

}