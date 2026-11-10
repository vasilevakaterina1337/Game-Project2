#pragma once
class Unit;
class IInteractionStrategy {
public:
    virtual ~IInteractionStrategy() = default;
    virtual void apply(Unit& unit) = 0;
};
class AttackBoostStrategy : public IInteractionStrategy { 
public: 
    void apply(Unit& unit) 
    override; 
};
class HealthRestoreStrategy : public IInteractionStrategy { 
public: 
    void apply(Unit& unit) 
        override; 
};