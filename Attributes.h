#pragma once
#include <algorithm>
#include <stdexcept>

class Health {
private:
    int value_;
    int max_value_;

public:
    explicit Health(int max_val)
        : max_value_(max_val), value_(max_val){}

    int getValue() const {
        return value_;
    }
    int getMaxValue() const{
        return max_value_;
    }

    void decrease(int amount){
        value_ = std::max(0, value_ - amount);
    }
    void increase(int amount) {
        value_ = std::min(max_value_, value_ + amount);
    }
    bool isZero() const {
        return value_ == 0;
    }
};

class Armor {
private:
    int value_;

public:
    explicit Armor(int val)
        : value_(std::max(0, val)) {
    }
    int getValue() const {
        return value_;
    }
    int reduceDamage(int dmg) const {
        return std::max(0, dmg - value_);
    }
};

class Attack {
private:
    int value_;

public:
    explicit Attack(int val)
        : value_(std::max(0, val)) {
    }
    int getValue() const {
        return value_;
    }
    void increase(int amount) {
        value_ += amount;
    }
    int calculateDamage(const Armor& targetArmor) const {
        return targetArmor.reduceDamage(value_);
    }
};