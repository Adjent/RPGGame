#pragma once
class Health {
private:
    int value;
public:
    Health(int val = 0);
    void decrease(int amount);
    void increase(int amount);
    bool isZero() const;
    int getValue() const;
};