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
        onDestroy.Broadcast(this);
        mIsPendingDestroy = true;
    }

    weak<Object> Object::GetWeakRef()
    {
        return shared_from_this();
    }
    
    weak<const Object> Object::GetWeakRef() const
    {
        return shared_from_this();
    }
}