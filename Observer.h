#pragma once
#include <vector>
#include <algorithm>

class Unit;
enum class UnitEventType { CREATED, DAMAGED, DESTROYED };

struct UnitEvent {
    UnitEventType type;
    Unit* unit;
    int damage;
};

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onUnitEvent(const UnitEvent& event) = 0;
};

class IObservable {
    std::vector<IObserver*> observers_;
public:
    virtual ~IObservable() = default;
    void subscribe(IObserver* obs) { 
        if (obs) 
            observers_.push_back(obs); 
    }
    void unsubscribe(IObserver* obs) { 
        observers_.erase(std::remove(observers_.begin(), observers_.end(), obs), observers_.end()); 
    }
    void notify(const UnitEvent& event) { 
        for (auto* o : observers_) 
            o->onUnitEvent(event); 
    }
};