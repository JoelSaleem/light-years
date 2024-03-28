#pragma once
#include "framework/Delegate.h"

namespace ly
{
    class HealthComponent
    {
    public:
        HealthComponent(float health, float maxHealth);
        void ChangeHealth(float amt);
        float GetHealth() const { return mHealth; }
        float GetMaxHealth() const
        {
            return mMaxHealth;
        }

        Delegate<float, float, float> onHealthChanged;

    private:
        void TakenDamage(float amt);
        void HealthRegen(float amt);
        void HealthEmpty();
        float mHealth;
        float mMaxHealth;
    };
}